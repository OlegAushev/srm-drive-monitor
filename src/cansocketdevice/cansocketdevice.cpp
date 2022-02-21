#include "cansocketdevice.h"


///
///
///
CanSocketDevice::CanSocketDevice()
{

}

///
///
///
CanSocketDevice::~CanSocketDevice()
{
	disconnectDevice();
}

///
///
///
QString CanSocketDevice::findConnectionScript()
{	
	return QFileDialog::getOpenFileName(nullptr, tr("Open SocketCAN Script"), "../", tr("Script Files (*.sh)"));
}

///
///
///
int CanSocketDevice::executeConnectionScript(const QString& scriptPath)
{
	QProcess *process = new QProcess();
#ifdef EDGE_COMPUTER
	QString exec = "sh";
#else
	QString exec = "pkexec";
#endif
	QStringList params{scriptPath};
	process->start(exec, params);
	process->waitForFinished();
	return process->exitCode();
}

///
///
///
void CanSocketDevice::connectDevice(const QString& interface)
{
	m_interface = interface;

	QString scriptPath = findConnectionScript();	
	int exitCode = executeConnectionScript(scriptPath);
	if (exitCode != 0)
	{
		emit statusMessageAvailable("CAN device connection failed. Exit code: " + QString::number(exitCode));
		return;
	}

	m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (m_socket < 0)
	{
		emit statusMessageAvailable("CAN socket initialization failed");
		return;
	}

	std::strcpy(m_ifr.ifr_name, interface.toStdString().c_str());
	ioctl(m_socket, SIOCGIFINDEX, &m_ifr);

	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.can_family = AF_CAN;
	m_addr.can_ifindex = m_ifr.ifr_ifindex;

	if (bind(m_socket, (sockaddr*)&m_addr, sizeof(m_addr)) < 0)
	{
		emit statusMessageAvailable("CAN socket binding failed");
		return;
	}

	emit statusMessageAvailable(QString("CAN device connected to %1").arg(m_interface));

	can_filter filter[1];
	filter[0].can_id = 0;
	filter[0].can_mask = 0x000;
	setsockopt(m_socket, SOL_CAN_RAW, CAN_RAW_FILTER, filter, sizeof(can_filter));

	m_recvTimer = new QTimer();
	QObject::connect(m_recvTimer, &QTimer::timeout, this, &CanSocketDevice::recvFrame);
	m_recvTimer->setInterval(RECV_PERIOD);
	m_recvTimer->start();
}

///
///
///
void CanSocketDevice::disconnectDevice()
{
	if (m_recvTimer)
	{
		m_recvTimer->stop();
		m_recvTimer->disconnect();
		delete m_recvTimer;
	}

	if (close(m_socket) < 0)
	{
		emit statusMessageAvailable("CAN socket closing failed");
	}
	else
	{
		emit statusMessageAvailable("CAN device disconnected");
	}
	m_socket = -1;
}

///
///
///
void CanSocketDevice::recvFrame()
{
	if (m_socket < 0)
	{
		return;
	}
	
	int nBytes;
	can_frame socketCanFrame;

	do
	{	
		nBytes = recv(m_socket, &socketCanFrame, sizeof(can_frame), MSG_PEEK | MSG_DONTWAIT);	// non-blocking read
													// check if there is available CAN frame
		if (nBytes == sizeof(can_frame))
		{
			nBytes = read(m_socket, &socketCanFrame, sizeof(can_frame));			// blocking read
			if (nBytes < 0)
			{
				emit statusMessageAvailable("CAN receiving error");
				return;
			}

			CanBusFrame frame(socketCanFrame.can_id,
					QByteArray((char*)socketCanFrame.data, (int)socketCanFrame.can_dlc));
			emit frameAvailable(frame);
		}
		else if (nBytes < 0 && errno != EAGAIN)	// error was caused not by absence of CAN frame
		{
			emit statusMessageAvailable("CAN receiving error");
			return;
		}
	} while (nBytes == sizeof(can_frame));
}

///
///
///
QString CanSocketDevice::busStatus()
{
	int error = 0;
	socklen_t len = sizeof (error);
	int retval = getsockopt (m_socket, SOL_SOCKET, SO_ERROR, &error, &len);

	if (retval != 0) 
	{
		// there was a problem getting the error code
		return QString("CAN bus status: unknown");
	}

	if (error != 0) 
	{
		// socket has a non zero error status
		return QString("CAN bus status: error %1").arg(error);
	}

	return QString("CAN bus status: OK");
}


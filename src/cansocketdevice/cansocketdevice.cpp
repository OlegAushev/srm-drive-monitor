#include "cansocketdevice.h"


///
///
///
CanSocketDevice::CanSocketDevice()
	: m_recvTimer(new QTimer)
{
	QObject::connect(m_recvTimer, &QTimer::timeout, this, &CanSocketDevice::recvFrame);
	m_recvTimer->setInterval(RECV_PERIOD);
}

///
///
///
CanSocketDevice::~CanSocketDevice()
{

}

///
///
///
QString CanSocketDevice::findConnectionScript()
{	
	return QFileDialog::getOpenFileName(nullptr, tr("Open SocketCAN Script"), "../../", tr("Script Files (*.sh)"));
}

///
///
///
int CanSocketDevice::executeConnectionScript(const QString& scriptPath)
{
	QProcess *process = new QProcess();
	QString exec = "pkexec";
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
	m_recvTimer->start();
}

///
///
///
void CanSocketDevice::disconnectDevice()
{
	m_recvTimer->stop();
	if (close(m_socket) < 0)
	{
		emit statusMessageAvailable("CAN socket closing failed");
	}
	else
	{
		emit statusMessageAvailable("CAN device disconnected");
	}
}

///
///
///
void CanSocketDevice::recvFrame()
{
	can_filter filter[1];
	filter[0].can_id = 0;
	filter[0].can_mask = 0x000;
	setsockopt(m_socket, SOL_CAN_RAW, CAN_RAW_FILTER, filter, sizeof(can_filter));
	
	int nBytes;
	can_frame socketCanFrame;

	nBytes = read(m_socket, &socketCanFrame, sizeof(can_frame));
	if (nBytes < 0)
	{
		emit statusMessageAvailable("CAN receiving error");
		return;
	}

	CanBusFrame frame(socketCanFrame.can_id,
			QByteArray((char*)socketCanFrame.data, (int)socketCanFrame.len));
	emit frameAvailable(frame);
}




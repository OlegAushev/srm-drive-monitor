
#include "canbusdevice.h"


///
///
///
CanBusDevice::CanBusDevice()
{}

///
///
///
CanBusDevice::~CanBusDevice()
{
	disconnectDevice();
}

///
///
///
QString CanBusDevice::findConnectionScript(const QString& interface)
{	
	return QFileDialog::getOpenFileName(nullptr, tr("Open SocketCAN Script"), "../../", tr("Script Files (*.sh)"));
}

///
///
///
int CanBusDevice::executeConnectionScript(const QString& scriptPath)
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
void CanBusDevice::connectDevice(const QString& plugin, const QString& interface)
{
	m_plugin = plugin;
	m_interface = interface;

	QString scriptPath = findConnectionScript(interface);	
	int exitCode = executeConnectionScript(scriptPath);
	if (exitCode != 0)
	{
		emit statusMessageAvailable("CAN device connection failed. Exit code: " + QString::number(exitCode));
		return;
	}

	QString errorString, statusString;
	Status connectionStatus;

	if (QCanBus::instance()->plugins().contains(plugin))
	{
		m_device.reset(QCanBus::instance()->createDevice(plugin, interface, &errorString));
	}
	
	if (!m_device) 
	{
		statusString = QString("Error creating device %1, reason: %2").arg(plugin).arg(errorString);
		connectionStatus = Status::CONNECTION_ERROR;
	}
	else if (!m_device->connectDevice())
	{
		statusString = QString("Connection error %1: %2").arg(interface).arg(m_device->errorString());
		connectionStatus = Status::CONNECTION_ERROR;
	}
	else
	{
		statusString = QString("Plugin: %1, connected to %2").arg(plugin).arg(interface);
		connect(m_device.get(), &QCanBusDevice::framesReceived, this, &CanBusDevice::onFrameReceived);
		connectionStatus = Status::CONNECTED;
	}

	emit statusMessageAvailable(statusString);
}

///
///
///
void CanBusDevice::disconnectDevice()
{
	if (!m_device)
	{
		emit statusMessageAvailable("No CAN device");
		return;
	}

	m_device->disconnectDevice();
	emit statusMessageAvailable("CAN device disconnected");
	m_device.get()->disconnect();
}

///
///
///
QString CanBusDevice::busStatus() const
{
	if (!m_device || !m_device->hasBusStatus())
	{
		return QString("No CAN bus status available");
	}

	switch (m_device->busStatus()) {
	case QCanBusDevice::CanBusStatus::Good:
		return QString("CAN bus status: good");
		break;
	case QCanBusDevice::CanBusStatus::Warning:
		return QString("CAN bus status: warning");
		break;
	case QCanBusDevice::CanBusStatus::Error:
		return QString("CAN bus status: error");
		break;
	case QCanBusDevice::CanBusStatus::BusOff:
		return QString("CAN bus status: bus off");
		break;
	default:
		return QString("CAN bus status: unknown");
		break;
	}
}

///
///
///
void CanBusDevice::onFrameReceived()
{
	while (m_device->framesAvailable())
	{
		QCanBusFrame frame = m_device->readFrame();
		emit frameAvailable(frame);
	}
}





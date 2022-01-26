
#include "canbusdevice.h"


/**
 * @brief Construct a new Can Bus Device:: Can Bus Device object
 * 
 */
CanBusDevice::CanBusDevice()
{}

/**
 * @brief 
 * 
 * @param interface 
 * @return QString 
 */
QString CanBusDevice::findConnectionScript(QString interface)
{	
	return QFileDialog::getOpenFileName(nullptr, tr("Open SocketCAN Script"), "../", tr("Script Files (*.sh)"));
}

/**
 * @brief 
 * 
 * @param scriptPath 
 * @return int 
 */
int CanBusDevice::executeConnectionScript(QString scriptPath)
{
	QProcess *process = new QProcess();
	QString exec = "pkexec";
	QStringList params{scriptPath};
	process->start(exec, params);
	process->waitForFinished();
	return process->exitCode();
}

/**
 * @brief 
 * 
 * @param plugin 
 * @param interface 
 * @return CanBusDevice::Status 
 */
void CanBusDevice::connectDevice(QString plugin, QString interface)
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

/**
 * @brief 
 * 
 * @return CanBusDevice::Status 
 */
void CanBusDevice::disconnectDevice()
{
	if (m_device)
	{
		m_device.get()->disconnect();
		m_device->disconnectDevice();
		emit statusMessageAvailable("CAN device disconnected");
	}
	else
	{
		emit statusMessageAvailable("No CAN device");
	}
}

/**
 * @brief 
 * 
 */
void CanBusDevice::onFrameReceived()
{
	while (m_device->framesAvailable())
	{
		QCanBusFrame frame = m_device->readFrame();
		emit frameAvailable(frame);
	}
}





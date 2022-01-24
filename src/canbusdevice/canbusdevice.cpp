
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
CanBusDevice::Status CanBusDevice::connectDevice(QString plugin, QString interface)
{
	plugin_ = plugin;
	interface_ = interface;

	QString scriptPath = findConnectionScript(interface);	
	int exitCode = executeConnectionScript(scriptPath);
	if (exitCode != 0)
	{
		emit statusMessageAvailable("CAN device connection failed. Exit code: " + QString::number(exitCode));
		return Status::CONNECTION_ERROR;
	}

	QString errorString, statusString;
	Status connectionStatus;

	if (QCanBus::instance()->plugins().contains(plugin))
	{
		device_.reset(QCanBus::instance()->createDevice(plugin, interface, &errorString));
	}
	
	if (!device_) 
	{
		statusString = QString("Error creating device %1, reason: %2").arg(plugin).arg(errorString);
		connectionStatus = Status::CONNECTION_ERROR;
	}
	else if (!device_->connectDevice())
	{
		statusString = QString("Connection error %1: %2").arg(interface).arg(device_->errorString());
		connectionStatus = Status::CONNECTION_ERROR;
	}
	else
	{
		statusString = QString("Plugin: %1, connected to %2").arg(plugin).arg(interface);
		connect(device_.get(), &QCanBusDevice::framesReceived, this, &CanBusDevice::onFrameReceived);
		connectionStatus = Status::CONNECTED;
	}

	emit statusMessageAvailable(statusString);	
	return connectionStatus;
}

/**
 * @brief 
 * 
 * @return CanBusDevice::Status 
 */
CanBusDevice::Status CanBusDevice::disconnectDevice()
{
	if (device_)
	{
		device_.get()->disconnect();
		device_->disconnectDevice();
		emit statusMessageAvailable("CAN device disconnected");
	}
	else
	{
		emit statusMessageAvailable("No CAN device");
	}

	return Status::DISCONNECTED;
}

/**
 * @brief 
 * 
 */
void CanBusDevice::onFrameReceived()
{
	while (device_->framesAvailable())
	{
		QCanBusFrame frame = device_->readFrame();
		emit frameAvailable(frame);
	}
}





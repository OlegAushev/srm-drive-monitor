
#include "mcoclient.h"


namespace microcanopen {

///
///
///
McoClient::McoClient(NodeId clientNodeId, NodeId serverNodeId)
	: m_canDevice(new CanSocketDevice)
	, m_clientNodeId(clientNodeId.value)
	, m_serverNodeId(serverNodeId.value)
	, m_statusTimer(new QTimer(this))
{
	m_canDevice->moveToThread(&m_canDeviceThread);
	connect(&m_canDeviceThread, &QThread::finished, m_canDevice, &QObject::deleteLater);

	for (auto& timer : m_tpdoTimers)
	{
		timer = new QTimer(this);
	}
	
	QObject::connect(m_canDevice, &CanSocketDevice::frameAvailable, this, &McoClient::onFrameReceived);
	QObject::connect(m_canDevice, &CanSocketDevice::statusMessageAvailable, this, &McoClient::onInfoMessageMustBeSent);
	
	QObject::connect(m_tpdoTimers[0], &QTimer::timeout, this, &McoClient::messageTpdo1Required);
	QObject::connect(m_tpdoTimers[1], &QTimer::timeout, this, &McoClient::messageTpdo2Required);
	QObject::connect(m_tpdoTimers[2], &QTimer::timeout, this, &McoClient::messageTpdo3Required);
	QObject::connect(m_tpdoTimers[3], &QTimer::timeout, this, &McoClient::messageTpdo4Required);

	QObject::connect(m_statusTimer, &QTimer::timeout, [this]() { emit infoMessageAvailable(m_canDevice->busStatus()); });

	m_canDeviceThread.start();

	m_statusTimer->setInterval(2000);
	m_statusTimer->start();
}

///
///
///
McoClient::~McoClient()
{
	//delete m_canDevice;
	m_canDeviceThread.quit();
	m_canDeviceThread.wait();
	
}

///
///
///
void McoClient::connectCanDevice(const QString& plugin, const QString& interface)
{
	m_canDevice->connectDevice(interface);
	m_sysTimer.start();
}

///
///
///
void McoClient::disconnectCanDevice()
{
	m_canDevice->disconnectDevice();
	m_sysTimer.invalidate();
}

///
///
///
void McoClient::startTpdoSending()
{
	for (auto& timer : m_tpdoTimers)
	{
		if (timer->interval() != 0)
		{
			timer->start();
		}
	}
}
	
///
///
///
void McoClient::stopTpdoSending()
{
	for (auto& timer : m_tpdoTimers)
	{
		timer->stop();
	}
}

///
///
///
void McoClient::onFrameReceived(const CanBusFrame& frame)
{
	if (frame.frameId() == cobId(CobType::TPDO1, m_serverNodeId))
	{
		CobRpdo1 message = CanSocketDevice::mergeBytes<CobRpdo1>(frame.payload());
		emit messageRpdo1Received(message);
	}
	else if (frame.frameId() == cobId(CobType::TPDO2, m_serverNodeId))
	{
		CobRpdo2 message = CanSocketDevice::mergeBytes<CobRpdo2>(frame.payload());
		emit messageRpdo2Received(message);
	}
	else if (frame.frameId() == cobId(CobType::TPDO3, m_serverNodeId))
	{
		CobRpdo3 message = CanSocketDevice::mergeBytes<CobRpdo3>(frame.payload());
		emit messageRpdo3Received(message);
	}
	else if (frame.frameId() == cobId(CobType::TPDO4, m_serverNodeId))
	{
		CobRpdo4 message = CanSocketDevice::mergeBytes<CobRpdo4>(frame.payload());
		emit messageRpdo4Received(message);
	}
	else if (frame.frameId() == cobId(CobType::TSDO, m_serverNodeId))
	{
		CobSdo message = CanSocketDevice::mergeBytes<CobSdo>(frame.payload());
		emit messageSdoReceived(message);
	}
}

///
///
///
void McoClient::onInfoMessageMustBeSent(const QString& message)
{
	emit infoMessageAvailable(message);
	m_statusTimer->start();
}

///
///
///
void McoClient::sendMessageTpdo1(CobTpdo1 message)
{
	m_canDevice->sendFrame(CanSocketDevice::makeFrame<CobTpdo1>(cobId(CobType::TPDO1, m_clientNodeId), message));
}

///
///
///
void McoClient::sendMessageTpdo2(CobTpdo2 message)
{
	m_canDevice->sendFrame(CanSocketDevice::makeFrame<CobTpdo2>(cobId(CobType::TPDO2, m_clientNodeId), message));
}

///
///
///
void McoClient::sendMessageTpdo3(CobTpdo3 message)
{
	m_canDevice->sendFrame(CanSocketDevice::makeFrame<CobTpdo3>(cobId(CobType::TPDO3, m_clientNodeId), message));
}

///
///
///
void McoClient::sendMessageTpdo4(CobTpdo4 message)
{
	m_canDevice->sendFrame(CanSocketDevice::makeFrame<CobTpdo4>(cobId(CobType::TPDO4, m_clientNodeId), message));
}

///
///
///
void McoClient::sendOdReadRequest(const QString& odEntryName)
{
	ODEntryKey key = findODEntry(odEntryName);
	if (OBJECT_DICTIONARY.at(key).readAccess == false)
	{
		emit onInfoMessageMustBeSent(QString("Object dictionary bad read request: ") + odEntryName);
		m_statusTimer->start();
		return;
	}

	CobSdo message;
	message.index = key.index;
	message.subindex = key.subindex;
	message.cs = SDO_CCS_READ;
	m_canDevice->sendFrame(CanSocketDevice::makeFrame<CobSdo>(cobId(CobType::RSDO, m_serverNodeId), message));
}

///
///
///
void McoClient::sendOdWriteRequest(const QString& odEntryName, CobSdoData data)
{
	ODEntryKey key = findODEntry(odEntryName);
	if (OBJECT_DICTIONARY.at(key).writeAccess == false)
	{
		emit onInfoMessageMustBeSent(QString("Object dictionary bad write request: ") + odEntryName);
		m_statusTimer->start();
		return;
	}

	CobSdo message;
	message.index = key.index;
	message.subindex = key.subindex;
	message.cs = SDO_CCS_WRITE;
	message.data = data;
	m_canDevice->sendFrame(CanSocketDevice::makeFrame<CobSdo>(cobId(CobType::RSDO, m_serverNodeId), message));
}


















}

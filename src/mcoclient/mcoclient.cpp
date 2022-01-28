
#include "mcoclient.h"


namespace microcanopen {

///
///
///
McoClient::McoClient(NodeId clientNodeId, NodeId serverNodeId)
	: m_clientNodeId(clientNodeId.value)
	, m_serverNodeId(serverNodeId.value)
	, tpdoService(clientNodeId)
	, rpdoService(serverNodeId)
	, sdoService(serverNodeId)
{
	connect(&tpdoService, &TpdoService::frameReady, &m_canDevice, &CanBusDevice::sendFrame);
	connect(&m_canDevice, &CanBusDevice::frameAvailable, this, &McoClient::onFrameReceived);
	connect(&sdoService, &SdoService::frameReady, &m_canDevice, &CanBusDevice::sendFrame);

	connect(&m_canDevice, &CanBusDevice::statusMessageAvailable, this, &McoClient::infoMessageAvailable);
	connect(&sdoService, &SdoService::infoMessageAvailable, this, &McoClient::infoMessageAvailable);
}

///
///
///
void McoClient::connectCanDevice(QString plugin, QString interface)
{
	m_canDevice.connectDevice(plugin, interface);
}

///
///
///
void McoClient::disconnectCanDevice()
{
	m_canDevice.disconnectDevice();
}

///
///
///
void McoClient::startTpdoService()
{
	tpdoService.start();
}

///
///
///
void McoClient::stopTpdoService()
{
	tpdoService.stop();
}

///
///
///
void McoClient::onFrameReceived(QCanBusFrame frame)
{
	if ((frame.frameId() == cobId(CobType::TPDO1, m_serverNodeId))
			|| (frame.frameId() == cobId(CobType::TPDO2, 1))
			|| (frame.frameId() == cobId(CobType::TPDO3, 1))
			|| (frame.frameId() == cobId(CobType::TPDO4, 1)))
	{
		rpdoService.processFrame(frame);
	}
	else if (frame.frameId() == cobId(CobType::TSDO, m_serverNodeId))
	{
		sdoService.processResponse(frame);
	}


}


}









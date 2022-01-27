
#include "mcoclient.h"


namespace microcanopen {


McoClient::McoClient(NodeId clientNodeId, NodeId serverNodeId)
	: clientNodeId_(clientNodeId.value)
	, serverNodeId_(serverNodeId.value)
	, tpdoService(clientNodeId)
	, rpdoService(serverNodeId)
	, sdoService(serverNodeId)
{
	connect(&tpdoService, &TpdoService::frameReady, &canDevice, &CanBusDevice::sendFrame);
	connect(&canDevice, &CanBusDevice::frameAvailable, this, &McoClient::onFrameReceived);
	connect(&sdoService, &SdoService::frameReady, &canDevice, &CanBusDevice::sendFrame);
}


void McoClient::onFrameReceived(QCanBusFrame frame)
{
	if ((frame.frameId() == cobId(CobType::TPDO1, serverNodeId_))
			|| (frame.frameId() == cobId(CobType::TPDO2, 1))
			|| (frame.frameId() == cobId(CobType::TPDO3, 1))
			|| (frame.frameId() == cobId(CobType::TPDO4, 1)))
	{
		rpdoService.processFrame(frame);
	}
	else if (frame.frameId() == cobId(CobType::TSDO, serverNodeId_))
	{
		sdoService.processResponse(frame);
	}


}


}









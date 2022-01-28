
#include "tpdoservice.h"


namespace microcanopen {

///
///
///
TpdoService::TpdoService(NodeId nodeId)
	: m_nodeId(nodeId.value)
{
	for (auto& timer : m_timers)
	{
		timer = new QTimer(this);
	}
	
	connect(m_timers[0], &QTimer::timeout, this, &TpdoService::messageTpdo1Required);
	connect(m_timers[1], &QTimer::timeout, this, &TpdoService::messageTpdo2Required);
	connect(m_timers[2], &QTimer::timeout, this, &TpdoService::messageTpdo3Required);
	connect(m_timers[3], &QTimer::timeout, this, &TpdoService::messageTpdo4Required);
}

///
///
///
void TpdoService::sendMessageTpdo1(CobTpdo1 message)
{
	emit frameReady(CanBusDevice::makeFrame<CobTpdo1>(cobId(CobType::TPDO1, m_nodeId), message));
}

///
///
///
void TpdoService::sendMessageTpdo2(CobTpdo2 message)
{
	emit frameReady(CanBusDevice::makeFrame<CobTpdo2>(cobId(CobType::TPDO2, m_nodeId), message));
}

///
///
///
void TpdoService::sendMessageTpdo3(CobTpdo3 message)
{
	emit frameReady(CanBusDevice::makeFrame<CobTpdo3>(cobId(CobType::TPDO3, m_nodeId), message));
}

///
///
///
void TpdoService::sendMessageTpdo4(CobTpdo4 message)
{
	emit frameReady(CanBusDevice::makeFrame<CobTpdo4>(cobId(CobType::TPDO4, m_nodeId), message));
}




} // namespace microcanopen
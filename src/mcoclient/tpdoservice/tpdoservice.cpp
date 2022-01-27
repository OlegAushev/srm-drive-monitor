
#include "tpdoservice.h"


namespace microcanopen {

/**
 * @brief Construct a new Tpdo Service:: Tpdo Service object
 * 
 * @param nodeId 
 */
TpdoService::TpdoService(NodeId nodeId)
	: nodeId_(nodeId.value)
{
	for (auto& timer : timers_)
	{
		timer = new QTimer(this);
	}
	
	connect(timers_[0], &QTimer::timeout, this, &TpdoService::sendTpdo1);
	connect(timers_[1], &QTimer::timeout, this, &TpdoService::sendTpdo2);
	connect(timers_[2], &QTimer::timeout, this, &TpdoService::sendTpdo3);
	connect(timers_[3], &QTimer::timeout, this, &TpdoService::sendTpdo4);
}


/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART BEGIN ====================== */
/* ========================================================================== */
/**
 * @brief 
 * 
 */
void TpdoService::sendTpdo1()
{
	CobTpdo1 msg;
	msg.run = ((buttonRun_->isChecked()) ? 1 : 0);
	msg.emergency_stop = ((buttonEmergencyStop_->isChecked()) ? 1 : 0);
	emit frameReady(CanBusDevice::makeFrame<CobTpdo1>(cobId(CobType::TPDO1, nodeId_), msg));
}

/**
 * @brief 
 * 
 */
void TpdoService::sendTpdo2()
{
	CobTpdo2 msg;
	msg.torque = ((spinBoxTorque_->value() > 0) ? (spinBoxTorque_->value() / 100) * 32767 : (spinBoxTorque_->value() / 100) * 32768);
	emit frameReady(CanBusDevice::makeFrame<CobTpdo2>(cobId(CobType::TPDO2, nodeId_), msg));
}

/**
 * @brief 
 * 
 */
void TpdoService::sendTpdo3()
{
	
}

/**
 * @brief 
 * 
 */
void TpdoService::sendTpdo4()
{
	
}
/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART END   ====================== */
/* ========================================================================== */






} // namespace microcanopen
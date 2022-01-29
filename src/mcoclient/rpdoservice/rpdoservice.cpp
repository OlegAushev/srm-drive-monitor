#include "rpdoservice.h"


namespace microcanopen {

/**
 * @brief Construct a new Rpdo Service:: Rpdo Service object
 * 
 */
RpdoService::RpdoService(NodeId serverNodeId)
	: serverNodeId_(serverNodeId.value)
{

}

/**
 * @brief 
 * 
 * @param frame 
 */
void RpdoService::processFrame(const QCanBusFrame& frame)
{
	uint32_t frameId = frame.frameId();

	if (frameId == cobId(CobType::TPDO1, serverNodeId_))
	{
		CobRpdo1 msg = CanBusDevice::mergeBytes<CobRpdo1>(frame.payload());
		tableRpdo1_->setItem(0, 0, new QTableWidgetItem(QString::number(msg.statusRun)));
		tableRpdo1_->setItem(1, 0, new QTableWidgetItem(QString::number(msg.statusFault)));
		tableRpdo1_->setItem(2, 0, new QTableWidgetItem(QString::number(msg.statusWarning)));
		tableRpdo1_->setItem(3, 0, new QTableWidgetItem(QString::number(msg.statusOverheat)));

		tableRpdo1_->setItem(4, 0, new QTableWidgetItem(QString::number(msg.torque/127.0 * 100.0, 'f', 1)));
		tableRpdo1_->setItem(5, 0, new QTableWidgetItem(QString::number(msg.speed/32767.0 * 8000.0, 'f', 0)));
		tableRpdo1_->setItem(6, 0, new QTableWidgetItem(QString::number(msg.currentS/127.0 * 650, 'f', 0)));
		tableRpdo1_->setItem(7, 0, new QTableWidgetItem(QString::number(msg.power/127.0 * 150000, 'f', 0)));
		tableRpdo1_->setItem(8, 0, new QTableWidgetItem(QString::number(msg.voltageDC/255.0 * 1620.0, 'f', 0)));
		tableRpdo1_->setItem(9, 0, new QTableWidgetItem(QString::number(msg.currentF/255.0 * 35.0, 'f', 1)));
	}
	else if (frameId == cobId(CobType::TPDO2, serverNodeId_))
	{
		CobRpdo2 msg = CanBusDevice::mergeBytes<CobRpdo2>(frame.payload());
		tableRpdo2_->setItem(0, 0, new QTableWidgetItem(QString::number(msg.tempMotorS - 40)));
		tableRpdo2_->setItem(1, 0, new QTableWidgetItem(QString::number(msg.voltageOut/255.0 * 100.0, 'f', 1)));
		tableRpdo2_->setItem(2, 0, new QTableWidgetItem(QString::number(msg.torqueLimitation)));
		tableRpdo2_->setItem(3, 0, new QTableWidgetItem(QString::number(msg.tempMotorFw - 40)));
		tableRpdo2_->setItem(4, 0, new QTableWidgetItem(QString::number(msg.tempHeatsink - 40)));
		tableRpdo2_->setItem(5, 0, new QTableWidgetItem(QString::number(msg.tepmCaseAir - 40)));
	}
	else if (frameId == cobId(CobType::TPDO3, serverNodeId_))
	{
		CobRpdo3 msg = CanBusDevice::mergeBytes<CobRpdo3>(frame.payload());
		tableRpdo3_->setItem(0, 0, new QTableWidgetItem(QString::number(msg.voltagePosHousing/255.0 * 1620.0)));
		tableRpdo3_->setItem(1, 0, new QTableWidgetItem(QString::number(msg.voltageNegHousing/255.0 * 1620.0)));
		tableRpdo3_->setItem(2, 0, new QTableWidgetItem(QString::number(msg.statusInsulationLow)));
		tableRpdo3_->setItem(3, 0, new QTableWidgetItem(QString::number(msg.currentDC/127.0 * 200.0)));
		emit syslogMsgReceived(msg.syslogInfo);
	}
	else if (frameId == cobId(CobType::TPDO4, serverNodeId_))
	{
		CobRpdo4 msg = CanBusDevice::mergeBytes<CobRpdo4>(frame.payload());
		tableRpdo4_->setItem(0, 0, new QTableWidgetItem(QString::number(msg.faultCode, 16).toUpper()));
		tableRpdo4_->setItem(1, 0, new QTableWidgetItem(QString::number(msg.warningCode, 16).toUpper()));
		tableRpdo4_->setItem(2, 0, new QTableWidgetItem(QString::number(msg.nWarnings)));
	}
}






} // namespace microcanopen











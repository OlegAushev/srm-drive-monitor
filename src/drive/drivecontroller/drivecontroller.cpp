#include "drivecontroller.h"


namespace drive {


///
///
///
DriveController::DriveController(microcanopen::McoClient* mcoClient)
	: m_mcoClient(mcoClient)
{
	QObject::connect(&m_mcoClient->tpdoService, &microcanopen::TpdoService::messageTpdo1Required, this, &DriveController::onMessageTpdo1Request);
	QObject::connect(&m_mcoClient->tpdoService, &microcanopen::TpdoService::messageTpdo2Required, this, &DriveController::onMessageTpdo2Request);
	QObject::connect(this, &DriveController::messageTpdo1Ready, &m_mcoClient->tpdoService, &microcanopen::TpdoService::sendMessageTpdo1);
	QObject::connect(this, &DriveController::messageTpdo2Ready, &m_mcoClient->tpdoService, &microcanopen::TpdoService::sendMessageTpdo2);
}

///
///
///
void DriveController::onMessageTpdo1Request()
{
	microcanopen::CobTpdo1 message;
	message.run = ((m_runFlag) ? 1 : 0);
	message.emergencyStop = ((m_emergencyFlag) ? 1 : 0);
	emit messageTpdo1Ready(message);
}

///
///
///
void DriveController::onMessageTpdo2Request()
{
	microcanopen::CobTpdo2 message;

	emit messageTpdo2Ready(message);
}




} // namespace drive
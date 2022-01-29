#include "drivecontroller.h"


namespace drive {


///
///
///
DriveController::DriveController(microcanopen::McoClient* mcoClient)
	: m_mcoClient(mcoClient)
{
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageTpdo1Required, this, &DriveController::onMessageTpdo1Request);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageTpdo2Required, this, &DriveController::onMessageTpdo2Request);
	QObject::connect(this, &DriveController::messageTpdo1Ready, m_mcoClient, &microcanopen::McoClient::sendMessageTpdo1);
	QObject::connect(this, &DriveController::messageTpdo2Ready, m_mcoClient, &microcanopen::McoClient::sendMessageTpdo2);
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
	message.torque = ((m_torquePuRef > 0) ? m_torquePuRef * 32767 : m_torquePuRef * 32768);
	emit messageTpdo2Ready(message);
}




} // namespace drive
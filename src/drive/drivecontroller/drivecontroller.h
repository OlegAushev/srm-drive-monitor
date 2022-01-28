#pragma once


#include "mcoclient/mcoclient.h"


namespace drive {

class DriveController : public QObject
{
	Q_OBJECT
public:
	DriveController(microcanopen::McoClient* mcoClient);
private:
	microcanopen::McoClient* m_mcoClient = nullptr;

	bool m_runFlag = false;
	bool m_emergencyFlag = false;

signals:
	void messageTpdo1Ready(microcanopen::CobTpdo1 message);
	void messageTpdo2Ready(microcanopen::CobTpdo2 message);

public slots:
	void startMotor() { m_runFlag = true; }
	void stopMotor() { m_runFlag = false; }
	void setEmergencyOn() { m_emergencyFlag = true; }
	void setEmergencyOff() { m_emergencyFlag = false; }

private slots:
	void onMessageTpdo1Request();
	void onMessageTpdo2Request();
	

};







} // namespace drive
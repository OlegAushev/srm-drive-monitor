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
	void powerUpDrive() { m_mcoClient->sdoService.sendWriteRequest("POWER UP DRIVE"); }
	void powerDownDrive() { m_mcoClient->sdoService.sendWriteRequest("POWER DOWN DRIVE"); }
	void startMotor() { m_runFlag = true; }
	void stopMotor() { m_runFlag = false; }
	void setEmergencyOn() { m_emergencyFlag = true; }
	void setEmergencyOff() { m_emergencyFlag = false; }

	void resetFaults() { m_mcoClient->sdoService.sendWriteRequest("RESET FAULTS"); }
	void calibratePositionSensor() { m_mcoClient->sdoService.sendWriteRequest("BEGIN POSITION SENSOR CALIBRATION"); }
	void invertRotationDirection() { m_mcoClient->sdoService.sendWriteRequest("INVERT ROTATION"); }

	void getDeviceName() { m_mcoClient->sdoService.sendReadRequest("DEVICE NAME"); }
	void getSoftwareVersion() { m_mcoClient->sdoService.sendReadRequest("SOFTWARE VERSION"); }
	void getBuildConfiguration() { m_mcoClient->sdoService.sendReadRequest("BUILD CONFIGURATION"); }

private slots:
	void onMessageTpdo1Request();
	void onMessageTpdo2Request();
	

};







} // namespace drive
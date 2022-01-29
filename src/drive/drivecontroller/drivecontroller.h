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

	float m_torquePuRef = 0;
	float m_speedRef = 0;
	float m_fieldCurrentRef = 0;
	float m_gammaCorrectionRef = 0;

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

	void setTorque(double valPercentages)
	{
		m_torquePuRef = valPercentages / 100;
	}
	void setSpeed(double val)
	{
		m_speedRef = val;
		m_mcoClient->sdoService.sendWriteRequest("SPEED_RPM", m_speedRef);	
	}
	void setFieldCurrent(double val)
	{
		m_fieldCurrentRef = val;
		m_mcoClient->sdoService.sendWriteRequest("FIELD_CURRENT", m_fieldCurrentRef);		
	}
	void setGammaCorrection(double val)
	{
		m_gammaCorrectionRef = val;
		m_mcoClient->sdoService.sendWriteRequest("GAMMA_ANGLE_DEG", m_gammaCorrectionRef);		
	}

private slots:
	void onMessageTpdo1Request();
	void onMessageTpdo2Request();
	

};







} // namespace drive
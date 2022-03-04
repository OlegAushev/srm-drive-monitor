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
	void resetDevice() { m_mcoClient->sendOdWriteRequest("SYSTEM CONTROL", "RESET DEVICE"); }
	void powerUpDrive() { m_mcoClient->sendOdWriteRequest("DRIVE CONTROL", "POWER UP DRIVE"); }
	void powerDownDrive() { m_mcoClient->sendOdWriteRequest("DRIVE CONTROL", "POWER DOWN DRIVE"); }
	void startMotor() { m_runFlag = true; }
	void stopMotor() { m_runFlag = false; }
	void setEmergencyOn() { m_emergencyFlag = true; }
	void setEmergencyOff() { m_emergencyFlag = false; }

	void resetFaults() { m_mcoClient->sendOdWriteRequest("SYSTEM CONTROL", "RESET FAULTS"); }
	void calibratePositionSensor() { m_mcoClient->sendOdWriteRequest("SYSTEM CONTROL", "BEGIN POSITION SENSOR CALIBRATION"); }
	void invertRotationDirection() { m_mcoClient->sendOdWriteRequest("SYSTEM CONTROL", "INVERT ROTATION"); }

	void getDeviceName() { m_mcoClient->sendOdReadRequest("DEVICE", "DEVICE NAME"); }
	void getSoftwareVersion() { m_mcoClient->sendOdReadRequest("SOFTWARE", "SOFTWARE VERSION"); }
	void getBuildConfiguration() { m_mcoClient->sendOdReadRequest("SOFTWARE", "BUILD CONFIGURATION"); }

	void setTorque(double valPercentages)
	{
		m_torquePuRef = valPercentages / 100;
	}
	void setSpeed(double val)
	{
		m_speedRef = val;
		m_mcoClient->sendOdWriteRequest("WATCH", "SPEED_RPM", m_speedRef);	
	}
	void setFieldCurrent(double val)
	{
		m_fieldCurrentRef = val;
		m_mcoClient->sendOdWriteRequest("WATCH", "FIELD_CURRENT", m_fieldCurrentRef);		
	}
	void setGammaCorrection(double val)
	{
		m_gammaCorrectionRef = val;
		m_mcoClient->sendOdWriteRequest("WATCH", "GAMMA_ANGLE_DEG", m_gammaCorrectionRef);		
	}

private slots:
	void onMessageTpdo1Request();
	void onMessageTpdo2Request();
	

};







} // namespace drive
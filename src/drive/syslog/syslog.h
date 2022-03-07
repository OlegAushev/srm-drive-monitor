#pragma once


#include <QString>
#include <QVector>
#include "models/basicdatatable/basicdatatable.h"


namespace drive {


class Syslog : public QObject
{
	Q_OBJECT
public:
	Syslog();

	Q_INVOKABLE BasicDataTable* faultsTable() { return m_faultsTable; }
	Q_INVOKABLE BasicDataTable* warningsTable() { return m_warningsTable; }

	const QVector<QString>& driveStatesList() const { return DRIVE_STATES; }
	const QVector<QString>& messagesList() const { return SYSLOG_MESSAGES; }

private:
	static BasicDataTable* m_faultsTable;
	static BasicDataTable* m_warningsTable;

	const QVector<QString> FAULTS_AND_WARNINGS_HEADERS = {"Name", "Value"};
	const QVector<QString> FAULTS = {
		"DC_UNDERVOLTAGE",
		"DC_OVERVOLTAGE",
		"PHASE_OVERCURRENT",
		"FIELD_OVERCURRENT",
		"DC_OVERCURRENT",
		"DRIVER_3PH_FLT",
		"DRIVER_1PH_FLT",
		"JUNCTION_OVERTEMP",
		"CASE_AIR_OVERTEMP",
		"STATOR_OVERTEMP",
		"FIELD_WINDING_OVERTEMP",
		"CONNECTION_LOST",
		"CAN_BUS_ERROR",
		"RUNTIME_ERROR",
		"EEPROM_ERROR",
		"PHASE_CURRENT_SENSOR_FAULT",
		"FIELD_CURRENT_SENSOR_FAULT",
		"DC_CURRENT_SENSOR_FAULT",
		"EMERGENCY_STOP",
		"DCLINK_CHARGE_FAILURE",
		"POSSENSOR_CALIBRATION_FAULT",
		"MOTOR_TEMP_SENSOR_FAULT",
		"POWER_CONTACTOR_OPENING_FAULT"
	};

	const QVector<QString> WARNINGS = {
		"DCLINK_DISCONNECTED",
		"DCLINK_CHARGING",
		"DCLINK_HV_AT_OPEN_CONTACTORS",
		"CAN_BUS_WARNING",
		"JUNCTION_OVERHEATING",
		"CASE_AIR_OVERHEATING",
		"STATOR_OVERHEATING",
		"FIELD_WINDING_OVERHEATING"
	};

	const QVector<QString> DRIVE_STATES = {
		"STANDBY",
		"IDLE",
		"PWRUP",
		"READY",
		"PREP",
		"START",
		"INOP",
		"STOP",
		"PWRDOWN",
		"CALPWRUP",
		"CALPOSSENS",
		"EVALMOTOR"
	};

	const QVector<QString> SYSLOG_MESSAGES = {
	"No message",
	"[ INFO ] Device boot - success",
	"[ INFO ] Device is busy",
	"[ INFO ] Device is resetting...",
	"[ INFO ] Read configs from EEPROM - success",
	"[ FAIL ] Read configs from EEPROM - fail",
	"[ INFO ] Reset configs - success",
	"[ FAIL ] Reset configs - fail",
	"[ INFO ] Apply configs - success",
	"[ FAIL ] Apply configs - fail",
	"[ INFO ] Position sensor calibration - success",
	"[ FAIL ] Position sensor calibration - fail",
	"[ INFO ] Write calibration data to EEPROM - success",
	"[ FAIL ] Write calibration data to EEPROM - fail",
	};
};




} // namespace drive
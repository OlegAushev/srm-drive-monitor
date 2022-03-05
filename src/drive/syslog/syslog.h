#pragma once


#include <QString>
#include <QVector>


namespace drive {


class Syslog
{
public:
	const QVector<QString>& driveStatesList() const { return DRIVE_STATES; }
	const QVector<QString>& messagesList() const { return SYSLOG_MESSAGES; }

private:
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
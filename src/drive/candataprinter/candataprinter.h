#pragma once


#include "mcoclient/mcoclient.h"
#include "models/basicdatatable/basicdatatable.h"
#include "chartplotter/chartplotter.h"
#include <QDebug>
#include <QTime>


namespace drive {

static BasicDataTable* testTable;


class CanDataPrinter : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList textMessages MEMBER m_textMessages NOTIFY textMessagesChanged)
public:
	CanDataPrinter(microcanopen::McoClient* mcoClient, ChartPlotter* chartPlotter);

	Q_INVOKABLE BasicDataTable* watchTable() { return m_watchTable; }
	Q_INVOKABLE BasicDataTable* tpdo1Table() { return m_tpdo1Table; }
	Q_INVOKABLE BasicDataTable* tpdo2Table() { return m_tpdo2Table; }
	Q_INVOKABLE BasicDataTable* tpdo3Table() { return m_tpdo3Table; }
	Q_INVOKABLE BasicDataTable* tpdo4Table() { return m_tpdo4Table; }

private:
	microcanopen::McoClient* m_mcoClient = nullptr;
	static BasicDataTable* m_watchTable;
	static BasicDataTable* m_tpdo1Table;
	static BasicDataTable* m_tpdo2Table;
	static BasicDataTable* m_tpdo3Table;
	static BasicDataTable* m_tpdo4Table;
	QTimer* m_watchTimer = nullptr;
	QStringList m_textMessages;

	ChartPlotter* m_chartPlotter = nullptr;

signals:
	void textMessagesChanged();

public slots:
	void startWatch() { m_watchTimer->start(); }
	void stopWatch() { m_watchTimer->stop(); }
	void clearTextMessages()
	{ 
		m_textMessages.clear(); 
		emit textMessagesChanged();
	}

	void setWatchPeriod(int period)
	{
		if (period <= 0)
		{
			m_watchTimer->stop();
		}
		else
		{
			m_watchTimer->start(period);
		}
	}

	int watchPeriod() const { return m_watchTimer->interval(); }

private slots:
	void processAndDisplaySdo(microcanopen::CobSdo message);
	void processAndDisplayRpdo1(microcanopen::CobRpdo1 message);
	void processAndDisplayRpdo2(microcanopen::CobRpdo2 message);
	void processAndDisplayRpdo3(microcanopen::CobRpdo3 message);
	void processAndDisplayRpdo4(microcanopen::CobRpdo4 message);

	void sendWatchRequest();

private:
	const std::vector<std::pair<std::string, std::string>> WATCH_NAMES_AND_UNITS = {
		{"Time",	"s"},
		{"State",	""},
		{"Fault",	""},
		{"Vdc",		"V"},
		{"Idc",		"A"},
		{"If", 		"A"},
		{"Is", 		"A"},
		{"Ipha", 	"A"},
		{"Iphb", 	"A"},
		{"Iphc", 	"A"},
		{"Id", 		"A"},
		{"Iq", 		"A"},
		{"Tpha", 	"°C"},
		{"Tphb", 	"°C"},
		{"Tphc", 	"°C"},
		{"Tair", 	"°C"},
		{"Ts", 		"°C"},
		{"Tfw",		"°C"},
		{"Gamma",	"°"},
		{"Speed",	"rpm"},
		{"Torque",	"Nm"},
		{"Pm",		"W"},
		{"Pel",		"W"}};
	const std::vector<std::pair<std::string, std::string>> TPDO1_NAMES_AND_UNITS = {
		{"Run",		"bool"},
		{"Fault",	"bool"},
		{"Warning",	"bool"},
		{"Overheat",	"bool"},
		{"Torque",	"%"},
		{"Speed",	"rpm"},
		{"Is",		"A"},
		{"Power",	"W"},
		{"Vdc",		"V"},
		{"If",		"A"}};
	const std::vector<std::pair<std::string, std::string>> TPDO2_NAMES_AND_UNITS = {
		{"Tmot",	"°C"},
		{"Vout",	"%"},
		{"TorqLim",	"bool"},
		{"Tfw",		"°C"},
		{"Ths",		"°C"},
		{"Tair",	"°C"}};
	const std::vector<std::pair<std::string, std::string>> TPDO3_NAMES_AND_UNITS = {
		{"Vpc",		"V"}, 
		{"Vnc",		"V"},
		{"Status",	""},
		{"Idc",		"A"}};
	const std::vector<std::pair<std::string, std::string>> TPDO4_NAMES_AND_UNITS = {
		{"Fault", "hex"},
		{"Warning", "hex"},
		{"WarnCnt", ""}};

	const std::vector<QString> DRIVE_STATES = {
		"STANDBY",
		"IDLE",
		"POWERUP",
		"READY",
		"PREPARING",
		"STARTING",
		"IN_OPERATION",
		"STOPPING",
		"POWERDOWN",
		"CALIBRATING_POS_SENSOR_POWERUP",
		"CALIBRATING_POS_SENSOR",
		"EVALUATING_MOTOR"
	};

	const std::vector<QString> SYSLOG_MESSAGES = {
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

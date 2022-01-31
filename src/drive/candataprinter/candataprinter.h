#pragma once


#include "mcoclient/mcoclient.h"
#include "models/basicdatatable/basicdatatable.h"


namespace drive {

static BasicDataTable* testTable;


class CanDataPrinter : public QObject
{
	Q_OBJECT
public:
	CanDataPrinter(microcanopen::McoClient* mcoClient);

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

signals:
	void textMessageAvailable(QString message);

private slots:
	void processAndDisplaySdo(microcanopen::CobSdo message);
	void processAndDisplayRpdo1(microcanopen::CobRpdo1 message);
	void processAndDisplayRpdo2(microcanopen::CobRpdo2 message);
	void processAndDisplayRpdo3(microcanopen::CobRpdo3 message);
	void processAndDisplayRpdo4(microcanopen::CobRpdo4 message);

	void sendWatchRequest();

private:
	const std::vector<std::pair<std::string, std::string>> m_watchNamesAndUnits = {
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
	const std::vector<std::pair<std::string, std::string>> m_tpdo1NamesAndUnits = {
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
	const std::vector<std::pair<std::string, std::string>> m_tpdo2NamesAndUnits = {
		{"Tmot",	"°C"},
		{"Vout",	"%"},
		{"TorqLim",	"bool"},
		{"Tfw",		"°C"},
		{"Ths",		"°C"},
		{"Tair",	"°C"}};
	const std::vector<std::pair<std::string, std::string>> m_tpdo3NamesAndUnits = {
		{"Vpc",		"V"}, 
		{"Vnc",		"V"},
		{"Status",	""},
		{"Idc",		"A"}};
	const std::vector<std::pair<std::string, std::string>> m_tpdo4NamesAndUnits = {
		{"Fault", "hex"},
		{"Warning", "hex"},
		{"WarnCnt", ""}};

	const std::vector<QString> DriveStates = {
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

};






} // namespace drive

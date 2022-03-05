#pragma once


#include "mcoclient/mcoclient.h"
#include "models/basicdatatable/basicdatatable.h"
#include "chartplotter/chartplotter.h"
#include "../syslog/syslog.h"

#include <QTime>


namespace drive {


class CanDataProcessor : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList textMessages MEMBER m_textMessages NOTIFY textMessagesChanged)
public:
	CanDataProcessor(microcanopen::McoClient* mcoClient, ChartPlotter* chartPlotter, Syslog* syslog);

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
	QTimer* m_refreshTimer = nullptr;
	QStringList m_textMessages;

	ChartPlotter* m_chartPlotter = nullptr;
	Syslog* m_syslog = nullptr;

	void sendRefreshSignals();

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
	void processSdo(microcanopen::CobSdo message);
	void processRpdo1(microcanopen::CobRpdo1 message);
	void processRpdo2(microcanopen::CobRpdo2 message);
	void processRpdo3(microcanopen::CobRpdo3 message);
	void processRpdo4(microcanopen::CobRpdo4 message);

	void sendWatchRequest();

private:
	const QVector<QString> HEADER_NAMES = {"Name", "Value", "Unit"};

	const QVector<QPair<QString, QString>> WATCH_NAMES_AND_UNITS = {
		{"Uptime",	"s"},
		{"State",	""},
		{"Fault",	"hex"},
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
	const QVector<QPair<QString, QString>> TPDO1_NAMES_AND_UNITS = {
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
	const QVector<QPair<QString, QString>> TPDO2_NAMES_AND_UNITS = {
		{"Tmot",	"°C"},
		{"Vout",	"%"},
		{"TorqLim",	"bool"},
		{"Tfw",		"°C"},
		{"Ths",		"°C"},
		{"Tair",	"°C"}};
	const QVector<QPair<QString, QString>> TPDO3_NAMES_AND_UNITS = {
		{"Vpc",		"V"}, 
		{"Vnc",		"V"},
		{"Status",	""},
		{"Idc",		"A"}};
	const QVector<QPair<QString, QString>> TPDO4_NAMES_AND_UNITS = {
		{"Fault", "hex"},
		{"Warning", "hex"},
		{"WarnCnt", ""}};
};






} // namespace drive

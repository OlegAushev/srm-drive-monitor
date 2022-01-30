#pragma once


#include "mcoclient/mcoclient.h"
#include "models/basicdatatable/basicdatatable.h"


namespace drive {


class CanDataPrinter : public QObject
{
	Q_OBJECT
public:
	CanDataPrinter(microcanopen::McoClient* mcoClient);

private:
	microcanopen::McoClient* m_mcoClient;
	BasicDataTable m_watchTable;
	BasicDataTable m_tpdo1Table;
	BasicDataTable m_tpdo2Table;
	BasicDataTable m_tpdo3Table;
	BasicDataTable m_tpdo4Table;

private slots:
	void processAndDisplaySdo(microcanopen::CobSdo message);
	void processAndDisplayRpdo1(microcanopen::CobRpdo1 message);
	void processAndDisplayRpdo2(microcanopen::CobRpdo2 message);
	void processAndDisplayRpdo3(microcanopen::CobRpdo3 message);
	void processAndDisplayRpdo4(microcanopen::CobRpdo4 message);

private:
	const std::vector<std::pair<std::string, std::string>>& m_watchNamesAndUnits = {{"Time", "s"}};
	const std::vector<std::pair<std::string, std::string>>& m_tpdo1NamesAndUnits = {{"Run", "bool"}};
	const std::vector<std::pair<std::string, std::string>>& m_tpdo2NamesAndUnits = {{"Tmot", "s"}};
	const std::vector<std::pair<std::string, std::string>>& m_tpdo3NamesAndUnits = {{"Vpc", "V"}, {"Vnc", "V"}};
	const std::vector<std::pair<std::string, std::string>>& m_tpdo4NamesAndUnits = {{"Fault", "hex"}, {"Warning", "hex"}, {"WarnCnt", ""}};
	 

};






} // namespace drive

#include "candataprinter.h"


namespace drive {

///
///
///
BasicDataTable* CanDataPrinter::m_watchTable = nullptr;
BasicDataTable* CanDataPrinter::m_tpdo1Table = nullptr;
BasicDataTable* CanDataPrinter::m_tpdo2Table = nullptr;
BasicDataTable* CanDataPrinter::m_tpdo3Table = nullptr;
BasicDataTable* CanDataPrinter::m_tpdo4Table = nullptr;

///
///
///
CanDataPrinter::CanDataPrinter(microcanopen::McoClient* mcoClient)
	: m_mcoClient(mcoClient)
{
	m_watchTable = new BasicDataTable(m_watchNamesAndUnits, this);
	m_tpdo1Table = new BasicDataTable(m_tpdo1NamesAndUnits, this);
	m_tpdo2Table = new BasicDataTable(m_tpdo2NamesAndUnits, this);
	m_tpdo3Table = new BasicDataTable(m_tpdo3NamesAndUnits, this);
	m_tpdo4Table = new BasicDataTable(m_tpdo4NamesAndUnits, this);

	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageSdoReceived, this, &CanDataPrinter::processAndDisplaySdo);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo1Received, this, &CanDataPrinter::processAndDisplayRpdo1);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo2Received, this, &CanDataPrinter::processAndDisplayRpdo2);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo3Received, this, &CanDataPrinter::processAndDisplayRpdo3);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo4Received, this, &CanDataPrinter::processAndDisplayRpdo4);
}

///
///
///
void CanDataPrinter::processAndDisplaySdo(microcanopen::CobSdo message)
{

}

///
///
///
void CanDataPrinter::processAndDisplayRpdo1(microcanopen::CobRpdo1 message)
{

}

///
///
///
void CanDataPrinter::processAndDisplayRpdo2(microcanopen::CobRpdo2 message)
{
	
}
///
///
///
void CanDataPrinter::processAndDisplayRpdo3(microcanopen::CobRpdo3 message)
{
	
}
///
///
///
void CanDataPrinter::processAndDisplayRpdo4(microcanopen::CobRpdo4 message)
{
	
}







} // namespace drive

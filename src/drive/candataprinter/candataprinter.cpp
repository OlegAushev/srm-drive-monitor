#include "candataprinter.h"
#include <QDebug>

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
	, m_watchTimer(new QTimer(this))
{
	m_watchTable = new BasicDataTable(WATCH_NAMES_AND_UNITS, this);
	m_tpdo1Table = new BasicDataTable(TPDO1_NAMES_AND_UNITS, this);
	m_tpdo2Table = new BasicDataTable(TPDO2_NAMES_AND_UNITS, this);
	m_tpdo3Table = new BasicDataTable(TPDO3_NAMES_AND_UNITS, this);
	m_tpdo4Table = new BasicDataTable(TPDO4_NAMES_AND_UNITS, this);

	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageSdoReceived, this, &CanDataPrinter::processAndDisplaySdo);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo1Received, this, &CanDataPrinter::processAndDisplayRpdo1);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo2Received, this, &CanDataPrinter::processAndDisplayRpdo2);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo3Received, this, &CanDataPrinter::processAndDisplayRpdo3);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo4Received, this, &CanDataPrinter::processAndDisplayRpdo4);

	QObject::connect(m_watchTimer, &QTimer::timeout, this, &CanDataPrinter::sendWatchRequest);
	m_watchTimer->start(10);
}

///
///
///
void CanDataPrinter::processAndDisplaySdo(microcanopen::CobSdo message)
{
	microcanopen::ODEntryKey key = {message.index, message.subindex};
	auto entryIt = microcanopen::OBJECT_DICTIONARY.find(key);
	if (entryIt == microcanopen::OBJECT_DICTIONARY.end())
	{
		return;
	}

	QString category = entryIt->second.category;

	if (category == "WATCH")
	{
		if ((message.subindex >= m_watchTable->rowCount()) || (message.cs != microcanopen::SDO_SCS_READ))
		{
			return;
		}

		switch (message.subindex)
		{
		case 0x01:
			m_watchTable->setValue(message.subindex, QString(DRIVE_STATES[message.data.u32()]));
			break;
				
		case 0x02:
			m_watchTable->setValue(message.subindex, QString("0x") + QString::number(message.data.u32(), 16).toUpper());
			break;

		default:
			m_watchTable->setValue(message.subindex, QString::number(message.data.f32(), 'f', 2));
			break;
		}

		m_watchTable->updateView();
	}
	else
	{
		QString str;
		QTextStream tstream(&str);

		switch (message.cs)
		{
		case microcanopen::SDO_SCS_READ:
			switch (entryIt->second.dataType)
			{
			case microcanopen::OD_FUNC:
				return;
			case microcanopen::OD_UINT32:
				tstream << "[ READ ] " << entryIt->second.category << "::" << entryIt->second.subcategory << "::" << entryIt->second.name << " = " << message.data.u32();
				break;
			case microcanopen::OD_FLOAT32:
				tstream << "[ READ ] " << entryIt->second.category << "::" << entryIt->second.subcategory << "::" << entryIt->second.name << " = " << message.data.f32();
				break;
			case microcanopen::OD_ENUM:
				tstream << "[ READ ] " << entryIt->second.category << "::" << entryIt->second.subcategory << "::" << entryIt->second.name << " = " << message.data.u32();
				break;
			case microcanopen::OD_STRING:
				{
					uint32_t strRaw = message.data.u32();
					char cstr[5];
					memcpy(cstr, &strRaw, 4);
					cstr[4] = '\0';
					QString str(cstr);
					tstream << "[ READ ] " << entryIt->second.category << "::" << entryIt->second.subcategory << "::" << entryIt->second.name << " = " << str;
				}
				break;
			default:
				return;
			}
			break;

		case microcanopen::SDO_SCS_WRITE:
			switch (entryIt->second.dataType)
			{
			case microcanopen::OD_FUNC:
				tstream << "[ DONE ] " << entryIt->second.name;
				break;
			default:
				tstream << "[ DONE ] Write new value to " << entryIt->second.category << "::" << entryIt->second.subcategory << "::" << entryIt->second.name; 
				break;
			}
			break;

		default:
			return;	
		}
		
		m_textMessages.append(str);
		emit textMessagesChanged();
	}
}

///
///
///
void CanDataPrinter::processAndDisplayRpdo1(microcanopen::CobRpdo1 message)
{
	m_tpdo1Table->setValue(0, QString::number(message.statusRun));
	m_tpdo1Table->setValue(1, QString::number(message.statusFault));
	m_tpdo1Table->setValue(2, QString::number(message.statusWarning));
	m_tpdo1Table->setValue(3, QString::number(message.statusOverheat));

	m_tpdo1Table->setValue(4, QString::number(message.torque/127.0 * 100.0, 'f', 1));
	m_tpdo1Table->setValue(5, QString::number(message.speed/32767.0 * 8000.0, 'f', 0));
	m_tpdo1Table->setValue(6, QString::number(message.currentS/127.0 * 650, 'f', 0));
	m_tpdo1Table->setValue(7, QString::number(message.power/127.0 * 150000, 'f', 0));
	m_tpdo1Table->setValue(8, QString::number(message.voltageDC/255.0 * 1620.0, 'f', 0));
	m_tpdo1Table->setValue(9, QString::number(message.currentF/255.0 * 35.0, 'f', 1));

	m_tpdo1Table->updateView();
}

///
///
///
void CanDataPrinter::processAndDisplayRpdo2(microcanopen::CobRpdo2 message)
{
	m_tpdo2Table->setValue(0, QString::number(message.tempMotorS - 40));
	m_tpdo2Table->setValue(1, QString::number(message.voltageOut/255.0 * 100.0, 'f', 1));
	m_tpdo2Table->setValue(2, QString::number(message.torqueLimitation));
	m_tpdo2Table->setValue(3, QString::number(message.tempMotorFw - 40));
	m_tpdo2Table->setValue(4, QString::number(message.tempHeatsink - 40));
	m_tpdo2Table->setValue(5, QString::number(message.tepmCaseAir - 40));

	m_tpdo2Table->updateView();
}
///
///
///
void CanDataPrinter::processAndDisplayRpdo3(microcanopen::CobRpdo3 message)
{
	m_tpdo3Table->setValue(0, QString::number(message.voltagePosHousing/255.0 * 1620.0));
	m_tpdo3Table->setValue(1, QString::number(message.voltageNegHousing/255.0 * 1620.0));
	m_tpdo3Table->setValue(2, QString::number(message.statusInsulationLow));
	m_tpdo3Table->setValue(3, QString::number(message.currentDC/127.0 * 200.0));
	uint32_t syslogMsg = message.syslogInfo;
	if ((syslogMsg > 0) && (syslogMsg < SYSLOG_MESSAGES.size()))
	{
		m_textMessages.append(SYSLOG_MESSAGES.at(syslogMsg));
		emit textMessagesChanged();
	}
	
	m_tpdo3Table->updateView();
}
///
///
///
void CanDataPrinter::processAndDisplayRpdo4(microcanopen::CobRpdo4 message)
{
	m_tpdo4Table->setValue(0, QString::number(message.faultCode, 16).toUpper());
	m_tpdo4Table->setValue(1, QString::number(message.warningCode, 16).toUpper());
	m_tpdo4Table->setValue(2, QString::number(message.nWarnings));

	m_tpdo4Table->updateView();
}

///
///
///
void CanDataPrinter::sendWatchRequest()
{
	static uint32_t subindex = 0;

	microcanopen::ODEntryKey key = {0x2000, subindex};
	auto entryIt = microcanopen::OBJECT_DICTIONARY.find(key);

	if (entryIt == microcanopen::OBJECT_DICTIONARY.end())
	{
		subindex = 0;
		return;
	}
	else
	{
		m_mcoClient->sendOdReadRequest(entryIt->second.name);
		++subindex;
	}
}





} // namespace drive

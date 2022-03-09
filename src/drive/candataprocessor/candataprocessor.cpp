#include "candataprocessor.h"
#include <QDebug>

namespace drive {

///
///
///
BasicDataTable* CanDataProcessor::m_watchTable = nullptr;
BasicDataTable* CanDataProcessor::m_tpdo1Table = nullptr;
BasicDataTable* CanDataProcessor::m_tpdo2Table = nullptr;
BasicDataTable* CanDataProcessor::m_tpdo3Table = nullptr;
BasicDataTable* CanDataProcessor::m_tpdo4Table = nullptr;

///
///
///
CanDataProcessor::CanDataProcessor(microcanopen::McoClient* mcoClient, ChartPlotter* chartPlotter, Syslog* syslog)
	: m_mcoClient(mcoClient)
	, m_watchTimer(new QTimer(this))
	, m_refreshTimer(new QTimer(this))
	, m_chartPlotter(chartPlotter)
	, m_syslog(syslog)
{
	m_watchTable = new BasicDataTable(WATCH_NAMES_AND_UNITS.size(), 3, this);
	m_tpdo1Table = new BasicDataTable(TPDO1_NAMES_AND_UNITS.size(), 3, this);
	m_tpdo2Table = new BasicDataTable(TPDO2_NAMES_AND_UNITS.size(), 3, this);
	m_tpdo3Table = new BasicDataTable(TPDO3_NAMES_AND_UNITS.size(), 3, this);
	m_tpdo4Table = new BasicDataTable(TPDO4_NAMES_AND_UNITS.size(), 3, this);

	/* prepare tables */
	for (auto i = 0; i < 3; ++i)
	{
		m_watchTable->setHeader(i, HEADER_NAMES[i]);
		m_tpdo1Table->setHeader(i, HEADER_NAMES[i]);
		m_tpdo2Table->setHeader(i, HEADER_NAMES[i]);
		m_tpdo3Table->setHeader(i, HEADER_NAMES[i]);
		m_tpdo4Table->setHeader(i, HEADER_NAMES[i]);
	}

	for (auto i = 0; i < m_watchTable->rowCount(); ++i)
	{
		m_watchTable->setValue(i, 0, WATCH_NAMES_AND_UNITS[i].first);
		m_watchTable->setValue(i, 2, WATCH_NAMES_AND_UNITS[i].second);
	}

	for (auto i = 0; i < m_tpdo1Table->rowCount(); ++i)
	{
		m_tpdo1Table->setValue(i, 0, TPDO1_NAMES_AND_UNITS[i].first);
		m_tpdo1Table->setValue(i, 2, TPDO1_NAMES_AND_UNITS[i].second);
	}

	for (auto i = 0; i < m_tpdo2Table->rowCount(); ++i)
	{
		m_tpdo2Table->setValue(i, 0, TPDO2_NAMES_AND_UNITS[i].first);
		m_tpdo2Table->setValue(i, 2, TPDO2_NAMES_AND_UNITS[i].second);
	}

	for (auto i = 0; i < m_tpdo3Table->rowCount(); ++i)
	{
		m_tpdo3Table->setValue(i, 0, TPDO3_NAMES_AND_UNITS[i].first);
		m_tpdo3Table->setValue(i, 2, TPDO3_NAMES_AND_UNITS[i].second);
	}

	for (auto i = 0; i < m_tpdo4Table->rowCount(); ++i)
	{
		m_tpdo4Table->setValue(i, 0, TPDO4_NAMES_AND_UNITS[i].first);
		m_tpdo4Table->setValue(i, 2, TPDO4_NAMES_AND_UNITS[i].second);
	}



	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageSdoReceived, this, &CanDataProcessor::processSdo);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo1Received, this, &CanDataProcessor::processRpdo1);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo2Received, this, &CanDataProcessor::processRpdo2);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo3Received, this, &CanDataProcessor::processRpdo3);
	QObject::connect(m_mcoClient, &microcanopen::McoClient::messageRpdo4Received, this, &CanDataProcessor::processRpdo4);

	QObject::connect(m_watchTimer, &QTimer::timeout, this, &CanDataProcessor::sendWatchRequest);
	m_watchTimer->start(10);

	QObject::connect(m_refreshTimer, &QTimer::timeout, this, &CanDataProcessor::sendRefreshSignals);
	m_refreshTimer->start(100);
}

///
///
///
void CanDataProcessor::processSdo(microcanopen::CobSdo message)
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
			m_watchTable->setValue(message.subindex, 1, m_syslog->driveStatesList().at(message.data.u32()));
			break;
				
		case 0x02:
			m_watchTable->setValue(message.subindex, 1, QString("0x") + QString::number(message.data.u32(), 16).toUpper());
			break;

		default:
			m_watchTable->setValue(message.subindex, 1, QString::number(message.data.f32(), 'f', 2));
			break;
		}
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
				tstream << "[ DONE ] Task " << entryIt->second.category << "::" 
						<< entryIt->second.name << " is completed";
				break;
			default:
				tstream << "[ DONE ] Write new value to " << entryIt->second.category 
						<< "::" << entryIt->second.subcategory << "::" << entryIt->second.name; 
				break;
			}
			break;

		default:
			return;	
		}
		
		m_textMessages.append(str);
	}
}

///
///
///
void CanDataProcessor::processRpdo1(microcanopen::CobRpdo1 message)
{
	m_tpdo1Table->setValue(0, 1, QString::number(message.statusRun));
	m_tpdo1Table->setValue(1, 1, QString::number(message.statusFault));
	m_tpdo1Table->setValue(2, 1, QString::number(message.statusWarning));
	m_tpdo1Table->setValue(3, 1, QString::number(message.statusOverheat));

	m_tpdo1Table->setValue(4, 1, QString::number(message.torque/127.0 * 100.0, 'f', 1));
	m_tpdo1Table->setValue(5, 1, QString::number(message.speed/32767.0 * 8000.0, 'f', 0));
	m_tpdo1Table->setValue(6, 1, QString::number(message.currentS/127.0 * 650, 'f', 0));
	m_tpdo1Table->setValue(7, 1, QString::number(message.power/127.0 * 150000, 'f', 0));
	m_tpdo1Table->setValue(8, 1, QString::number(message.voltageDC/255.0 * 1620.0, 'f', 0));
	m_tpdo1Table->setValue(9, 1, QString::number(message.currentF/255.0 * 35.0, 'f', 1));
}

///
///
///
void CanDataProcessor::processRpdo2(microcanopen::CobRpdo2 message)
{
	m_tpdo2Table->setValue(0, 1, QString::number(message.tempMotorS - 40));
	m_tpdo2Table->setValue(1, 1, QString::number(message.voltageOut/255.0 * 100.0, 'f', 1));
	m_tpdo2Table->setValue(2, 1, QString::number(message.torqueLimitation));
	m_tpdo2Table->setValue(3, 1, QString::number(message.tempMotorFw - 40));
	m_tpdo2Table->setValue(4, 1, QString::number(message.tempHeatsink - 40));
	m_tpdo2Table->setValue(5, 1, QString::number(message.tepmCaseAir - 40));
}
///
///
///
void CanDataProcessor::processRpdo3(microcanopen::CobRpdo3 message)
{
	m_tpdo3Table->setValue(0, 1, QString::number(message.voltagePosHousing/255.0 * 1620.0));
	m_tpdo3Table->setValue(1, 1, QString::number(message.voltageNegHousing/255.0 * 1620.0));
	m_tpdo3Table->setValue(2, 1, QString::number(message.statusInsulationLow));
	m_tpdo3Table->setValue(3, 1, QString::number(message.currentDC/127.0 * 200.0));
	int syslogMsgIndex = message.syslogInfo;
	if ((syslogMsgIndex > 0) && (syslogMsgIndex < m_syslog->messagesList().size()))
	{
		m_textMessages.append(m_syslog->messagesList().at(syslogMsgIndex));
	}
}
///
///
///
void CanDataProcessor::processRpdo4(microcanopen::CobRpdo4 message)
{
	m_tpdo4Table->setValue(0, 1, QString("0x") + QString::number(message.faultCode, 16).toUpper());
	m_syslog->setFault(message.faultCode);
	m_tpdo4Table->setValue(1, 1, QString("0x") + QString::number(message.warningCode, 16).toUpper());
	m_syslog->setWarning(message.warningCode);
	m_tpdo4Table->setValue(2, 1, QString::number(message.nWarnings));
}

///
///
///
void CanDataProcessor::sendWatchRequest()
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
		m_mcoClient->sendOdReadRequest("WATCH", entryIt->second.name);
		++subindex;
	}
}

///
///
///
void CanDataProcessor::sendRefreshSignals()
{
	m_watchTable->dataChanged(0, 1, m_watchTable->rowCount()-1, 1);
	m_tpdo1Table->dataChanged(0, 1, 9, 1);
	m_tpdo2Table->dataChanged(0, 1, 5, 1);
	m_tpdo3Table->dataChanged(0, 1, 3, 1);
	emit textMessagesChanged();
	m_tpdo4Table->dataChanged(0, 1, 2, 1);
}



} // namespace drive

#include "sdoservice.h"


namespace microcanopen {

/**
 * @brief Construct a new Sdo Service:: Sdo Service object
 * 
 * @param serverNodeId 
 */
SdoService::SdoService(NodeId serverNodeId)
	: serverNodeId_(serverNodeId.value)
{
	periodicSdoRequestTimer_ = new QTimer(this);
	connect(periodicSdoRequestTimer_, &QTimer::timeout, this, &SdoService::makePeriodicRequest);
	//periodicSdoRequestTimer_->start();
}

/**
 * @brief 
 * 
 * @param odEntryName 
 */
void SdoService::sendReadRequest(const QString& odEntryName)
{
	ODEntryKey key = findODEntry(odEntryName);
	if (OBJECT_DICTIONARY.at(key).readAccess == false)
	{
		emit infoMessageAvailable(QString("Object dictioanry bad read request: ") + odEntryName);
		return;
	}

	CobSdo msg;
	msg.index = key.index;
	msg.subindex = key.subindex;
	msg.cs = SDO_CCS_READ;
	emit frameReady(CanBusDevice::makeFrame<CobSdo>(cobId(CobType::RSDO, serverNodeId_), msg));
}

/**
 * @brief 
 * 
 * @param odEntryName 
 */
void SdoService::sendWriteRequest(const QString& odEntryName, CobSdoData data)
{
	ODEntryKey key = findODEntry(odEntryName);
	if (OBJECT_DICTIONARY.at(key).writeAccess == false)
	{
		emit infoMessageAvailable(QString("Object dictioanry bad write request: ") + odEntryName);
		return;
	}

	CobSdo msg;
	msg.index = key.index;
	msg.subindex = key.subindex;
	msg.cs = SDO_CCS_WRITE;
	msg.data = data;
	emit frameReady(CanBusDevice::makeFrame<CobSdo>(cobId(CobType::RSDO, serverNodeId_), msg));
}

/**
 * @brief 
 * 
 * @param frame 
 */
void SdoService::processResponse(QCanBusFrame frame)
{
	CobSdo msg = CanBusDevice::mergeBytes<CobSdo>(frame.payload());
	ODEntryKey key = {msg.index, msg.subindex};
	auto entryIt = OBJECT_DICTIONARY.find(key);
	if (entryIt == OBJECT_DICTIONARY.end())
	{
		return;
	}

	QString category = entryIt->second.category;

	if (category == "WATCH")
	{
		if ((msg.subindex >= TABLE_Tsdo->rowCount()) || (msg.cs != SDO_SCS_READ))
		{
			return;
		}

		switch (msg.subindex)
		{
		case 0x01:
			TABLE_Tsdo->setItem(msg.subindex, 0, new QTableWidgetItem(DriveStates[msg.data.u32()]));
			break;
				
		case 0x02:
			TABLE_Tsdo->setItem(msg.subindex, 0, new QTableWidgetItem("0x" + QString::number(msg.data.u32(), 16).toUpper()));
			break;

		default:
			TABLE_Tsdo->setItem(msg.subindex, 0, new QTableWidgetItem(QString::number(msg.data.f32(), 'f', 2)));
			break;
		}
	}
	else
	{
		QString str;
		QTextStream tstream(&str);

		switch (msg.cs)
		{
		case SDO_SCS_READ:
			switch (entryIt->second.dataType)
			{
			case OD_FUNC:
				return;
			case OD_UINT32:
				tstream << "[ READ ] " << entryIt->second.category << ":" << entryIt->second.subcategory << ":" << entryIt->second.name << " = " << msg.data.u32();
				break;
			case OD_FLOAT32:
				tstream << "[ READ ] " << entryIt->second.category << ":" << entryIt->second.subcategory << ":" << entryIt->second.name << " = " << msg.data.f32();
				break;
			case OD_ENUM:
				tstream << "[ READ ] " << entryIt->second.category << ":" << entryIt->second.subcategory << ":" << entryIt->second.name << " = " << msg.data.u32();
				break;
			case OD_STRING:
				{
					uint32_t strRaw = msg.data.u32();
					char cstr[5];
					memcpy(cstr, &strRaw, 4);
					cstr[4] = '\0';
					QString str(cstr);
					tstream << "[ READ ] " << entryIt->second.category << ":" << entryIt->second.subcategory << ":" << entryIt->second.name << " = " << str;
				}
				break;
			default:
				return;
			}
			break;

		case SDO_SCS_WRITE:
			switch (entryIt->second.dataType)
			{
			case OD_FUNC:
				tstream << "[ DONE ] " << entryIt->second.name;
				break;
			default:
				tstream << "[ DONE ] Write new value to " << entryIt->second.category << ":" << entryIt->second.subcategory << ":" << entryIt->second.name; 
				break;
			}
			break;

		default:
			return;	
		}

		TEXTEDIT_Tsdo->append(str);
	}
}

/**
 * @brief 
 * 
 */
void SdoService::makePeriodicRequest()
{
	static uint32_t subindex = 0;
	CobSdo msg;
	msg.index = 0x2000;
	msg.subindex = (subindex++) % 23;
	msg.cs = 2;
	emit frameReady(CanBusDevice::makeFrame<CobSdo>(cobId(CobType::RSDO, serverNodeId_), msg));
}





}





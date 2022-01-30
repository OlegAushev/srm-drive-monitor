#include "configeditor.h"


namespace drive {

///
///
///
ConfigEditor::ConfigEditor(microcanopen::McoClient* mcoClient)
	: m_mcoClient(mcoClient)
{
	parseObjectDictionary();
}

///
///
///
void ConfigEditor::parseObjectDictionary()
{
	for (const auto& entry : microcanopen::OBJECT_DICTIONARY)
	{
		if(entry.second.category == "CONFIG")
		{
			m_driveParameters[entry.second.subcategory].push_back({entry.second.name, entry.second.unit});
		}
	}
}

///
///
///
QStringList ConfigEditor::parameterCategories()
{
	QStringList list;
	for (const auto& category : m_driveParameters)
	{
		list.append(category.first);
	}
	return list;
}

///
///
///
QStringList ConfigEditor::parameterNames(QString category)
{
	QStringList list;
	if (m_driveParameters.count(category))
	{
		for (const auto& parameter : m_driveParameters.at(category))
		{
			list.append(parameter.name);
		}
	}
	return list;
}

///
///
///
void ConfigEditor::readParameter(const QString& name)
{
	m_mcoClient->sendOdReadRequest(name);
}

///
///
///
void ConfigEditor::writeParameter(const QString& name, const QString& value)
{
	auto key = microcanopen::findODEntry(name);
	float valueF32 = value.toFloat();
	uint32_t valueU32 = value.toUInt();
	
	if (name == "REFERENCE")
	{
		if (valueU32 != 0)
		{
			valueU32 = 1;
		}
		m_mcoClient->sendOdWriteRequest(name, valueU32);
	}
	else if (microcanopen::OBJECT_DICTIONARY.at(key).dataType == microcanopen::OD_UINT32)
	{
		m_mcoClient->sendOdWriteRequest(name, valueU32);
	}
	else if (microcanopen::OBJECT_DICTIONARY.at(key).dataType == microcanopen::OD_FLOAT32)
	{
		m_mcoClient->sendOdWriteRequest(name, valueF32);
	}
}

///
///
///
void ConfigEditor::applyParameters()
{
	m_mcoClient->sendOdWriteRequest("APPLY PARAMETERS");
}

///
///
///
void ConfigEditor::resetParameters()
{
	m_mcoClient->sendOdWriteRequest("RESET PARAMETERS");
}












} // namespace drive


#include "configeditor.h"
#include <QDebug>

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
void ConfigEditor::readParameter(const QString& category, const QString& name)
{
	m_mcoClient->sendOdReadRequest(category, name);
}

///
///
///
void ConfigEditor::writeParameter(const QString& category, const QString& name, const QString& value)
{
	auto key = microcanopen::findODEntry(category, name);
	float valueF32 = value.toFloat();
	uint32_t valueU32 = valueF32;

	if (name == "REFERENCE")
	{
		if (valueU32 != 0)
		{
			valueU32 = 1;
		}
		m_mcoClient->sendOdWriteRequest(category, name, valueU32);
	}
	else if (microcanopen::OBJECT_DICTIONARY.at(key).dataType == microcanopen::OD_UINT32)
	{
		m_mcoClient->sendOdWriteRequest(category, name, valueU32);
	}
	else if (microcanopen::OBJECT_DICTIONARY.at(key).dataType == microcanopen::OD_FLOAT32)
	{
		m_mcoClient->sendOdWriteRequest(category, name, valueF32);
	}
}

///
///
///
void ConfigEditor::applyParameters()
{
	m_mcoClient->sendOdWriteRequest("SYSTEM CONTROL", "APPLY PARAMETERS");
}

///
///
///
void ConfigEditor::resetParameters()
{
	m_mcoClient->sendOdWriteRequest("SYSTEM CONTROL", "RESET PARAMETERS");
}












} // namespace drive


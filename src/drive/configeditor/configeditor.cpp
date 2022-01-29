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
















} // namespace drive


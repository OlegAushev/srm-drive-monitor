#include "candatatable.h"


///
///
///
CanDataTable::CanDataTable(const std::vector<std::pair<std::string, std::string>>& namesAndUnits,
				QObject* parent)
	: QObject(parent)
	, m_size(namesAndUnits.size())
{
	for (auto item : namesAndUnits)
	{
		m_names.append(QString::fromStdString(item.first));
		m_values.append(QString());
		m_units.append(QString::fromStdString(item.second));

	}
}





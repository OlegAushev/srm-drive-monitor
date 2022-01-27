#include "basicdatatable.h"


///
///
///
BasicDataTable::BasicDataTable(const std::vector<std::pair<std::string, std::string>>& namesAndUnits,
				QObject* parent)
	: QObject(parent)
	, m_rowCount(namesAndUnits.size())
	, m_columnCount(3)
{
	m_headerNames.append(QString("Name"));
	m_headerNames.append(QString("Value"));
	m_headerNames.append(QString("Unit"));

	for (auto item : namesAndUnits)
	{
		m_names.append(QString::fromStdString(item.first));
		m_values.append(QString());
		m_units.append(QString::fromStdString(item.second));

	}
}





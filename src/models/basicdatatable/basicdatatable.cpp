#include "basicdatatable.h"


///
///
///
BasicDataTable::BasicDataTable(size_t rowCount, size_t columnCount, QObject* parent)
	: QObject(parent)
	, m_rowCount(rowCount)
	, m_columnCount(columnCount)
{
	m_headerNames.resize(columnCount);
	m_data.resize(columnCount);
	for (auto& column : m_data)
	{
		column.resize(rowCount);
	}
}



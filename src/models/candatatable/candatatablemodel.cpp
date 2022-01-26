#include "candatatablemodel.h"
#include "candatatable.h"
#include <QDebug>

///
///
///
CanDataTableModel::CanDataTableModel(QObject* parent)
	: QAbstractTableModel(parent)
	, m_table(nullptr)
{}

///
///
///
int CanDataTableModel::rowCount(const QModelIndex &parent) const 
{
	if (!m_table)
	{
		return 0;
	}
	return m_table->size();
}

///
///
///
int CanDataTableModel::columnCount(const QModelIndex &parent) const 
{
	if (!m_table)
	{
		return 0;
	}
	return 3;
}

///
///
///
QVariant CanDataTableModel::data(const QModelIndex &index, int role) const 
{
	if (!m_table)
	{
		return QVariant();
	}

	switch (role)
	{
	case NAME:
		return m_table->names().at(index.row());
		break;
	case VALUE:
		return m_table->values().at(index.row());
		break;
	case UNIT:
		return m_table->units().at(index.row());
		break;
	default:
		break;
	}
	return QVariant();
}

///
///
///
QHash<int, QByteArray> CanDataTableModel::roleNames() const 
{
	QHash<int, QByteArray> names;
	names[NAME] = "name";
	names[VALUE] = "value";
	names[UNIT] = "unit";
	return names;
}

///
///
///
void CanDataTableModel::setTable(CanDataTable* table)
{
	if (m_table)
	{
		m_table->disconnect(this);
	}

	m_table = table;

	if (m_table)
	{
		// TODO connect
	}
}
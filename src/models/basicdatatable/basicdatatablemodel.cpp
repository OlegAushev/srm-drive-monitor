#include "basicdatatablemodel.h"
#include "basicdatatable.h"
#include <QDebug>

///
///
///
BasicDataTableModel::BasicDataTableModel(QObject* parent)
	: QAbstractTableModel(parent)
	, m_table(nullptr)
{}

///
///
///
int BasicDataTableModel::rowCount(const QModelIndex &parent) const 
{
	Q_UNUSED(parent);
	if (!m_table)
	{
		return 0;
	}
	return m_table->rowCount();
}

///
///
///
int BasicDataTableModel::columnCount(const QModelIndex &parent) const 
{
	Q_UNUSED(parent);
	if (!m_table)
	{
		return 0;
	}
	return m_table->columnCount();
}

///
///
///
QVariant BasicDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (!m_table || (role != Qt::DisplayRole))
	{
		return QVariant();
	}

	if (orientation == Qt::Horizontal)
	{
		if (section < columnCount())
		{
			return m_table->headerNames().at(section);
		}
	}
	else
	{
		return QString("");
	}
	return QVariant();
}

///
///
///
QVariant BasicDataTableModel::data(const QModelIndex &index, int role) const 
{
	if (!m_table)
	{
		return QVariant();
	}
	return m_table->data().at(role - Qt::UserRole).at(index.row());
}

///
///
///
QHash<int, QByteArray> BasicDataTableModel::roleNames() const 
{
	int role = Qt::UserRole;
	QHash<int, QByteArray> names;

	for (const auto& name : m_table->headerNames())
	{
		names[role] = name.toUtf8();
		++role;
	}
	return names;
	//return { {Qt::DisplayRole, "display"} };// - Qt5.15
}

///
///
///
void BasicDataTableModel::setTable(BasicDataTable* table)
{
	if (m_table)
	{
		m_table->disconnect(this);
	}

	m_table = table;

	if (m_table)
	{
		QObject::connect(m_table, &BasicDataTable::dataChanged, 
			[this](int topLeftRow, int topLeftCol, int bottomRightRow, int bottomRightCol)
			{
				emit dataChanged(createIndex(topLeftRow, topLeftCol), 
						createIndex(bottomRightRow, bottomRightCol));
			});
	}
}



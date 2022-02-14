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

	/*switch (role)
	{
	case Qt::DisplayRole:
		switch (index.column())
		{
		case 0:
			return m_table->names().at(index.row());
			break;
		case 1:
			return m_table->values().at(index.row());
			break;
		case 2:
			return m_table->units().at(index.row());
			break;	
		default:
			break;
		}
	default:
		break;
	} - Qt5.15*/
	return QVariant();
}

///
///
///
QHash<int, QByteArray> BasicDataTableModel::roleNames() const 
{
	QHash<int, QByteArray> names;
	names[NAME] = "name";
	names[VALUE] = "value";
	names[UNIT] = "unit";
	return names;
	//return { {Qt::DisplayRole, "display"} }; - Qt5.15
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
						createIndex(bottomRightRow, bottomRightCol), 
						{VALUE});	// Qt::DisplayRole - Qt5.15
			});
	}
}

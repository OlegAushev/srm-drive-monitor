#include "watchdatatablemodel.h"

///
///
///
WatchDataTableModel::WatchDataTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{}

///
///
///
int WatchDataTableModel::rowCount(const QModelIndex &parent) const 
	{
		return 23;
	}

///
///
///
int WatchDataTableModel::columnCount(const QModelIndex &parent) const 
{
	return 3;
}

///
///
///
QVariant WatchDataTableModel::data(const QModelIndex &index, int role) const 
{
	switch (role)
	{
	case Qt::DisplayRole:
		return QString("%1, %2").arg(index.column()).arg(index.row());
		break;
	
	default:
		break;
	}
	return QVariant();
}

///
///
///
QHash<int, QByteArray> WatchDataTableModel::roleNames() const 
{
	return { {Qt::DisplayRole, "display"} };
}
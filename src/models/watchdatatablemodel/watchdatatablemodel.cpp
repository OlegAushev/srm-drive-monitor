#include "watchdatatablemodel.h"
#include <QDebug>

///
///
///
WatchDataTableModel::WatchDataTableModel(QObject* parent)
	: QAbstractTableModel(parent)
	, timer_(new QTimer(this))
{
	timer_->setInterval(1000);
	connect(timer_, &QTimer::timeout , this, &WatchDataTableModel::timerHit);
	timer_->start();
}

///
///
///
int WatchDataTableModel::rowCount(const QModelIndex &parent) const 
	{
		return 4;
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
	case NAME:
		return NAMES.at(index.row());
		break;
	case VALUE:
		return data_.at(index.row());
		break;
	case UNIT:
		return UNITS.at(index.row());
		break;
	default:
		break;
	}
	return QVariant();
}

///
///
///
QVariant WatchDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	qDebug() << section << orientation << role;
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
		return QString("first");
		case 1:
		return QString("second");
		case 2:
		return QString("third");
		}
	}
	return QVariant();
}


///
///
///
QHash<int, QByteArray> WatchDataTableModel::roleNames() const 
{
	QHash<int, QByteArray> roles;
	roles.insert(NAME, "name");
	roles.insert(VALUE, "value");
	roles.insert(UNIT, "unit");
	return roles;
}
#pragma once

#include <QAbstractTableModel>


class WatchDataTableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit WatchDataTableModel(QObject* parent);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;	
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;	
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;


signals:

public slots:

};
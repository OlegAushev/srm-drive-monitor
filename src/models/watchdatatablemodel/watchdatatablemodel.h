#pragma once

#include <QAbstractTableModel>
#include <QTimer>
#include <QTime>
#include <vector>

class WatchDataTableModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	WatchDataTableModel(QObject* parent = nullptr);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;	
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;	
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	QHash<int, QByteArray> roleNames() const override;
private:
	enum RoleName
	{
		NAME = Qt::UserRole + 1,
		VALUE,
		UNIT
	};

	QTimer* timer_;
	QVector<QString> NAMES = {"Time", "State", "Voltage", "Current"};
	std::vector<double> data_ = {0, 0, 0, 0};
	QVector<QString> UNITS = {"s", "", "V", "A"};
signals:

public slots:

private slots:
	void timerHit()
	{
		data_.at(0) += 1;
		QModelIndex topLeft = createIndex(0,1);
		emit dataChanged(topLeft, topLeft, {VALUE});
	}
};
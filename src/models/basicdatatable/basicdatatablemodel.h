#pragma once

#include <QAbstractTableModel>


class BasicDataTable;


class BasicDataTableModel : public QAbstractTableModel
{
	Q_OBJECT
	Q_PROPERTY(BasicDataTable *table READ table WRITE setTable NOTIFY tableChanged)
public:
	BasicDataTableModel(QObject* parent = nullptr);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;	
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;	
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

	BasicDataTable* table() const { return m_table; }
	void setTable(BasicDataTable* table);

private:
	enum RoleName
	{
		NAME = Qt::UserRole,
		VALUE,
		UNIT
	};

	BasicDataTable* m_table;

signals:
	void tableChanged();
public slots:

private slots:

};
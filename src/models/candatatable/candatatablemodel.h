#pragma once

#include <QAbstractTableModel>


class CanDataTable;


class CanDataTableModel : public QAbstractTableModel
{
	Q_OBJECT
	Q_PROPERTY(CanDataTable *table READ table WRITE setTable)
public:
	CanDataTableModel(QObject* parent = nullptr);
	
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;	
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;	
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

	CanDataTable* table() const { return m_table; }
	void setTable(CanDataTable* table);

private:
	enum RoleName
	{
		NAME = Qt::UserRole,
		VALUE,
		UNIT
	};

	CanDataTable* m_table;

signals:

public slots:

private slots:

};
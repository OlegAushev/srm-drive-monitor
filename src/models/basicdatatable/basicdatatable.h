#pragma once


#include <QObject>
#include <QVector>
#include <QString>


class BasicDataTable : public QObject
{
	Q_OBJECT
public:
	explicit BasicDataTable(int rowCount, int columnCount, QObject* parent = nullptr);

	const QVector<QString>& headerNames() const { return m_headerNames; }
	const QVector<QVector<QString>>& data() const { return m_data; }
	int rowCount() const { return m_rowCount; }
	int columnCount() const { return m_columnCount; }

	void setValue(int row, int column, QString value)
	{
		Q_UNUSED(value);
		if (row >= rowCount() || column >= columnCount())
		{
			return;
		}
		m_data[column][row] = value;
	}

	void setHeader(int column, QString name)
	{
		if (column >= columnCount())
		{
			return;
		}
		m_headerNames[column] = name;
	}

private:
	const int m_rowCount;
	const int m_columnCount;
	QVector<QString> m_headerNames;
	QVector< QVector <QString> > m_data;
	
signals:
	void dataChanged(int topLeftRow, int topLeftCol, int bottomRightRow, int bottomRightCol);
};



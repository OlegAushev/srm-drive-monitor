#pragma once


#include <QObject>
#include <QVector>
#include <QString>


class BasicDataTable : public QObject
{
	Q_OBJECT
public:
	explicit BasicDataTable(size_t rowCount, size_t columnCount, QObject* parent = nullptr);

	const QVector<QString>& headerNames() const { return m_headerNames; }
	const QVector<QVector<QString>>& data() const { return m_data; }
	size_t rowCount() const { return m_rowCount; }
	size_t columnCount() const { return m_columnCount; }

	void setValue(size_t row, size_t column, QString value)
	{
		Q_UNUSED(value);
		if (row >= rowCount() || column >= columnCount())
		{
			return;
		}
		m_data[column][row] = value;
	}

	void setHeader(size_t column, QString name)
	{
		if (column >= columnCount())
		{
			return;
		}
		m_headerNames[column] = name;
	}

private:
	const size_t m_rowCount;
	const size_t m_columnCount;
	QVector<QString> m_headerNames;
	QVector< QVector <QString> > m_data;
	
signals:
	void dataChanged(int topLeftRow, int topLeftCol, int bottomRightRow, int bottomRightCol);
};



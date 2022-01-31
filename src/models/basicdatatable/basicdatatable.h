#pragma once


#include <QObject>
#include <QVector>
#include <QString>

#include <vector>
#include <string>

class BasicDataTable : public QObject
{
	Q_OBJECT
public:
	explicit BasicDataTable(const std::vector<std::pair<std::string, std::string>>& namesAndUnits,
				QObject* parent = nullptr);

	const QVector<QString>& headerNames() const { return m_headerNames; }
	const QVector<QString>& names() const { return m_names; }
	const QVector<QString>& values() const { return m_values; }
	const QVector<QString>& units() const { return m_units; }
	size_t rowCount() const { return m_rowCount; }
	size_t columnCount() const { return m_columnCount; }

	void setValue(size_t row, QString value)
	{
		if (row >= rowCount())
		{
			return;
		}
		else
		{
			m_values[row] = value;
		}
	}

	void updateView() { emit tableChanged(); }

private:
	const size_t m_rowCount;
	const size_t m_columnCount;
	QVector<QString> m_headerNames;
	QVector<QString> m_names;
	QVector<QString> m_values;
	QVector<QString> m_units; 
	
signals:
	void tableChanged();


};
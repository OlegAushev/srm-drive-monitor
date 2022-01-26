#pragma once


#include <QObject>
#include <QVector>
#include <QString>

#include <vector>
#include <string>

class CanDataTable : public QObject
{
	Q_OBJECT
public:
	explicit CanDataTable(const std::vector<std::pair<std::string, std::string>>& namesAndUnits,
				QObject* parent = nullptr);

	const QVector<QString>& names() const { return m_names; }
	const QVector<QString>& values() const { return m_values; }
	const QVector<QString>& units() const { return m_units; } 
	size_t size() const { return m_size; }

private:
	const size_t m_size;
	QVector<QString> m_names;
	QVector<QString> m_values;
	QVector<QString> m_units; 



};
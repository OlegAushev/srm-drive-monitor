#pragma once


#include "mcoclient/mcoclient.h"
#include <map>
#include <list>
#include <QString>
#include <QStringList>


//namespace drive {

class ConfigEditor : public QObject
{
	Q_OBJECT
	//Q_PROPERTY(QStringList parameterCategories READ parameterCategories NOTIFY parameterCategoriesChanged)
private:
	microcanopen::McoClient* m_mcoClient = nullptr;

	struct Parameter
	{
		QString name;
		QString unit;
	};

	std::map<QString, std::vector<Parameter> > m_driveParameters;
	void parseObjectDictionary();

public:
	ConfigEditor(microcanopen::McoClient* mcoClient);

	Q_INVOKABLE QStringList parameterCategories()
	{
		QStringList list;
		for (const auto& category : m_driveParameters)
		{
			list.append(category.first);
		}
		return list;
	}

	Q_INVOKABLE QStringList parameterNames(QString category)
	{
		QStringList list;
		if (m_driveParameters.count(category))
		{
			for (const auto& parameter : m_driveParameters.at(category))
			{
				list.append(parameter.name);
			}
		}
		return list;
	}	

signals:
	void parameterCategoriesChanged();
	void parameterNamesChanged();

};



//} // namespace drive


/*
class TestTest : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList list1 READ list1 NOTIFY list1Changed)
public:

};*/
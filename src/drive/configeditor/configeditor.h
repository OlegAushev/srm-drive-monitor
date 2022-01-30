#pragma once


#include "mcoclient/mcoclient.h"
#include <map>
#include <list>
#include <QString>
#include <QStringList>


namespace drive {

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

	Q_INVOKABLE QStringList parameterCategories();
	Q_INVOKABLE QStringList parameterNames(QString category);

	Q_INVOKABLE void readParameter(const QString& name);
	Q_INVOKABLE void writeParameter(const QString& name, const QString& value);
	Q_INVOKABLE void applyParameters();
	Q_INVOKABLE void resetParameters();


signals:
	void parameterCategoriesChanged();
	void parameterNamesChanged();

};



} // namespace drive



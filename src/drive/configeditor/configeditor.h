#pragma once


#include "mcoclient/mcoclient.h"
#include <map>
#include <list>
#include <QString>
#include <QAbstractListModel>


namespace drive {

class ConfigEditor : public QObject
{
	Q_OBJECT
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

};



} // namespace drive

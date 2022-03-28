///
#pragma once


#include <QSettings>
#include <QtWidgets/QApplication>


class AppSettings : public QObject
{
	Q_OBJECT
public:
	AppSettings();
	Q_INVOKABLE QVariant value(const QString& key)
	{
		return m_settings.value(key);
	}

private:
	QSettings m_settings;
};
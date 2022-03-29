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

	Q_INVOKABLE void setValue(const QString& key, const QVariant& value)
	{
		m_settings.setValue(key, value);
	}

	Q_INVOKABLE void restoreDefaultChartsSettings();

private:
	QSettings m_settings;
};
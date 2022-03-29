///
#include "appsettings.h"


///
///
///
AppSettings::AppSettings()
{
	QVariant firstRun = m_settings.value("firstRun");
	if (!firstRun.isValid())
	{
		// write default settings
		m_settings.beginGroup("mcoClient");
		m_settings.setValue("sdoWatchPeriod", 10);
		m_settings.endGroup();

		restoreDefaultChartsSettings();

		m_settings.setValue("firstRun", false);
	}
	else
	{

	}
}

///
///
///
void AppSettings::restoreDefaultChartsSettings()
{
	m_settings.beginGroup("charts");
	m_settings.setValue("updateFreq", 30);
	m_settings.setValue("axisUpdateFreq", 0.5);
	m_settings.setValue("timeWindow", 60);
	m_settings.setValue("openGL", true);
	m_settings.setValue("bufSize", 600);
	m_settings.setValue("timeResolution", 0);
	m_settings.endGroup();
}







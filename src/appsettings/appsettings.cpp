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

		m_settings.setValue("firstRun", false);
	}
	else
	{

	}
}

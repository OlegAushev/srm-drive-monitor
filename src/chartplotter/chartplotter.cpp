#include "chartplotter.h"


///
///
///
ChartPlotter::ChartPlotter(QStringList channelList)
	: m_channelList(channelList)
{
	QSettings settings;
	m_channelBufLength = settings.value("charts/bufSize", 10).toInt();
	m_timeResolution = settings.value("charts/timeResolution", 0).toDouble();

	for (auto channel : m_channelList)
	{
		m_data.insert(channel, {});
		m_data[channel].append({0, 0});
	}
}

///
///
///
ChartPlotter::~ChartPlotter()
{

}

///
///
///
void ChartPlotter::update(const QString& channel, QtCharts::QAbstractSeries* series)
{
	if (series)
	{
		QtCharts::QXYSeries* xySeries = static_cast<QtCharts::QXYSeries*>(series);
		xySeries->replace(m_data[channel]);		
	}
}

///
///
///
void ChartPlotter::addData(const QString& channel, QPointF point)
{
	if ((point.x() - m_data[channel].last().x()) < m_timeResolution)
	{
		return;
	}

	m_data[channel].append(point);

	if (m_data[channel].size() > m_channelBufLength)
	{
		m_data[channel].removeFirst();
	}

	if (point.x() > m_timeSec)
	{
		m_timeSec = point.x();
	}
}


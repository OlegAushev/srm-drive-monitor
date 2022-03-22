#include "chartplotter.h"


///
///
///
ChartPlotter::ChartPlotter(QStringList channelList)
	: m_channelList(channelList)
{
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
	if ((point.x() - m_data[channel].last().x()) < TIME_RESOLUTION)
	{
		return;
	}

	m_data[channel].append(point);

	if (m_data[channel].size() > CHANNEL_BUF_LENGTH)
	{
		m_data[channel].removeFirst();
	}

	if (point.x() > m_timeSec)
	{
		m_timeSec = point.x();
	}
}


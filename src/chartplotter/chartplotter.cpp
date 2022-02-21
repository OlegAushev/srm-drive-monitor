#include "chartplotter.h"


///
///
///
ChartPlotter::ChartPlotter()
	: m_timer(new QTimer(this))
{
	for (auto channel : m_channelList)
	{
		m_data.insert(channel, {});
		m_data[channel].append({0, 0});
		m_minValues.insert(channel, 0);
		m_maxValues.insert(channel, 0);
	} 

	QObject::connect(m_timer, &QTimer::timeout, this, &ChartPlotter::generateData);
	m_sysTimer.start();
	m_timer->start(50);
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
}

///
///
///
void ChartPlotter::generateData()
{
	double x = timeMsec() / 1000.0;
	double y1 = 500 * std::sin(0.05*x) * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	double y2 = 1000 * std::sin(0.01*x);//QRandomGenerator::global()->bounded(-100, 100);
	double y3 = 75 * std::sin(0.5*x) * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	addData("Channel1", QPointF(x, y1));
	addData("Channel2", QPointF(x, y2));
	addData("Channel3", QPointF(x, y3));
}








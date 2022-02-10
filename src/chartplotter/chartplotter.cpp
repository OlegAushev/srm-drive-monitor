#include "chartplotter.h"


///
///
///
ChartPlotter::ChartPlotter()
	: m_timer(new QTimer(this))
{
	m_data.resize(CHANNEL_COUNT);
	QObject::connect(m_timer, &QTimer::timeout, this, &ChartPlotter::generateData);
	m_sysTimer.start();
	m_timer->start(10);
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
void ChartPlotter::update(int channel, QtCharts::QAbstractSeries* series)
{
	if (channel < 0 || channel >= CHANNEL_COUNT)
	{
		return;
	}

	if (series)
	{
		QtCharts::QXYSeries* xySeries = static_cast<QtCharts::QXYSeries*>(series);
		xySeries->replace(m_data[channel]);		
	}
}

///
///
///
void ChartPlotter::addData(int channel, QPointF point)
{
	if (channel < 0 || channel >= CHANNEL_COUNT)
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
	double y1 = 25 * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	double y2 = 50 * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	double y3 = 75 * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	addData(CHANNEL_1, QPointF(x, y1));
	addData(CHANNEL_2, QPointF(x, y2));
	addData(CHANNEL_3, QPointF(x, y3));
}








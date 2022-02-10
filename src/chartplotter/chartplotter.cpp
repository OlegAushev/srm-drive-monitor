#include "chartplotter.h"


///
///
///
ChartPlotter::ChartPlotter()
	: m_timer(new QTimer(this))
{
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
	if (series)
	{
		QtCharts::QXYSeries* xySeries = static_cast<QtCharts::QXYSeries*>(series);

		switch (channel)
		{
		case CHANNEL_1:
			xySeries->replace(m_data1);
			break;
		case CHANNEL_2:
			xySeries->replace(m_data2);
			break;
		case CHANNEL_3:
			xySeries->replace(m_data3);
			break;
		default:
			break;
		}
		
	}
}

///
///
///
void ChartPlotter::addData(int channel, QPointF point)
{
	switch (channel)
	{
	case CHANNEL_1:
		m_data1.append(point);
		break;
	case CHANNEL_2:
		m_data2.append(point);
		break;
	case CHANNEL_3:
		m_data3.append(point);
		break;
	default:
		break;
	}
}

///
///
///
void ChartPlotter::generateData()
{
	double x = timeMs() / 1000.0;
	double y1 = 25 * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	double y2 = 50 * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	double y3 = 75 * std::sin(x);//QRandomGenerator::global()->bounded(-100, 100);
	addData(CHANNEL_1, QPointF(x, y1));
	addData(CHANNEL_2, QPointF(x, y2));
	addData(CHANNEL_3, QPointF(x, y3));
}








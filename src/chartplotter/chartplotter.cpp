#include "chartplotter.h"


///
///
///
ChartPlotter::ChartPlotter()
{

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
void ChartPlotter::update(QtCharts::QAbstractSeries* series)
{
	if (series)
	{
		QtCharts::QXYSeries* xySeries = static_cast<QtCharts::QXYSeries*>(series);
		xySeries->replace(m_data);
	}
}

///
///
///
void ChartPlotter::addData(QPointF point)
{
	m_data.append(point);
}










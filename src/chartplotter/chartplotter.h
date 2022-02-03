#pragma once


#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>


class ChartPlotter : public QObject
{
	Q_OBJECT
public:
	ChartPlotter();
	~ChartPlotter();

private:
	QVector<QPointF> m_data;

public slots:
	void update(QtCharts::QAbstractSeries* series);
	void addData(QPointF point);

private:


};




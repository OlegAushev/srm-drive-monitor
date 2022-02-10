#pragma once


#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>

#include <QTimer>
#include <QElapsedTimer>
#include <QtCore/QRandomGenerator>
#include <cmath>


class ChartPlotter : public QObject
{
	Q_OBJECT
public:
	enum Channel
	{
		CHANNEL_1,
		CHANNEL_2,
		CHANNEL_3,
	};

	ChartPlotter();
	~ChartPlotter();

	int timeMs()
	{
		if (!m_sysTimer.isValid())
		{
			return 0;
		}
		return m_sysTimer.nsecsElapsed() / 1000'000; 
	}

private:
	QVector<QPointF> m_data1;
	QVector<QPointF> m_data2;
	QVector<QPointF> m_data3;

	QTimer* m_timer;
	QElapsedTimer m_sysTimer;

public slots:
	void update(int channel, QtCharts::QAbstractSeries* series);
	void addData(int channel, QPointF point);

private slots:
	void generateData();

private:


};




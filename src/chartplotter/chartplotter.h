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

	int timeMsec()
	{
		if (!m_sysTimer.isValid())
		{
			return 0;
		}
		return m_sysTimer.nsecsElapsed() / 1000'000; 
	}

private:
	static const inline int CHANNEL_COUNT = 3;
	static const inline int CHANNEL_BUF_LENGTH = 1000;

	QVector<QList<QPointF>> m_data;

	QTimer* m_timer;
	QElapsedTimer m_sysTimer;

public slots:
	void update(int channel, QtCharts::QAbstractSeries* series);
	void addData(int channel, QPointF point);

	double timeSec() { return timeMsec() / 1000.0; }

private slots:
	void generateData();

private:


};




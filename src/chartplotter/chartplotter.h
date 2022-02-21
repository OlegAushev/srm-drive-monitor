#pragma once


#include <QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>

#include <QTimer>
#include <QElapsedTimer>
#include <QtCore/QRandomGenerator>
#include <cmath>
#include <algorithm>


class ChartPlotter : public QObject
{
	Q_OBJECT
/*public:
	ChartPlotter();
	~ChartPlotter();

	Q_INVOKABLE QStringList channelList() const { return m_channelList; };

	int timeMsec()
	{
		if (!m_sysTimer.isValid())
		{
			return 0;
		}
		return m_sysTimer.nsecsElapsed() / 1000'000; 
	}

	Q_INVOKABLE double timeSec() { return timeMsec() / 1000.0; }

	Q_INVOKABLE double minValue(const QString& channel) 
	{	
		return (*std::min_element(m_data[channel].begin(), m_data[channel].end(),
			[](const QPointF& first, const QPointF& second)
			{
				return first.y() < second.y();
			})).y();
	}
	
	Q_INVOKABLE double maxValue(const QString& channel)
	{
		return (*std::max_element(m_data[channel].begin(), m_data[channel].end(),
			[](const QPointF& first, const QPointF& second)
			{
				return first.y() < second.y();
			})).y();
	}

private:
	static const inline int CHANNEL_COUNT = 3;
	static const inline int CHANNEL_BUF_LENGTH = 600;
	static const inline double TIME_RESOLUTION = 0.1;
	QStringList m_channelList = {"Channel1", "Channel2", "Channel3"};

	QMap<QString, QList<QPointF>> m_data;
	QMap<QString, double> m_minValues;
	QMap<QString, double> m_maxValues;

	QTimer* m_timer;
	QElapsedTimer m_sysTimer;

public slots:
	void update(const QString& channel, QtCharts::QAbstractSeries* series);
	void addData(const QString& channel, QPointF point);

private slots:
	void generateData();

private:

*/
};




#pragma once


#include <QObject>
#include <QStringList>
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
public:
	ChartPlotter(QStringList channelList);
	~ChartPlotter();

	Q_INVOKABLE QStringList channelList() const { return m_channelList; };

	Q_INVOKABLE double minValue(const QString& channel) 
	{	
		if (m_data[channel].empty())
		{
			return -100;
		}

		return (*std::min_element(m_data[channel].begin(), m_data[channel].end(),
			[](const QPointF& first, const QPointF& second)
			{
				return first.y() < second.y();
			})).y();
	}
	
	Q_INVOKABLE double maxValue(const QString& channel)
	{
		if (m_data[channel].empty())
		{
			return 100;
		}

		return (*std::max_element(m_data[channel].begin(), m_data[channel].end(),
			[](const QPointF& first, const QPointF& second)
			{
				return first.y() < second.y();
			})).y();
	}

	Q_INVOKABLE double timeSec() { return m_timeSec; }

private:
	static const inline int CHANNEL_BUF_LENGTH = 600;
	static const inline double TIME_RESOLUTION = 0;
	QStringList m_channelList;

	QMap<QString, QList<QPointF>> m_data;
	double m_timeSec = 0;

public slots:
	void update(const QString& channel, QtCharts::QAbstractSeries* series);
	void addData(const QString& channel, QPointF point);

private slots:

private:


};




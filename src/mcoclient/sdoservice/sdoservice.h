#pragma once


#include "canbusdevice/canbusdevice.h"
#include "../mcodef.h"
#include "../objectdictionary/objectdictionary.h"
#include <QTableWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QTimer>


namespace microcanopen {


class SdoService : public QObject
{
	Q_OBJECT
public:
	SdoService(NodeId serverNodeId);
	void processResponse(const QCanBusFrame& frame);
	void sendReadRequest(const QString& odEntryName);
	void sendWriteRequest(const QString& odEntryName, CobSdoData data = {});
private:
	const unsigned int serverNodeId_;
signals:
	void frameReady(const QCanBusFrame& frame);
	void infoMessageAvailable(const QString& message);

/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART BEGIN ====================== */
/* ========================================================================== */
public:
	void assignTsdoDestWidgets(QTableWidget* tableTsdo, QTextEdit* textLog)
	{
		TABLE_Tsdo = tableTsdo;
		TEXTEDIT_Tsdo = textLog;
	}

	void setRequestPeriod(int msec) { periodicSdoRequestTimer_->setInterval(msec); }
	void start()
	{
		if (periodicSdoRequestTimer_->interval() != 0)
		{
			periodicSdoRequestTimer_->start();
		}
	}

	void stop() { periodicSdoRequestTimer_->stop(); }
private:
	QTableWidget* TABLE_Tsdo = nullptr; 
	QTextEdit* TEXTEDIT_Tsdo = nullptr;
	const std::vector<QString> DriveStates = {
		"STANDBY",
		"IDLE",
		"POWERUP",
		"READY",
		"PREPARING",
		"STARTING",
		"IN_OPERATION",
		"STOPPING",
		"POWERDOWN",
		"CALIBRATING_POS_SENSOR_POWERUP",
		"CALIBRATING_POS_SENSOR",
		"EVALUATING_MOTOR"
	};
	QTimer* periodicSdoRequestTimer_ = nullptr;
	void makePeriodicRequest();
/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART END   ====================== */
/* ========================================================================== */



};




}





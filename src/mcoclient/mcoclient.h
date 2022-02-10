#pragma once


#include "cansocketdevice/cansocketdevice.h"
#include "mcodef.h"
#include "tpdodef.h"
#include "rpdodef.h"
#include "objectdictionary/objectdictionary.h"
#include <array>

#include <QTimer>
#include <QThread>
#include <QElapsedTimer>


namespace microcanopen {

class McoClient : public QObject
{
	Q_OBJECT
public:
	McoClient(NodeId clientNodeId, NodeId serverNodeId);
	~McoClient();

	void setTpdoPeriod(TpdoNum tpdoNum, int msec) { m_tpdoTimers[static_cast<size_t>(tpdoNum)]->setInterval(msec); }
	void sendOdReadRequest(const QString& odEntryName);
	void sendOdWriteRequest(const QString& odEntryName, CobSdoData data = {});

	int timeMsec()
	{
		if (!m_sysTimer.isValid())
		{
			return 0;
		}
		return m_sysTimer.nsecsElapsed() / 1000'000; 
	}

private:
	QThread m_canDeviceThread;
	CanSocketDevice* m_canDevice = nullptr;
	const unsigned int m_clientNodeId = 0;
	const unsigned int m_serverNodeId = 0;
	QTimer* m_statusTimer;

	std::array<QTimer*, 4> m_tpdoTimers;

	QElapsedTimer m_sysTimer;

signals:
	void infoMessageAvailable(QString message);

	void messageTpdo1Required();
	void messageTpdo2Required();
	void messageTpdo3Required();
	void messageTpdo4Required();

	void messageRpdo1Received(CobRpdo1 message);
	void messageRpdo2Received(CobRpdo2 message);
	void messageRpdo3Received(CobRpdo3 message);
	void messageRpdo4Received(CobRpdo4 message);
	void messageSdoReceived(CobSdo message);

public slots:
	void connectCanDevice(const QString& interface);
	void disconnectCanDevice();

	void startTpdoSending();
	void stopTpdoSending();

	void sendMessageTpdo1(CobTpdo1 message);
	void sendMessageTpdo2(CobTpdo2 message);
	void sendMessageTpdo3(CobTpdo3 message);
	void sendMessageTpdo4(CobTpdo4 message);

private slots:
	void onFrameReceived(const CanBusFrame& frame);
	void onInfoMessageMustBeSent(const QString& message);
};



}





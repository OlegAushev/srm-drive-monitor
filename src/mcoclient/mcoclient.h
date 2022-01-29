#pragma once


#include "canbusdevice/canbusdevice.h"
#include "mcodef.h"
#include "tpdodef.h"
#include "rpdodef.h"
#include "objectdictionary/objectdictionary.h"
#include <array>

#include <QTimer>


namespace microcanopen {

class McoClient : public QObject
{
	Q_OBJECT
public:
	McoClient(NodeId clientNodeId, NodeId serverNodeId);

	void setTpdoPeriod(TpdoNum tpdoNum, int msec) { m_tpdoTimers[static_cast<size_t>(tpdoNum)]->setInterval(msec); }
	void sendOdReadRequest(const QString& odEntryName);
	void sendOdWriteRequest(const QString& odEntryName, CobSdoData data = {});
private:
	CanBusDevice m_canDevice;
	const unsigned int m_clientNodeId = 0;
	const unsigned int m_serverNodeId = 0;
	QTimer* m_statusTimer;

	std::array<QTimer*, 4> m_tpdoTimers;

signals:
	void infoMessageAvailable(QString message);

	void messageTpdo1Required();
	void messageTpdo2Required();
	void messageTpdo3Required();
	void messageTpdo4Required();

	void messageRpdoReceived(const QCanBusFrame& frame);
	void messageSdoReceived(const QCanBusFrame& frame);

public slots:
	void connectCanDevice(const QString& plugin, const QString& interface);
	void disconnectCanDevice();

	void startTpdoSending();
	void stopTpdoSending();

	void sendMessageTpdo1(CobTpdo1 message);
	void sendMessageTpdo2(CobTpdo2 message);
	void sendMessageTpdo3(CobTpdo3 message);
	void sendMessageTpdo4(CobTpdo4 message);

private slots:
	void onFrameReceived(const QCanBusFrame& frame);
	void onInfoMessageMustBeSent(const QString& message);
};



}





#pragma once


#include "canbusdevice/canbusdevice.h"
#include "tpdoservice/tpdoservice.h"
#include "rpdoservice/rpdoservice.h"
#include "sdoservice/sdoservice.h"
#include <array>

#include <QTimer>


namespace microcanopen {

class McoClient : public QObject
{
	Q_OBJECT
public:
	McoClient(NodeId clientNodeId, NodeId serverNodeId);

	TpdoService tpdoService;
	RpdoService rpdoService;
	SdoService sdoService;

private:
	CanBusDevice m_canDevice;
	const unsigned int m_clientNodeId = 0;
	const unsigned int m_serverNodeId = 0;
	QTimer* m_statusTimer;

signals:
	void infoMessageAvailable(QString message);

public slots:
	void connectCanDevice(const QString& plugin, const QString& interface);
	void disconnectCanDevice();
	void startTpdoService();
	void stopTpdoService();

private slots:
	void onFrameReceived(QCanBusFrame frame);
	void onInfoMessageReady(QString message);
};



}





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

	CanBusDevice canDevice;
	TpdoService tpdoService;
	RpdoService rpdoService;
	SdoService sdoService;
private:
	const unsigned int clientNodeId_ = 0;
	const unsigned int serverNodeId_ = 0;
	std::array<QTimer, 4> tpdoTimers_;
private slots:
	void onFrameReceived(QCanBusFrame frame);



};



}





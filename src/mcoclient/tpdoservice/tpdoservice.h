#pragma once


#include "../mcodef.h"
#include "canbusdevice/canbusdevice.h"
#include <array>
#include <QCanBusDevice>
#include <QTimer>

#include <QAction>
#include <QDoubleSpinBox>


namespace microcanopen {

/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART BEGIN ====================== */
/* ========================================================================== */
struct CobTpdo1
{
	uint16_t run : 1;
	uint32_t reserved1 : 31;
	uint16_t emergency_stop : 1;
	uint16_t reserved2 : 1;
	uint16_t braking : 1;
	uint32_t reserved3 : 29;
	CobTpdo1()
	{
		uint64_t rawMsg = 0;
		memcpy(this, &rawMsg, sizeof(CobTpdo1));
	}
	CobTpdo1(uint64_t rawMsg) { memcpy(this, &rawMsg, sizeof(CobTpdo1)); }
	uint64_t all() const
	{
		uint64_t data = 0;
		memcpy(&data, this, sizeof(CobTpdo1));
		return data;
	}
};

struct CobTpdo2
{
	int8_t torque_obsolete : 8;
	uint8_t reserved1 : 8;
	int16_t torque : 16;
	uint32_t reserved2 : 32;
	CobTpdo2()
	{
		uint64_t rawMsg = 0;
		memcpy(this, &rawMsg, sizeof(CobTpdo2));
	}
	CobTpdo2(uint64_t rawMsg) { memcpy(this, &rawMsg, sizeof(CobTpdo2)); }
	uint64_t all() const
	{
		uint64_t data = 0;
		memcpy(&data, this, sizeof(CobTpdo2));
		return data;
	}
};
/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART END ======================== */
/* ========================================================================== */

class TpdoService : public QObject
{
	Q_OBJECT
public:
	TpdoService(NodeId nodeId);
	void setPeriod(TpdoNum tpdoNum, int msec) { timers_[static_cast<size_t>(tpdoNum)]->setInterval(msec); }
	void start()
	{
		for (auto& timer : timers_)
		{
			if (timer->interval() != 0)
			{
				timer->start();
			}
		}
	}
	void stop()
	{
		for (auto& timer : timers_)
		{
			timer->stop();
		}
	}
private:
	const unsigned int nodeId_;
	std::array<QTimer*, 4> timers_;
	QTimer* timerTpdo1_;

private slots:
	void sendTpdo1();
	void sendTpdo2();
	void sendTpdo3();
	void sendTpdo4();
signals:
	void frameReady(QCanBusFrame frame);

/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART BEGIN ====================== */
/* ========================================================================== */
public:
	void assignTpdoSrcWidgets(QAction* buttonRun, QAction* buttonEmergencyStop, QDoubleSpinBox*spinBoxTorque)
	{
		buttonRun_ = buttonRun;
		buttonEmergencyStop_ = buttonEmergencyStop;
		spinBoxTorque_ = spinBoxTorque;
	}
private:
	QAction* buttonRun_ = nullptr;
	QAction* buttonEmergencyStop_ = nullptr;
	QDoubleSpinBox* spinBoxTorque_ = nullptr;
/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART END   ====================== */
/* ========================================================================== */



};




}

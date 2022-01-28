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
	uint16_t emergencyStop : 1;
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
	int8_t torqueObsolete : 8;
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

struct CobTpdo3
{
	uint64_t data;
};

struct CobTpdo4
{
	uint64_t data;
};

/* ========================================================================== */
/* =================== APPLICATION-SPECIFIC PART END ======================== */
/* ========================================================================== */

class TpdoService : public QObject
{
	Q_OBJECT
public:
	TpdoService(NodeId nodeId);
	void setPeriod(TpdoNum tpdoNum, int msec) { m_timers[static_cast<size_t>(tpdoNum)]->setInterval(msec); }
	void start()
	{
		for (auto& timer : m_timers)
		{
			if (timer->interval() != 0)
			{
				timer->start();
			}
		}
	}
	void stop()
	{
		for (auto& timer : m_timers)
		{
			timer->stop();
		}
	}
private:
	const unsigned int m_nodeId;
	std::array<QTimer*, 4> m_timers;

signals:
	void messageTpdo1Required();
	void messageTpdo2Required();
	void messageTpdo3Required();
	void messageTpdo4Required();
	void frameReady(QCanBusFrame frame);

public slots:
	void sendMessageTpdo1(CobTpdo1 message);
	void sendMessageTpdo2(CobTpdo2 message);
	void sendMessageTpdo3(CobTpdo3 message);
	void sendMessageTpdo4(CobTpdo4 message);
};




}

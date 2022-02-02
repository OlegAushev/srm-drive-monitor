#pragma once


#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <cstring>

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QProcess>
#include <QFileDialog>
#include <QTimer>


/**
 * @brief 
 * 
 */
class CanBusFrame
{
public:
	CanBusFrame() : m_id(0) {}
	CanBusFrame(quint32 identifier, const QByteArray &data)
		: m_id(identifier)
		, m_load(data)
	{}

	quint32 frameId() const { return m_id; }
	void setFrameId(quint32 newFrameId)
	{
		if (newFrameId > 0x7FF)
		{
			return;
		}
		m_id = newFrameId;
	}

	QByteArray payload() const { return m_load; }
	void setPayload(const QByteArray &data)
	{
		if (data.size() > 8)
		{
			return;
		}
		m_load = data;
	}
private:
	canid_t m_id;
	QByteArray m_load;	
};

/**
 * @brief 
 * 
 */
class CanSocketDevice : public QObject
{
	Q_OBJECT
public:
	CanSocketDevice();
	~CanSocketDevice();
	QString busStatus() { return {}; }

private:
	QString m_interface;
	int m_socket;
	ifreq m_ifr;
	sockaddr_can m_addr;

	QTimer* m_recvTimer;
	const int RECV_PERIOD = 2;

	QString findConnectionScript();
	int executeConnectionScript(const QString& scriptPath);

signals:
	void frameAvailable(const CanBusFrame& frame);
	void statusMessageAvailable(const QString& message);

public slots:
	void connectDevice(const QString& interface);
	void disconnectDevice();

	void sendFrame(const CanBusFrame& frame)
	{
		can_frame socketCanFrame;
		socketCanFrame.can_id = frame.frameId();
		socketCanFrame.len = frame.payload().size();
		memcpy(socketCanFrame.data, frame.payload().data(), frame.payload().size());

		if (write(m_socket, &socketCanFrame, sizeof(can_frame)) != sizeof(can_frame))
		{
			emit statusMessageAvailable("CAN sending error");
		}
	}

private slots:
	void recvFrame();

public:
	template <typename T>
	static inline CanBusFrame makeFrame(uint32_t id, T data)
	{
		static_assert(sizeof(T) <= 8, "CAN frame payload size must be <= 8 bytes");
		std::array<char, 8> buf;
		memcpy(buf.data(), &data, sizeof(T));
		QByteArray payload(buf.data(), sizeof(T));
		return CanBusFrame(id, payload);
	}

	template <typename T>
	static inline T mergeBytes(const QByteArray& bytes)
	{
		if (bytes.size() != sizeof(T))
		{
			return T();
		}
		T result;
		memcpy(&result, bytes.data(), sizeof(T));
		return result;
	}



};





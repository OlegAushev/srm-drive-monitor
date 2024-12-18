#pragma once

#include <memory>
#include <array>
#include <string>

#include <QByteArray>
#include <QProcess>
#include <QCanBus>
#include <QCanBusDevice>
#include <QLabel>
#include <QFileDialog>


class CanBusDevice : public QObject
{
	Q_OBJECT
public:
	CanBusDevice();
	~CanBusDevice();
	QString busStatus() const;

private:
	QString m_plugin;
	QString m_interface;
	std::unique_ptr<QCanBusDevice> m_device;

	QString findConnectionScript(const QString& interface);
	int executeConnectionScript(const QString& scriptPath);

signals:
	void frameAvailable(const QCanBusFrame& frame);
	void statusMessageAvailable(const QString& message);

public slots:
	void connectDevice(const QString& plugin, const QString& interface);
	void disconnectDevice();
	void sendFrame(const QCanBusFrame& frame)
	{
		if (m_device)
		{
			m_device->writeFrame(frame);
		}
	}

private slots:
	void onFrameReceived();

public:
	template <typename T>
	static inline QCanBusFrame makeFrame(uint32_t id, T data)
	{
		static_assert(sizeof(T) <= 8, "CAN frame payload size must be <= 8 bytes");
		std::array<char, 8> buf;
		memcpy(buf.data(), &data, sizeof(T));
		QByteArray payload(buf.data(), sizeof(T));
		return QCanBusFrame(id, payload);
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
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
	enum class Status
	{
		DISCONNECTED,
		CONNECTED,
		DISCONNECTION_ERROR,
		CONNECTION_ERROR,
		SCRIPT_NOT_FOUND
	};

private:
	QString plugin_;
	QString interface_;
	std::unique_ptr<QCanBusDevice> device_;

	QString findConnectionScript(QString interface);
	int executeConnectionScript(QString scriptPath);

public:
	CanBusDevice();
	Status connectDevice(QString plugin, QString interface);
	Status disconnectDevice();

private slots:
	void onFrameReceived();

public slots:
	void sendFrame(QCanBusFrame frame)
	{
		if (device_)
		{
			device_->writeFrame(frame);
		}
	}

signals:
	void frameAvailable(QCanBusFrame frame);
	void statusMessageAvailable(QString message);

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
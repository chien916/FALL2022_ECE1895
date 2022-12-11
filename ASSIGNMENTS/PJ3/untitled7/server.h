#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QPointer>
#include <QMetaEnum>
#include <QDebug>
#include <QtBluetooth>
#if defined(Q_OS_ANDROID)
#include <QTiltSensor>
#endif
//#include <QBluetoothServiceDiscoveryAgent>
//#include <QBluetoothLocalDevice>
//#include <QBluetoothServer>
#include <QtSensors>
class Server: public QObject {
	Q_OBJECT
  public:
	Server(const QString& role, QObject * debugger, QObject *parent = nullptr);
  private:
	QPoint point;
	QPointer<QBluetoothSocket> socket;
	//FOR SERVERS (COMPUTER/CURSOR RECEIVER)
	QString deviceName = "QYH_TILT_CTRL";
	QString targetAddress = "9C:BC:F0:CF:32:2F";
	QVector<QBluetoothAddress> availbleDevices;
	QPointer<QCursor> cursor;
	//FOR CLIENTS (PHONE/TILTER)
	QPointer<QTiltSensor> tileSensor;
	// QObject interface
  protected:
	void timerEvent(QTimerEvent *event) override final;
  Q_SIGNALS:
	void disp(const QString msg);
};


inline Server::Server(const QString& role, QObject * debugger, QObject *parent) : QObject(parent) {
	QObject::connect(this, &Server::disp, [debugger](const QString msg) {
		QMetaObject::invokeMethod(debugger, "disp", Q_ARG(QVariant, QVariant::fromValue(msg)));
	});

	QBluetoothLocalDevice* localDev = new QBluetoothLocalDevice(this);
	QObject::connect(localDev, &QBluetoothLocalDevice::hostModeStateChanged, this, [this](QBluetoothLocalDevice::HostMode state) {
		emit disp( "-> NEW HOST MODE " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothLocalDevice::HostMode>().valueToKey(state)));
	});;
	emit disp("-> LOCAL DEVICE " + localDev->address().toString());
	localDev->setObjectName(deviceName);
	emit disp("-> LOCAL HOST " + localDev->name());
	Q_ASSERT(localDev->isValid());
	localDev->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
	if(role == "client") {
		QBluetoothDeviceDiscoveryAgent* deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
		QObject::connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
		[this](const QBluetoothDeviceInfo & info) {
			emit disp("-> FOUND DEVICE " + info.address().toString() + " " + info.name());
			availbleDevices.push_front(info.address());
		});
		QObject::connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this,
		[this]() {
			if(availbleDevices.lastIndexOf(QBluetoothAddress(targetAddress)) == -1)
				emit disp("-> NO DEVICE MATCHES TARGET ADDRESS ");
			else {
				socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
				QObject::connect(socket, &QBluetoothSocket::connected, this, [this]() {
					emit disp("-> RX SOCKET CONNECTED ");
				});
				QObject::connect(socket, &QBluetoothSocket::disconnected, this, [this]() {
					emit disp("-> RX SOCKET DISCONNECTED ");
				});
				QObject::connect(socket, static_cast <void(QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error), this, [this](QBluetoothSocket::SocketError error) {
					emit disp("-> RX SOCKET ERROR " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketError>().valueToKey(error)));
				});
				QObject::connect(socket, &QBluetoothSocket::stateChanged, this, [this](QBluetoothSocket::SocketState state) {
					emit disp("-> RX SOCKET STATE CHANGED " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketState>().valueToKey(state)));
				});
//				QObject::connect(socket, &QBluetoothSocket::rea, this, [this](QBluetoothSocket::SocketState state) {
//					emit disp("-> SOCKET STATE CHANGED " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketState>().valueToKey(state)));
//				});
				QObject::connect(socket, &QBluetoothSocket::readyRead, [this]() {
					QString dataRead = QString::fromUtf8(socket->readAll());
					dataRead.truncate(dataRead.indexOf('|'));
					emit disp("-> RX SOCKET RECEIVED " + dataRead);
				});
				socket->connectToService(QBluetoothAddress(targetAddress), QBluetoothUuid::SerialPort);
			}
		});
		deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(10000);
		deviceDiscoveryAgent->start();

//		QBluetoothServiceDiscoveryAgent* discoveryAgent = new QBluetoothServiceDiscoveryAgent(this);
//		emit disp("-> START AS CLIENT ");
//		connect(discoveryAgent, &QBluetoothServiceDiscoveryAgent::serviceDiscovered, this, [this](const QBluetoothServiceInfo & info) {
//			emit disp("-> FOUND SERVICE " + info.serviceName());
//		});
//		connect(discoveryAgent, static_cast<void(QBluetoothServiceDiscoveryAgent::*)(QBluetoothServiceDiscoveryAgent::Error)>(&QBluetoothServiceDiscoveryAgent::error), this, [this](QBluetoothServiceDiscoveryAgent::Error error) {
//			emit disp("-> ERROR SERVICE " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothServiceDiscoveryAgent::Error>().valueToKey(error)));
//		});
//		connect(discoveryAgent, &QBluetoothServiceDiscoveryAgent::finished, this, [this]() {
//			emit disp("-> FINISHED SERVICE "  );
//		});


////		qInfo() << discoveryAgent->remoteAddress().toString();
//		discoveryAgent->start(QBluetoothServiceDiscoveryAgent::DiscoveryMode::FullDiscovery);
	} else if(role == "server") {


		QBluetoothServer* server = new QBluetoothServer(QBluetoothServiceInfo::Protocol::RfcommProtocol, this);
		emit disp("-> START AS SERVER")  ;
		QObject::connect(server, &QBluetoothServer::newConnection, this, [this, server]() {
			socket = server->nextPendingConnection();
			emit disp("-> TX SOCKET CONNECTED " + socket->peerAddress().toString());

			//TILT SENSOR CONFIG
			tileSensor = new QTiltSensor(this);
			tileSensor->setDataRate(50);
			//		tileSensor->setSkipDuplicates(true);
			QObject::connect(tileSensor, &QTiltSensor::readingChanged, this, [this]() {
				qreal x = tileSensor->reading()->xRotation();
				qreal y = tileSensor->reading()->yRotation();
				QString dataWrite = "X_" + QString::number(x) + "_Y_" + QString::number(y) + "|";
				socket->write(dataWrite.toLocal8Bit());
				emit disp("-> RX SOCKET SENT " + dataWrite);
			});

			QObject::connect(tileSensor, &QTiltSensor::sensorError, this, [this](int error) {
				emit disp("-> TILT ERROR " + QString::number(error) );
			});

			tileSensor->start();

		});
		QObject::connect(server, static_cast<void(QBluetoothServer::*)(QBluetoothServer::Error)>(&QBluetoothServer::error), this, [this](QBluetoothServer::Error error) {
			emit disp("-> SERVER ERROR " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothServer::Error>().valueToKey(error))  );
		});

		QBluetoothServiceInfo serviceInfo = server->listen(QBluetoothUuid::SerialPort, "TILTMOUSE");
		Q_ASSERT(serviceInfo.isValid());
		emit disp("-> SERVER LISTENING ADDRESS "  + server->serverAddress().toString());
		emit disp("-> SERVER LISTENING PORT "  + QString::number(server->serverPort()));
		emit disp("-> SERVER LISTENING STATUS " + QString::number(server->isListening()));
	}
}

inline void Server::timerEvent(QTimerEvent *event) {

}


#endif // SERVER_H

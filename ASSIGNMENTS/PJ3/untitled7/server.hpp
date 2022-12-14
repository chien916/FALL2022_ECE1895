#ifndef SERVER_HPP
#define SERVER_HPP
#include <QCursor>
#include <QObject>
#include <QPointer>
#include <QMetaEnum>
#include <QDebug>
#include <QtBluetooth>
#include <QScreen>
#include <QGuiApplication>
#include <QtQml>
#if defined(Q_OS_ANDROID)
#include <QTiltSensor>
#endif
#include <QtSensors>
class Server: public QObject {
	Q_OBJECT

  public:
	Server(QObject *parent = nullptr);
	void setQmlObjects(QObject * rootObject);
	enum Role {UndefinedRole, ServerRole, ClientRole};
	Q_ENUM(Role)
  private:
	//FOR BOTH:
	QMap<QString, QObject*> qmlObjects;
	Role role = UndefinedRole;
	QPointer<QBluetoothSocket> socket;
	void unsetRole();
	//FOR SERVER-LISTENER (COMPUTER/CURSOR RECEIVER)

	void setRoleAsServer();

	QPointer<QBluetoothDeviceDiscoveryAgent> deviceDiscoveryAgent;
	QList<QString> availableDevices;

	QPointer<QBluetoothServer> server;
	QString targetAddress = "9C:BC:F0:CF:32:2F";

	QList<QScreen*> availableScreens;
	int currentScreenIndex = -1;

	QCursor cursor = QCursor();
	QList<QPair<qreal, qreal>> coordinateCache;
	QPair<qreal, qreal> averagedCoordinate;
	int cacheSize = 50;

	//FOR CLIENT-BROADCASTER (PHONE/TILTER)
	void setRoleAsClient();

	QPointer<QTiltSensor> tileSensor;
	qreal maxAngle = 45.0;

	// QObject interface
  signals:
	void disp(const QString msg);
  public slots:
	void execute(const QString& cmd);
};

inline Server::Server( QObject *parent) {
	availableScreens = QGuiApplication::screens();
	currentScreenIndex = availableScreens.empty() ? -1 : 0;
	//initialize bluetooth socket - for both client and server
	socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
	QObject::connect(socket, &QBluetoothSocket::disconnected, this, [this]() {
		emit disp("soc disconnected " );
	});
	QObject::connect(socket, &QBluetoothSocket::connected, this, [this]() {
		emit disp("soc connected ");
	});
	QObject::connect(socket, static_cast <void(QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error), this, [this](QBluetoothSocket::SocketError error) {
		emit disp("soc error " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketError>().valueToKey(error)));
	});
	QObject::connect(socket, &QBluetoothSocket::stateChanged, this, [this](QBluetoothSocket::SocketState state) {
		emit disp("soc state changed " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketState>().valueToKey(state)));
	});
	QObject::connect(socket, &QBluetoothSocket::readyRead, this, [this]() {
		emit disp("soc received " );
		QString dataRead = QString::fromUtf8(socket->readAll());
		dataRead.truncate(dataRead.indexOf('|'));
		emit disp("soc received " + dataRead);
		emit execute(dataRead);
	});

	//initialize command handler - for both client and server
}

inline void Server::setQmlObjects(QObject *rootObject) {
	//initialize map for accessing my qml components
	qmlObjects.insert("MyBase", rootObject->findChild<QObject*>("root_myBase"));
	qmlObjects.insert("MyDebugger", rootObject->findChild<QObject*>("root_myDebugger"));
//	qmlObjects.insert("MyDeviceList", rootObject->findChild<QObject*>("root_myDeviceList"));
	qmlObjects.insert("MyInterface", rootObject->findChild<QObject*>("root_myInterface"));
	foreach(QObject* it, qmlObjects.values()) {
		Q_ASSERT(it);//check if all qml objects have been located
	}
	QObject::connect(this, &Server::disp, this, [this](const QString msg) {
		QMetaObject::invokeMethod(qmlObjects.value("MyDebugger"), "disp", Q_ARG(QVariant, QVariant::fromValue("-> " + msg.toUpper())));
	});
	emit disp("debugger connected to core");
}

inline void Server::unsetRole() {

	QPointer<QBluetoothSocket> socket;
	void unsetRole();
	//FOR SERVER-LISTENER (COMPUTER/CURSOR RECEIVER)

	void setRoleAsServer();

	QPointer<QBluetoothDeviceDiscoveryAgent> deviceDiscoveryAgent;
	QList<QString> availableDevices;

	QPointer<QBluetoothServer> server;
	QString targetAddress = "9C:BC:F0:CF:32:2F";

	QList<QScreen*> availableScreens;

	coordinateCache.clear();

	delete tileSensor;
	role = UndefinedRole;

}

inline void Server::setRoleAsServer() {
	//initializing bluetooth server - for server only
	server = new QBluetoothServer(QBluetoothServiceInfo::Protocol::RfcommProtocol, this);

	//initializing tilt sensor - for server only
	tileSensor = new QTiltSensor(this);

	QObject::connect(server, static_cast<void(QBluetoothServer::*)(QBluetoothServer::Error)>(&QBluetoothServer::error), this, [this](QBluetoothServer::Error error) {
		emit disp("server error " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothServer::Error>().valueToKey(error))  );
	});
	QObject::connect(server, &QBluetoothServer::newConnection, this, [this]() {
		socket = server->nextPendingConnection();
		emit disp("server socket connnected " + socket->peerAddress().toString());
		QObject::connect(tileSensor, &QTiltSensor::readingChanged, this, [this]() {
			qreal x = tileSensor->reading()->xRotation();
			qreal y = tileSensor->reading()->yRotation();
			//TO-DO round number here
			QString dataWrite = "X_" + QString::number(x) + "_Y_" + QString::number(y) + "|";
			socket->write(dataWrite.toLocal8Bit());
		});

		QObject::connect(tileSensor, &QTiltSensor::sensorError, this, [this](int error) {
			emit disp("sensor error " + QString::number(error) );
		});
		tileSensor->start();
	});
	QBluetoothServiceInfo serviceInfo = server->listen(QBluetoothUuid::SerialPort, "TILTMOUSE");
	role = ServerRole;
}

inline void Server::setRoleAsClient() {
	//initialize discovery agent - only for client
	deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
	QObject::connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, [this](const QBluetoothDeviceInfo & info) {
		emit disp("agent device discovered " + info.address().toString() + " " + info.name());
		availableDevices.push_front(info.address().toString());
	});
	QObject::connect(deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, [this]() {
		emit disp("agent finished " );
	});
//	QObject::connect(deviceDiscoveryAgent, static_cast<void(QBluetoothDeviceDiscoveryAgent::*)(QBluetoothDeviceDiscoveryAgent::Error)>(&QBluetoothDeviceDiscoveryAgent::error), this, [this](QBluetoothServiceDiscoveryAgent::Error error) {
//		emit disp("agent error " + QString::fromUtf8(QMetaEnum::fromType<QBluetoothDeviceDiscoveryAgent::Error>().valueToKey(error)));
//	});
	socket->connectToService(QBluetoothAddress(targetAddress), QBluetoothUuid::SerialPort);
	role = ClientRole;
}

inline void Server::execute(const QString &cmd) {

	QStringList splittedCmd = cmd.split('_');
	//X_[arg1]_Y_[arg2] :Set cursor to position
	if(splittedCmd.size() == 4 && splittedCmd.at(0) == "X" && splittedCmd.at(2) == "Y" && role == ClientRole) {
		bool ok = true;
		qreal x_t = splittedCmd.at(1).toFloat(&ok);
		qreal y_t = splittedCmd.at(3).toFloat(&ok);
		if(ok && 0 <= currentScreenIndex && currentScreenIndex < availableScreens.size()) {
			//ALGORITHMS TO DETERMINE POSITIONS OF CURSOR
			qreal xmin_t = -maxAngle, xmax_t = maxAngle, ymin_t = -maxAngle, ymax_t = maxAngle;
			int xmin_m_helper, xmax_m_helper, ymin_m_helper, ymax_m_helper;
			availableScreens.at(currentScreenIndex)->availableGeometry().getCoords(&xmin_m_helper, &ymin_m_helper, &xmax_m_helper, &ymax_m_helper);
			qreal xmin_m = static_cast<qreal>(xmin_m_helper), xmax_m = static_cast<qreal>(xmax_m_helper), ymin_m = static_cast<qreal>(ymin_m_helper), ymax_m = static_cast<qreal>(ymax_m_helper);
			qreal x_m = (y_t - ymin_t) * (xmax_m - xmin_m) / (ymax_t - ymin_t) + xmin_m;
			qreal y_m = (x_t - xmin_t) * (ymax_m - ymin_m) / (xmax_t - xmin_t) + ymin_m;
			//SIGNAL STABLIZING
			if(coordinateCache.size() < cacheSize) {
				averagedCoordinate.first += x_m;
				averagedCoordinate.second += y_m;
			} else if(coordinateCache.size() == cacheSize) {
				averagedCoordinate.first = averagedCoordinate.first / cacheSize;
				averagedCoordinate.second = averagedCoordinate.second / cacheSize;
			} else {
				QPair<qreal, qreal> popedCoordinate = coordinateCache.first();
				averagedCoordinate.first = (averagedCoordinate.first * cacheSize - popedCoordinate.first + x_m) / cacheSize;
				averagedCoordinate.second = (averagedCoordinate.second * cacheSize - popedCoordinate.second + y_m) / cacheSize;
				coordinateCache.pop_front();
			}
			coordinateCache.push_back(QPair<qreal, qreal>(x_m, y_m));
			cursor.setPos(qRound(averagedCoordinate.first), qRound(averagedCoordinate.second));
		}
	} //ROLE_[arg1] :Set to role (arg1:CLIENT/SERVER)
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "ROLE" && role == UndefinedRole) {
		if(splittedCmd.at(1) == "CLIENT") {
			setRoleAsClient();
		} else if(splittedCmd.at(1) == "SERVER") {
			setRoleAsServer();
		}
	} //ROLE_UNDEFINED :Set to role (arg1:UNDEFINED)
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "ROLE" && role != UndefinedRole) {
		if(splittedCmd.at(1) == "UNDEFINED") {
			unsetRole();
		}
	}
}



#endif // SERVER_H

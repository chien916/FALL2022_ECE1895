#ifndef SERVER_HPP
#define SERVER_HPP


//#include <QCursor>
//#include <QObject>
//#include <QPointer>
//#include <QMetaEnum>

#include <QtBluetooth>
#include <QGuiApplication>
#include <QtQml>
#include <QtGui>
#include <QtTest>
#include <QtCore>
#if defined(Q_OS_ANDROID)
#include <QTiltSensor>
#elif defined(Q_OS_WINDOWS)
#pragma comment(lib, "User32.lib")
#include <windows.h>
#endif
#include <QtSensors>

class Server: public QObject {
	//Meta-Object System Declarations
	Q_OBJECT
	Q_PROPERTY(qreal xRatio_m_q MEMBER xRatio_m NOTIFY onXYRatio_mChanged)
	Q_PROPERTY(qreal yRatio_m_q MEMBER yRatio_m NOTIFY onXYRatio_mChanged)
	Q_PROPERTY(ServiceRole role_q MEMBER role)
	Q_PROPERTY(QString currentMessage_q MEMBER currentMessage NOTIFY onCurrentMessageChanged)
	Q_PROPERTY(QString debuggerMessages_q MEMBER debuggerMessages NOTIFY onDebuggerMessagesChanged)
  public:
	//Constructor
	Server(QObject *parent = nullptr);
	//**********************************************
	//Service Role Management (Determined at compile-time)
	enum ServiceRole {ServerRole = 0, ClientRole = 1, UndefinedRole = 2};
	Q_ENUM(ServiceRole)
	ServiceRole role
#if defined(Q_OS_WIN)
		= ClientRole;
//		= ServerRole;
#elif defined(Q_OS_ANDROID)
		= ServerRole;
#else
		= UndefinedRole;
#endif

	//Current Device Serving State
//	QString isLoading = "false";


	//Displaying Messages To Two-Line DisplayBoard
	QString debuggerMessages = "-> wait for debugger to connect\n-> please be patient :)";//all messages displaying to debugger
	QString currentMessage;//formatted string synced to two-line display board
	QPair<int, QString> prioritzedMessage = QPair<int, QString>(0, "NOT IN SERVICE\nPLEASE WAIT");
	QList<QPair<int, QString>> regularMessages;
	void buildMessage(QString firstMessage, QString secondMessage, bool isPrioritized);
	int stayIterationConstant = 10;

	bool isInputtingAddress = false;
	int idleIterationConstant = 10;
	int idleIteration = 0;
	int idleIndex = 0;

	//Bluetooth Communication Socket
	QPointer<QBluetoothSocket> socket;
	//**********************************************
	//FOR CLIENT (COMPUTER)
	QString targetAddress = "9C:BC:F0:CF:32:2F";

	//Screen Management (Not configurable yet)
	QList<QScreen*> availableScreens;
	int currentScreenIndex = -1;

	//Cursor Control
	QCursor cursor = QCursor();
	QList<QPair<qreal, qreal>> coordinateCache;
	qreal averagedX_m = 0.0, averagedY_m = 0.0;
	qreal xRatio_m = 0.0, yRatio_m = 0.0;
	int cacheSize = 50;

	//**********************************************
	//FOR SERVER (SMARTPHONE)
	//Tilt Angles Sensoring
	QPointer<QBluetoothServer> server;
	QPointer<QTiltSensor> tiltSensor;
	QPair<qreal, qreal> maxAngles = QPair<qreal, qreal>(45.0, 80.0);
  signals:
	void onXYRatio_mChanged();
	void onCurrentMessageChanged();
	void onDebuggerMessagesChanged();
  public slots:
	void execute(const QString& cmd);
	void write(const QString& cmd);

	// QObject interface
  protected:
	void timerEvent(QTimerEvent *event) override final;
};

inline Server::Server(QObject *parent): QObject(parent) {
	if(role == ClientRole) {
		socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
//		QObject::connect(socket, &QBluetoothSocket::disconnected, this, [this]() {
////			buildMessage("socket disconnected", "", true);
//			//		unsetRole();
//		});
//		QObject::connect(socket, &QBluetoothSocket::connected, this, [this]() {
////			buildMessage("socket connected to", targetAddress, true);
//		});
		QObject::connect(socket, static_cast <void(QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error), this, [this](QBluetoothSocket::SocketError error) {
			buildMessage("socket error occured", QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketError>().valueToKey(error)), true);
			//		unsetRole();
		});
		QObject::connect(socket, &QBluetoothSocket::stateChanged, this, [this](QBluetoothSocket::SocketState state) {
			buildMessage("socket state changed", QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketState>().valueToKey(state)), true);
		});
		QObject::connect(socket, &QBluetoothSocket::readyRead, this, [this]() {
			QString dataRead = QString::fromUtf8(socket->readAll());
			dataRead.truncate(dataRead.indexOf('|'));
			execute(dataRead);
		});
	} else if(role == ServerRole) {
		server = new QBluetoothServer(QBluetoothServiceInfo::Protocol::RfcommProtocol, this);

		//initializing tilt sensor - for server only
		tiltSensor = new QTiltSensor(this);
		QObject::connect(server, static_cast<void(QBluetoothServer::*)(QBluetoothServer::Error)>(&QBluetoothServer::error), this, [this](QBluetoothServer::Error error) {
			buildMessage("server error occured", QString::fromUtf8(QMetaEnum::fromType<QBluetoothServer::Error>().valueToKey(error)), true);
		});
		QObject::connect(server, &QBluetoothServer::newConnection, this, [this]() {
			socket = server->nextPendingConnection();
//			QObject::connect(socket, &QBluetoothSocket::disconnected, this, [this]() {
////				buildMessage("socket disconnected", "", true);
//			});
			QObject::connect(socket, static_cast <void(QBluetoothSocket::*)(QBluetoothSocket::SocketError)>(&QBluetoothSocket::error), this, [this](QBluetoothSocket::SocketError error) {
				buildMessage("socket error occured", QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketError>().valueToKey(error)), true);
			});
			QObject::connect(socket, &QBluetoothSocket::stateChanged, this, [this](QBluetoothSocket::SocketState state) {
				buildMessage("socket state changed", QString::fromUtf8(QMetaEnum::fromType<QBluetoothSocket::SocketState>().valueToKey(state)), true);
			});
			buildMessage("socket oked conn req", "code " + socket->peerAddress().toString(), true);
			QObject::connect(tiltSensor, &QTiltSensor::readingChanged, this, [this]() {
				qreal x = 0.0, y = 0.0;
				if(tiltSensor->reading()) {
					x = tiltSensor->reading()->xRotation();
					y = tiltSensor->reading()->yRotation();
				}
				//TO-DO round number here
				QString dataWrite = "X_" + QString::number(x, 'g', 2) + "_Y_" + QString::number(y, 'g', 2) + "|";
				socket->write(dataWrite.toLocal8Bit());
			});
			QObject::connect(tiltSensor, &QTiltSensor::sensorError, this, [this](int error) {
				buildMessage("tilt sensor error", "code " + QString::number(error), true);
			});
		});
		tiltSensor->start();
	}


	availableScreens = QGuiApplication::screens();
	currentScreenIndex = availableScreens.empty() ? -1 : 0;
	Q_ASSERT(!availableScreens.empty());

}

inline void Server::buildMessage(QString firstMessage, QString secondMessage, bool isPrioritized) {
	Q_UNUSED(isPrioritized);
	//handle debugger messages
	QStringList splittedDebuggerMessages = debuggerMessages.split('\n');
	if(splittedDebuggerMessages.size() >= 30)
		splittedDebuggerMessages.pop_front();
	splittedDebuggerMessages.push_front("-> " + firstMessage + " " + secondMessage);
	QString msg = QString( firstMessage + "\n" + secondMessage);
	currentMessage = msg;
	prioritzedMessage = QPair<int, QString>(stayIterationConstant, msg);
	debuggerMessages  = splittedDebuggerMessages.join('\n');
	emit onCurrentMessageChanged();
	emit onDebuggerMessagesChanged();
}



inline void Server::execute(const QString &cmd) {
	QStringList splittedCmd = cmd.split('_');
	//X_[arg1]_Y_[arg2] :Set cursor to position
	if(splittedCmd.size() == 4 && splittedCmd.at(0) == "X" && splittedCmd.at(2) == "Y" && role == ClientRole) {
		bool ok = true;
		qreal x_t = (splittedCmd.at(1).toFloat(&ok));
		qreal y_t = (splittedCmd.at(3).toFloat(&ok));
		if(ok && 0 <= currentScreenIndex && currentScreenIndex < availableScreens.size()) {
			//ALGORITHMS TO DETERMINE POSITIONS OF CURSOR
			qreal xmin_t = -maxAngles.first, xmax_t = maxAngles.first, ymin_t = -maxAngles.second, ymax_t = maxAngles.second;
			int xmin_m_helper, xmax_m_helper, ymin_m_helper, ymax_m_helper;
			availableScreens.at(currentScreenIndex)->availableGeometry().getCoords(&xmin_m_helper, &ymin_m_helper, &xmax_m_helper, &ymax_m_helper);
			qreal xmin_m = static_cast<qreal>(xmin_m_helper), xmax_m = static_cast<qreal>(xmax_m_helper), ymin_m = static_cast<qreal>(ymin_m_helper), ymax_m = static_cast<qreal>(ymax_m_helper);
			qreal x_m = (y_t - ymin_t) * (xmax_m - xmin_m) / (ymax_t - ymin_t) + xmin_m;
			qreal y_m = (x_t - xmin_t) * (ymax_m - ymin_m) / (xmax_t - xmin_t) + ymin_m;
			xRatio_m = 0.5 - (y_t - ymin_t) / (ymax_t - ymin_t);
			yRatio_m = 0.5 - (x_t - xmin_t) / (xmax_t - xmin_t);
			emit onXYRatio_mChanged();
			//SIGNAL STABLIZING
			if(coordinateCache.size() < cacheSize) {
				averagedX_m += x_m;
				averagedY_m += y_m;
				coordinateCache.push_back(QPair<qreal, qreal>(x_m, y_m));
			} else if(coordinateCache.size() == cacheSize) {
				averagedX_m = averagedX_m / cacheSize;
				averagedY_m = averagedY_m / cacheSize;
				coordinateCache.push_back(QPair<qreal, qreal>(x_m, y_m));
			} else {
				QPair<qreal, qreal> popedCoordinate = coordinateCache.first();
				averagedX_m = (averagedX_m * cacheSize - popedCoordinate.first + x_m) / cacheSize;
				averagedY_m = (averagedY_m * cacheSize - popedCoordinate.second + y_m) / cacheSize;
				coordinateCache.pop_front();
				coordinateCache.push_back(QPair<qreal, qreal>(x_m, y_m));
			}
			if(abs(coordinateCache.last().first - averagedX_m) > 1.0 || abs(coordinateCache.last().second - averagedY_m) > 1.0)
				cursor.setPos(qRound(averagedX_m), qRound(averagedY_m));
		}
	} /*//ROLE :Set to role
	else if(splittedCmd.size() == 1 && splittedCmd.at(0) == "CONNECT") {
		if(role == ClientRole) {
			setRoleAsClient();
		} else if(role == ServerRole) {
			setRoleAsServer();
		}
	} //UNROLE:Set to unrole
	else if(splittedCmd.size() == 1 && splittedCmd.at(0) == "DISCONNECT" ) {
		unsetRole();
	} *///BUTTON_CL BUTTON_HO
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "BUTTON" && (splittedCmd.at(1) == "CL" || splittedCmd.at(1) == "HO")) {
		if(role == ClientRole) {
#if defined(Q_OS_WINDOWS)
			if(splittedCmd.at(1) == "CL")
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
			else if(splittedCmd.at(1) == "HO")
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 1, 1, 0, 0);
			buildMessage("received from client", cmd, false);
#endif
		} else if(role == ServerRole) {
			write(cmd + "|");
			buildMessage("send to client", cmd, true);
		}
	} //BUTTON_CA
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "BUTTON" && splittedCmd.at(1) == "CA") {
		if(!tiltSensor) {
			buildMessage("calibrate error", "powerr on first", true);
		} else {
			buildMessage("caliberation success", "calibrated", true);
			tiltSensor->calibrate();
		}

	} //BUTTON_PO
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "BUTTON" && splittedCmd.at(1) == "PO") {
//		if(socket || server || tiltSensor)
//			unsetRole();
		if(role == ClientRole) {
			buildMessage("powering on", "opening client port", true);
			if(socket->state() == QBluetoothSocket::UnconnectedState) {
				socket->connectToService(QBluetoothAddress(targetAddress), QBluetoothUuid::SerialPort);
			} else if(socket->state() == QBluetoothSocket::ConnectedState) {
				socket->abort();
				buildMessage("powering off", "closing client port", true);
			} else {
				buildMessage("powering error", "port is busy", true);
			}
		} else if(role == ServerRole) {
			if(!socket || socket->state() == QBluetoothSocket::UnconnectedState) {
				buildMessage("powering on", "opening server port", true);
				QBluetoothServiceInfo serviceInfo = server->listen(QBluetoothUuid::SerialPort, "TILTMOUSE");
				while(!(server && !server.isNull() && server->isListening())) {	}
				buildMessage("service connected to", "port number" + QString::number(server->serverPort()), true);
			} else if(socket->state() == QBluetoothSocket::ConnectedState) {
				socket->abort();
				server->close();
				buildMessage("powering off", "closing server port", true);
			} else {
				buildMessage("powering error", "port is busy", true);
			}
		}

	}//BUTTON_AD
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "BUTTON" && splittedCmd.at(1) == "AD") {
		if(server) buildMessage("set address error", "power off first", true);
		else {
			isInputtingAddress = true;
			targetAddress = "__-__-__-__-__-__";
			currentMessage = "set target address\n" + targetAddress;
			emit onCurrentMessageChanged();
		}
	}//BUTTON_OK
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "BUTTON" && splittedCmd.at(1) == "OK") {
		if(isInputtingAddress) {
			bool validFormat = true;
			for(int ind = 0; ind < targetAddress.size(); ++ind) {
				QChar it = targetAddress.at(ind);
				if((ind + 1) % 3 == 0) {
					Q_ASSERT(it == '-');
				} else {
					validFormat = (it == '_') ? false : validFormat;
				}
			}
			if(validFormat) {
				targetAddress = targetAddress.replace('-', ':');
				isInputtingAddress = false;
				buildMessage("set address success", targetAddress, true);
			}
		}
	}//BUTTON_[A-F]|[0-9]
	else if(splittedCmd.size() == 2 && splittedCmd.at(0) == "BUTTON" && splittedCmd.at(1).size() == 1) {
		if(isInputtingAddress) {
			qsizetype indexOfFirstUnderscore = targetAddress.indexOf('_');
			if(indexOfFirstUnderscore != -1) {
				targetAddress.replace(indexOfFirstUnderscore, 1, splittedCmd.at(1));
				currentMessage = "set target address\n" + targetAddress;
				emit onCurrentMessageChanged();
			}
		}
	}
}

inline void Server::write(const QString & cmd) {
	if(socket && socket->state() == QBluetoothSocket::ConnectedState && role == ServerRole) {
		QString dataToWrite = cmd;
		socket->write(dataToWrite.toLocal8Bit());
	}
}

inline void Server::timerEvent(QTimerEvent *event) {
	Q_UNUSED(event);
	//prioritized messages
//	if(isLoading == "true") {
//		currentMessage = "\nplease wait";
//		emit onCurrentMessageChanged();
//	}
	if(isInputtingAddress) {
		//DO NOTHING
	} else if(prioritzedMessage.first > 0) {
		--prioritzedMessage.first;
	}//regular messages
	/*else if(!regularMessages.isEmpty()) {
		if(regularMessages.first().first > 0)
			--regularMessages.first().first;
		else if(regularMessages.first().first == 0) {
			regularMessages.pop_front();
			currentMessage = regularMessages.first().second;
			emit onCurrentMessageChanged();
		}
	}*/ else {//idle messages
		QString idleMessage1, idleMessage2;
		if(0 <= idleIteration && idleIteration < 10) {
			if(socket == nullptr) {
				idleMessage1 = "socket disconnected ";
				idleMessage2 = " no connect request";
			} else if(socket->state() == QBluetoothSocket::ConnectedState) {
				idleMessage1 = role == ClientRole ? "socket pulling from" : "socket direct to";
				idleMessage2 = targetAddress;
			} else if(socket->state() == QBluetoothSocket::UnconnectedState) {
				idleMessage1 = "socket disconnected ";
				idleMessage2 = "click po to connect";
			} else {
				idleMessage1 = "socket is busy";
				idleMessage2 = "do not close socket";
			}
		} else if(10 <= idleIteration && idleIteration < 15) {
			if(idleIteration % 2 == 0) {
				idleMessage1 = "  bl gravity mouse  ";
				idleMessage2 = "   made by yinhao   ";
			} else {
				idleMessage1 = "";
				idleMessage2 = "";
			}
		} else if(15 <= idleIteration && idleIteration < 25) {
			if(role == ClientRole) {
				if(socket == nullptr) {
					idleMessage1 = "socket disconnected";
					idleMessage2 = "no connect request";
				} else if(socket->state() == QBluetoothSocket::ConnectedState) {
					idleMessage1 = role == ClientRole ? "socket pulling from" : "socket direct to";
					idleMessage2 = targetAddress;
				} else if(socket->state() == QBluetoothSocket::UnconnectedState) {
					idleMessage1 = "socket disconnected";
					idleMessage2 = "click po to connect";
				} else {
					idleMessage1 = "socket is busy";
					idleMessage2 = "do not close socket";
				}
			} else if(role == ServerRole) {
				idleMessage1 = server->isListening() ? "server listening" : "server not listening";
				idleMessage2 = tiltSensor->isActive() ? "sensor is operating" : "sensor not working";
			}
		} else if(25 <= idleIteration && idleIteration <= 35) {
			idleMessage1 = QDateTime::currentDateTime().toString("ddd MMMM d yyyy");
			idleMessage2 = QDateTime::currentDateTime().toString("      hh-mm-ss      ");
		}
		if(idleIteration >= 35) idleIteration =  0;
		else ++idleIteration;
		currentMessage = idleMessage1 + "\n" + idleMessage2;
		emit onCurrentMessageChanged();
	}
}


#endif // SERVER_H

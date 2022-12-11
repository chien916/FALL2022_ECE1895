#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP
#include <QObject>
#include <QPointer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
class NetworkManager: public QObject {
	Q_OBJECT
  public:
	NetworkManager(QObject *parent = nullptr);
	QPointer<QNetworkAccessManager> networkAccessManager;
};

#endif // NETWORKMANAGER_HPP


inline NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
	networkAccessManager = new QNetworkAccessManager(this);


}


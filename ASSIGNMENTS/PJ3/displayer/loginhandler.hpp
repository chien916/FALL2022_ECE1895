#ifndef LOGINHANDLER_HPP
#define LOGINHANDLER_HPP

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QPointer>
class LoginQmlHandler : public QObject {
	Q_OBJECT
  private:
	QPointer<QQuickItem> loginQmlRoot;
	enum PageType {Login, Signup};
	PageType pageType = Login;

  public:
	LoginQmlHandler(QQmlApplicationEngine* qmlApplicationEngine, QObject *parent = nullptr);
  signals:

  public slots:
	void changePageType();
	void submitForm();

};

inline LoginQmlHandler::LoginQmlHandler(QQmlApplicationEngine* qmlApplicationEngine, QObject *parent)
	: QObject{parent} {
	auto rootObjects = qmlApplicationEngine->rootObjects();
	loginQmlRoot = rootObjects.at(0)->findChild<QQuickItem*>("login_qml_root");
}

inline void LoginQmlHandler::changePageType() {

}

inline void LoginQmlHandler::submitForm() {

}


#endif // LOGINHANDLER_HPP

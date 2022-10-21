#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QObject>
#include <QQmlContext>
#include "myquickpainteditem.h"
#include "qtcommunicator.h"
#include "mygameserver.h"

int main(int argc, char *argv[]) {
	qmlRegisterType<MyQuickPaintedItem>("com.yinhao.mygameserver", 1, 0, "MyGameServer");
	qmlRegisterType<MyQuickPaintedItem>("com.yinhao.myquickpainteditem", 1, 0, "MyQuickPaintedItem");

	MyGameServer myGameServer{};
	QtCommunicator qtCommunicator{};

	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	const QUrl url(u"qrc:/qt_lib/main.qml"_qs);
	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreated,
		&app,
	[url](QObject * obj, const QUrl & objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);



	QQmlContext* a = engine.rootContext();
	a->setContextProperty("myGameServer", &myGameServer);
//	QtCommunicator<8, int, int> qtCommunicator = QtCommunicator<8, int, int>();
//	Communicator<8, int, int>* communicatorPointer = &qtCommunicator;
	MyQuickPaintedItem* myQuickPaintedItem = qobject_cast<MyQuickPaintedItem*>(engine.rootObjects().at(0)->findChild<QQuickPaintedItem*>("myQuickPaintedItem_radarScreen"));
	QQuickItem* rectangleRwr1Led = qobject_cast<QQuickItem*>(engine.rootObjects().at(0)->findChild<QQuickItem*>("rectangle_rwr1Led"));
	QQuickItem* rectangleRwr2Led = qobject_cast<QQuickItem*>(engine.rootObjects().at(0)->findChild<QQuickItem*>("rectangle_rwr1Led"));
	QQuickItem* rectangleBuzzer = qobject_cast<QQuickItem*>(engine.rootObjects().at(0)->findChild<QQuickItem*>("rectangle_buzzer"));


	qtCommunicator.setMyQuickPaintedItem(myQuickPaintedItem);
	qtCommunicator.setQQuickItemLeds(rectangleRwr1Led, rectangleRwr2Led, rectangleBuzzer);
	myGameServer.setCommunicator(&qtCommunicator);

	myGameServer.executeAneLoop();
	return  app.exec();

}

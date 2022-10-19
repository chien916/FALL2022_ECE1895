#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QObject>
#include "myquickpainteditem.h"
#include "qtplayable.h"
#include "qtcommunicator.h"


int main(int argc, char *argv[]) {
	qmlRegisterType<MyQuickPaintedItem>("com.yinhao.myquickpainteditem", 1, 0, "MyQuickPaintedItem");

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



	QtCommunicator<8, int, int> qtCommunicator = QtCommunicator<8, int, int>();
	Communicator<8, int, int>* communicatorPointer = &qtCommunicator;
	MyQuickPaintedItem* myQuickPaintedItem =
		qobject_cast<MyQuickPaintedItem*>
		(engine.rootObjects().at(0)
		 ->findChild<QQuickPaintedItem*>
		 ("myQuickPaintedItem_radarScreen"));
	return  app.exec();

}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QObject>
#include "myquickpainteditem.h"
#include "base/exception.h"

int main(int argc, char *argv[]) {
	qmlRegisterType<MyQuickPaintedItem>("com.yinhao.myquickpainteditem", 1, 0, "MyQuickPaintedItem");

	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	const QUrl url(u"qrc:/qt_lib/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
	&app, [url](QObject * obj, const QUrl & objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);


	return app.exec();
}

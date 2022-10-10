#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qpixelobject.h"


int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	const QUrl url(u"qrc:/library_qt/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);


	puts("s");


	return app.exec();
}

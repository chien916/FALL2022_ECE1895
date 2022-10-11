#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[]) {
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


	return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>
#include <QtQuick>
#include <server.hpp>
#if defined(Q_OS_ANDROID)
#include <QTiltSensor>
#include <QtAndroid>
#endif

int main(int argc, char *argv[]) {
//	qmlRegisterType<()

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
	&app, [url](QObject * obj, const QUrl & objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);

#ifdef Q_OS_ANDROID
	QStringList permissionList;
	permissionList.append("android.permission.BLUETOOTH_ADMIN");
	permissionList.append("android.permission.ACCESS_FINE_LOCATION");
	permissionList.append("android.permission.ACCESS_COARSE_LOCATION");
	QtAndroid::requestPermissionsSync(permissionList);
#endif

	/*int pingguo =*/ QFontDatabase::addApplicationFont(":/pingguo.ttf");
	/*int yahei =*/ QFontDatabase::addApplicationFont(":/yahei.ttf");
	QFontDatabase::addApplicationFont(":/seg.ttf");
//	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
//	QFont pingguoHeiti = QFont(family);
	Server myServer;

	engine.rootContext()->setContextProperty("MyServer", &myServer);
	engine.load(url);
//	myServer.setQmlObjects(engine.rootObjects().at(0));

	myServer.startTimer(700);
//	QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
//	myServer.execute("CONNECT");


	return app.exec();
}

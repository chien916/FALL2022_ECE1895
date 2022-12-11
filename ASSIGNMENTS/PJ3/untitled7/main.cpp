#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtCore>
#include <QtQuick>
#include <server.h>
#if defined(Q_OS_ANDROID)
#include <QTiltSensor>
#include <QtAndroid>
#endif

int main(int argc, char *argv[]) {
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
	engine.load(url);
	auto rootobjects =  engine.rootObjects();
	QObject * loader = engine.rootObjects().at(0)->findChild<QObject*>("loader_loader");
	QObject * debugger = qvariant_cast<QObject*>(QQmlProperty::read(loader, "item"));
	QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
#if defined(Q_OS_ANDROID)
	Server server("server", debugger);
#elif defined(Q_OS_WINDOWS)
	Server client("client", debugger);
#endif
	return app.exec();
}

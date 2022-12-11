#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QFontDatabase>
#include <QQuickItem>
#include <QTimer>
#include <QProcess>
#include <QtNetwork>
#include <filechooserqmlhandler.hpp>
#include <QCursor>
#include <cursorcontroller.h>
//void registerQmlHandler() {
//	qmlRegisterType<FileChooserQmlHandler>("com.yinhao.filechooserqmlhandler", 1, 0, "FileChooserQmlHandler");
//}

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

	int id = QFontDatabase::addApplicationFont(":/pingguo.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	QFont pingguoHeiti = QFont(family);




	// Set the cursor shape to an invisible shape.
	CursorController lc;
//	lc.startTimer(20);

	engine.load(url);



//	FileChooserQmlHandler fileUploader(&engine, nullptr);


	return app.exec();
}

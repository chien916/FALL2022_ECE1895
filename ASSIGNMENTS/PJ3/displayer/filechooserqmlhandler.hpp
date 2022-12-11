#ifndef FILECHOOSERQMLHANDLER_H
#define FILECHOOSERQMLHANDLER_H


#include <QObject>
#include <QPointer>
#include <QOAuth2AuthorizationCodeFlow>
#include <QtNetwork>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
class FileChooserQmlHandler : public QObject {
	Q_OBJECT
  private:
	QPointer <QQuickItem> quickItem;
//	QString scope = "https://www.googleapis.com/auth/devstorage.full_control";
//	QString clientId = "750239967040-9fm389v2iank9h0ql0ad60lem6467n2t.apps.googleusercontent.com";
//	QString clientSecret = "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";
//	QString responseMode = "query";
//	QString responseType = "json";
//	QUrl authorizeUrl = QUrl("https://accounts.google.com/o/oauth2/v2/auth");
//	QUrl authorizeTokenUrl = QUrl("https://accounts.google.com/o/oauth2/v2/token");
//	QUrl redirectUrl = QUrl("http://localhost");
//	quint16 port = 8080;
	QUrl url = QUrl("https://api.openai.com/v1/images/generations");
	QString myAccessToken = "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";
  public:
	QPointer<QNetworkAccessManager> networkAccessManager;

	explicit FileChooserQmlHandler(QQmlApplicationEngine* qmlApplicationEngine, QObject *parent = nullptr);

//  signals:
//	void onTokenGranted(QString accessToken);
};

inline FileChooserQmlHandler::FileChooserQmlHandler(QQmlApplicationEngine* qmlApplicationEngine, QObject *parent): QObject{parent} {
	//find qml
	auto rootObjects = qmlApplicationEngine->rootObjects();
	quickItem = rootObjects.at(0)->findChild<QQuickItem*>("root_fileChooser");

	if(networkAccessManager == false)
		networkAccessManager = new QNetworkAccessManager(this);
	//authenticate
	QNetworkRequest networkRequest = QNetworkRequest(url);
	networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
	networkRequest.setRawHeader("Authorization", "Bearer " + myAccessToken.toUtf8());
	networkRequest.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
	QJsonObject jsonObject;
	jsonObject.insert("model", "text-davinci-002");
	jsonObject.insert("prompt", "write me qt function to calculate fft");
	jsonObject.insert("temperature", 0.5);
	jsonObject.insert("top_p", 1);
	jsonObject.insert("frequency_penalty", 0);
	jsonObject.insert("presence_penalty", 0);
	jsonObject.insert("n", 1);
	jsonObject.insert("stream", true);
	jsonObject.insert("stop", "\n\n");





	Q_ASSERT(networkAccessManager);
	QPointer<QNetworkReply> networkReply = networkAccessManager->post(networkRequest, QJsonDocument(jsonObject).toJson());
	QObject::connect(networkReply, &QNetworkReply::readyRead, this, [networkReply, this]() {
		QByteArray html = networkReply->readAll();
		qInfo() << html;
		quickItem->setProperty("htmlContent", QString::fromUtf8(html));
	});

//	QScopedPointer<QOAuth2AuthorizationCodeFlow> oauth2(new QOAuth2AuthorizationCodeFlow);
//	oauth2->setScope(scope);
//	QObject::connect(oauth2.data(), &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, [this](const QUrl & url) {
//		qInfo() << url;
//	});
//	QObject::connect(oauth2.data(), &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);


//	oauth2->setAuthorizationUrl(authorizeUrl);
//	oauth2->setClientIdentifier(clientId);
//	oauth2->setAccessTokenUrl(authorizeTokenUrl);
//	oauth2->setClientIdentifierSharedKey(clientSecret);

//	QScopedPointer<QOAuthHttpServerReplyHandler> replyHandler(new QOAuthHttpServerReplyHandler(port, this));
//	oauth2->setReplyHandler(replyHandler.data());


//	QObject::connect(oauth2.data(), &QOAuth2AuthorizationCodeFlow::granted, []() {
//		qInfo() << "granted";
//	});
//	oauth2->grant();

}

#endif // FILECHOOSERQMLHANDLER_H

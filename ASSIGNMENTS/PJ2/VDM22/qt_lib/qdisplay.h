#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QObject>
#include <QDebug>
#include <QImage>

#include "display.h"
class QDisplay: public Display, QObject {
	Q_OBJECT
  private:
	QImage qImage{256, 256, QImage::Format_Mono};
  public:
	QDisplay(QObject *parent): QObject(parent) {}
	void message(char *msg) const Q_DECL_OVERRIDE {
		qDebug("%s", msg);
	};
	void flash(Pixel &pixel) const Q_DECL_OVERRIDE {

	};
  signals:

  public slots:

};

#endif // QDISPLAY_H

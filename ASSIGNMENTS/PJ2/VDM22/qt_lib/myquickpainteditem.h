#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QObject>
#include <QDebug>
#include <QImage>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QRandomGenerator>
#include "pixel.h"

class MyQuickPaintedItem:  public QQuickPaintedItem {
	Q_OBJECT
  public:
	MyQuickPaintedItem(QQuickItem *parent = nullptr);
	void paint(QPainter *painter) override;
	void clearBuffer();
	void uploadBufferToScreen();
	void uploadPixelToBuffer(Pixel &pixel);
  private:
	QImage imageToBePrinted{256, 256, QImage::Format_Mono};
	// Display interface
  public:
	void message(char *msg) const ;
	void flash()  ;
	Q_INVOKABLE void helloWorld();
};

inline void MyQuickPaintedItem::message(char *msg) const {
	qDebug("msg");
}

inline void MyQuickPaintedItem::uploadPixelToBuffer(Pixel &pixel)  {
	imageToBePrinted.setPixel(pixel.getX(), pixel.getY(), 1U);
}

inline void MyQuickPaintedItem::helloWorld() {
	clearBuffer();
	imageToBePrinted.fill(1);//把所有像素点设置为低电平
	update();
}

inline MyQuickPaintedItem::MyQuickPaintedItem(QQuickItem *parent) : QQuickPaintedItem(parent) {
	clearBuffer();
}

inline void MyQuickPaintedItem::paint(QPainter *painter) {
	painter->setClipping(true);
	painter->drawImage(0, 0, imageToBePrinted);
}

inline void MyQuickPaintedItem::clearBuffer() {
	imageToBePrinted.fill(0);//把所有像素点设置为低电平
	update();
}



#endif // QDISPLAY_H

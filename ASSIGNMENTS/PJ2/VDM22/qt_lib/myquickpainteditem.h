#ifndef QDISPLAY_H
#define QDISPLAY_H

#include <QObject>
#include <QDebug>
#include <QImage>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QRandomGenerator>
#include "displayable.h"

class MyQuickPaintedItem:  public QQuickPaintedItem {
	Q_OBJECT
  public:
	MyQuickPaintedItem(QQuickItem *parent = nullptr);
	void paint(QPainter *painter) override;
	void clearBuffer();
	void uploadBufferToScreen();
	template <unsigned int P, typename T>
	void uploadDisplayableToBuffer(Displayable<P, T> &displayable);
  private:
	QImage imageToBePrinted{256, 256, QImage::Format_Mono};

	// Display interface
  public:
	void message(char *msg) const ;
	Q_INVOKABLE void helloWorld();
};

template<unsigned int P, typename T>
inline void MyQuickPaintedItem::uploadDisplayableToBuffer(Displayable<P, T> &displayable) {
	for(struct Displayable<P, T>::Pixel it : displayable.pixelArray) {
		int convertedX = static_cast<int>(it.x) + 128L;
		int convertedY = -static_cast<int>(it.y) + 128L;
		bool convertedXInRange = convertedX >= 0L && convertedX <= imageToBePrinted.width();
		bool convertedYInRange = convertedY >= 0L && convertedY <= imageToBePrinted.height();
		if(convertedXInRange && convertedYInRange && displayable.visibility) {
			imageToBePrinted.setPixel(convertedX, convertedY, 1U);
		}
	}
	update();
}
inline void MyQuickPaintedItem::message(char *msg) const {
	qDebug("msg");
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

inline void MyQuickPaintedItem::uploadBufferToScreen() {
	update();
}





#endif // QDISPLAY_H

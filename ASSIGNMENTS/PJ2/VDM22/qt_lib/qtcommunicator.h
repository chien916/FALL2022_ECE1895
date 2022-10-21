#ifndef QTCOMMUNICATOR_H
#define QTCOMMUNICATOR_H
#include "communicator.h"
#include <QDebug>
#include <QString>
#include <iostream>
#include <QPointer>
#include <QQuickItem>
#include "myquickpainteditem.h"

#define QT_TEMPALTE_B 8
#define QT_TEMPALTE_T int
#define QT_TEMPALTE_D float
#define QT_TEMPALTE_A float

#define QT_TEMPALTE_PARAM QT_TEMPALTE_B,QT_TEMPALTE_T,QT_TEMPALTE_D,QT_TEMPALTE_A

class QtCommunicator: public Communicator<QT_TEMPALTE_PARAM> {
  private:
	QPointer<MyQuickPaintedItem> myQuickPaintedItemPointer{nullptr};
	QPointer<QQuickItem> rectangleRwr1Led{nullptr}, rectangleRwr2Led{nullptr}, rectangleBuzzer{nullptr};
	void platformSpecificPrint(char *messageText) override final {
		qInfo() << messageText;
	}
	void platformSpecificExit() override final {
		exit(1);
	}

  public:
	QVector<bool> buttonIntermediateBuffer = QVector<bool>(4, false);
	QVector<qreal> sliderIntermediateBuffer = QVector<qreal>(2, 0.0);
	bool setMyQuickPaintedItem(MyQuickPaintedItem* myQuickPaintedItemPointer);
	bool setQQuickItemLeds(QQuickItem* rectangleRwr1Led, QQuickItem* rectangleRwr2Led, QQuickItem* rectangleBuzzer);
	bool platformSpecificUpdateBufferToPins() override final ;
	bool platformSpecificUpdatePinsToBuffer() override final ;
	bool platformSpecificFlashPixelToScreen(const QT_TEMPALTE_T x, const QT_TEMPALTE_T y) override final ;

};

inline bool QtCommunicator::setMyQuickPaintedItem(MyQuickPaintedItem *myQuickPaintedItemPointer) {
	if(myQuickPaintedItemPointer == nullptr) return false;
	this->myQuickPaintedItemPointer = myQuickPaintedItemPointer;
	if(this->myQuickPaintedItemPointer == nullptr) return false;
	return true;
}

inline bool QtCommunicator::setQQuickItemLeds(QQuickItem *rectangleRwr1Led, QQuickItem *rectangleRwr2Led, QQuickItem *rectangleBuzzer) {
	if(rectangleRwr1Led == nullptr) return false;
	if(rectangleRwr2Led == nullptr) return false;
	if(rectangleBuzzer == nullptr) return false;
	this->rectangleRwr1Led = rectangleRwr1Led;
	this->rectangleRwr2Led = rectangleRwr2Led;
	this->rectangleBuzzer = rectangleBuzzer;
	if(this->rectangleRwr1Led == nullptr) return false;
	if(this->rectangleRwr2Led == nullptr) return false;
	if(this->rectangleBuzzer == nullptr) return false;
	return true;
}

inline bool QtCommunicator::platformSpecificUpdateBufferToPins() {
	if(this->rectangleRwr1Led == nullptr) return false;
	if(this->rectangleRwr2Led == nullptr) return false;
	if(this->rectangleBuzzer == nullptr) return false;
	try {
		this->rectangleRwr1Led->setProperty("color", this->digitalOutputRwr1LedBuffer ? QColor(Qt::red) : QColor(Qt::black));
		this->rectangleRwr2Led->setProperty("color", this->digitalOutputRwr2LedBuffer ? QColor(Qt::red) : QColor(Qt::black));
		this->rectangleBuzzer->setProperty("color", this->digitalOutputBuzzerBuffer ? QColor(Qt::red) : QColor(Qt::black));
		//To-Do Analog output not implemented
	} catch(std::exception& e) {
		return false;
	}
	return true;
}

inline bool QtCommunicator::platformSpecificUpdatePinsToBuffer() {
	this->digitalInputLaunchButtonBuffer = buttonIntermediateBuffer.at(0);
	this->digitalInputCounterMeasureBuffer = buttonIntermediateBuffer.at(1);
	this->digitalInputPiperUpButtonBuffer = buttonIntermediateBuffer.at(2);
	this->digitalInputPiperDownButtonBuffer = buttonIntermediateBuffer.at(3);
	return true;
}

inline bool QtCommunicator::platformSpecificFlashPixelToScreen(const QT_TEMPALTE_T x, const QT_TEMPALTE_T y) {
	if(this->myQuickPaintedItemPointer == nullptr) return false;
	bool status{true};
	status &= myQuickPaintedItemPointer->displayPixelOnScreen(static_cast<int>(x), static_cast<int>(y));
	return status;
}
#endif // QTCOMMUNICATOR_H


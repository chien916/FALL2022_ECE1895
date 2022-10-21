#ifndef MYGAMESERVER_H
#define MYGAMESERVER_H

#include <QObject>
#include <QQmlApplicationEngine>

#include <playable.h>
#include <qtcommunicator.h>


class MyGameServer: public QObject {
	Q_OBJECT
  private:
	Playable<QT_TEMPALTE_PARAM> playable;
  public:
	Q_INVOKABLE bool onButtonValueChanged(QString buttonId, bool value);
	Q_INVOKABLE bool onSliderValueChanged(QString sliderId, qreal value);
	MyGameServer(QObject *parent = nullptr);
	bool setCommunicator(Communicator<QT_TEMPALTE_PARAM> *communicatorPointer);
	bool executeAneLoop();
};

inline bool MyGameServer::onButtonValueChanged(QString buttonId, bool value) {
	if(playable.communicatorPointer == nullptr) return false;
	bool status{true};
	if(buttonId == "button_launchButton") {
		dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer[0] = value;
		qInfo() << "button_launchButton=" << dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer.at(0) ;
	} else if(buttonId == "button_counterMeasureButton") {
		dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer[1] = value;
		qInfo() << "button_counterMeasureButton=" << dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer.at(1) ;
	} else if(buttonId == "button_piperUpButton") {
		dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer[2] = value;
		qInfo() << "button_piperUpButton=" << dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer.at(2) ;
	} else if(buttonId == "button_piperDownButton") {
		dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer[3] = value;
		qInfo() << "button_piperDownButton=" << dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->buttonIntermediateBuffer.at(3) ;
	} else
		status = false;
	return status;
}

inline bool MyGameServer::onSliderValueChanged(QString sliderId, qreal value) {
	if(playable.communicatorPointer == nullptr) return false;
	bool status{true};
	if(sliderId == "slider_stickX") {
		dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->sliderIntermediateBuffer[0] = value;
		qInfo() << "analogInputStickXAxisBuffer=" << dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->sliderIntermediateBuffer.at(0);
	} else if(sliderId == "slider_stickY") {
		dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->sliderIntermediateBuffer[1] = value;
		qInfo() << "analogInputStickYAxisBuffer=" << dynamic_cast<QtCommunicator*>(playable.communicatorPointer)->sliderIntermediateBuffer.at(1);
	} else
		status = false;
	playable.communicatorPointer->platformSpecificUpdateBufferToPins();
	return status;
}

inline MyGameServer::MyGameServer(QObject *parent): QObject(parent) {

}

inline bool MyGameServer::setCommunicator(Communicator<QT_TEMPALTE_PARAM> *communicatorPointer) {
	if(communicatorPointer == nullptr) return false;
	this->playable.setCommunicator(communicatorPointer);
	return true;
}

inline bool MyGameServer::executeAneLoop() {
	bool status{true};
	status &= playable.executeAndLoop();
	return status;
}


#endif // MYGAMESERVER_H

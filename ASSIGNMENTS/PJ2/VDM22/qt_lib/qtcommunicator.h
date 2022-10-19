#ifndef QTCOMMUNICATOR_H
#define QTCOMMUNICATOR_H
#include "communicator.h"
#include <QDebug>
#include <QString>
#include <iostream>
template <unsigned char B, typename D, typename A>
class QtCommunicator: public Communicator<B, D, A> {


	// Communicator interface
private:
	void platformSpecificPrint(char *messageText) override final
	{
		qDebug(messageText);
	}
	void platformSpecificExit() override final
	{
		exit(1);
	}

public:
	void platformSpecificUpdateBufferToPins() override final
	{
	}
	void platformSpecificUpdatePinsToBuffer() override final
	{
	}
};
#endif // QTCOMMUNICATOR_H

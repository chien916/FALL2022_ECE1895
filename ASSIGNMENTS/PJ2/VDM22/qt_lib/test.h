#ifndef TEST_H
#define TEST_H

#include "gameimpl/interface/communicator.h"


class UnoCommunicator:public Communicator<8>{
	public
	// Communicator interface
	private:
	void platformSpecificPrint(char *messageText) override final
	{
	}
	void platformSpecificExit() override final
	{
	}

public:
	void platformSpecificUpdateBufferToPins() override final
	{
	}
	void platformSpecificUpdatePinsToBuffer() override final
	{
	}
	:
	
	



#endif // TEST_H


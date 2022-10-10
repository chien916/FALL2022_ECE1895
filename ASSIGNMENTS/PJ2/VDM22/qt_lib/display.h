#ifndef DISPLAY_H
#define DISPLAY_H

#include "pixel.h"


#define REFRESH_DELAY 2


class Display{
private:

public:
	virtual void message(char* msg);

	virtual void flash(Pixel& pixel);

	template<int S>
	void flash(Pixel(&pixelArray)[S]) {
	   for(Pixel& it:pixelArray){
		   this->flash(it);
	   }
	}
};

#endif // DISPLAY_H

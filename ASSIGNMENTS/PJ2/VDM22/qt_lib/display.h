#ifndef DISPLAY_H
#define DISPLAY_H

#include "pixel.h"


#define REFRESH_DELAY 2


class Display {
  private:

  public:
	virtual void message(char* msg) const;

	virtual void flash(Pixel& pixel) const;

	template<int S>
	void flash(Pixel(&pixelArray)[S]) const {
		for(Pixel& it : pixelArray) {
			this->flash(it);
		}
	}
};

#endif // DISPLAY_H

#ifndef PIXEL_H
#define PIXEL_H


class Pixel
{
public:
	int x;
	int y;
	Pixel(int x=0,int y=0){
		this->set(x,y);
	}
	void set(int x,int y){
		this->x = x;
		this->y = y;
	}
};

#endif // PIXEL_H

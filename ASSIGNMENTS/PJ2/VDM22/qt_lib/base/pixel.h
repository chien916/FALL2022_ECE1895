#ifndef PIXEL_H
#define PIXEL_H


class Pixel {
  private:
	int x;
	int y;
  public:
	Pixel(int x = 0, int y = 0);
	void set(int x, int y);
	int getX() const;
	int getY() const;
};

inline Pixel::Pixel(int x, int y) {
	this->set(x, y);
}

inline void Pixel::set(int x, int y) {

	this->x = x;
	this->y = y;

}

inline int Pixel::getX() const {
	return this->x;
}

inline int Pixel::getY() const {
	return this->y ;
}

#endif // PIXEL_H

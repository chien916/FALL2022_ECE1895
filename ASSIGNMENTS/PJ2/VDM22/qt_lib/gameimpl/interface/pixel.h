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
/**
 * 构造——一个位于（x,y）的高电平像素
 * 注意！如果坐标没有被指定，默认设置（0，0）坐标
 * @brief Pixel::Pixel
 * @param x 水平坐标；左负右正
 * @param y 垂直坐标；下负上正
 */
inline Pixel::Pixel(int x, int y) {
	this->set(x, y);
}

/**
 * 设定——这个高电平像素的（x,y）坐标
 * @brief Pixel::set
 * @param x 水平坐标；左负右正
 * @param y 垂直坐标；下负上正
 */
inline void Pixel::set(int x, int y) {

	this->x = x;
	this->y = y;

}

/**
 * 获取——这个高电平像素的水平x坐标
 * @brief Pixel::getX
 * @return 水平坐标；左负右正
 */
inline int Pixel::getX() const {
	return this->x;
}

/**
 * 获取——这个高电平像素的垂直y坐标
 * @brief Pixel::getY
 * @return 垂直坐标；下负上正
 */
inline int Pixel::getY() const {
	return this->y ;
}

#endif // PIXEL_H

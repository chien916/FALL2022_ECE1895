#ifndef PIXELENTITY_H
#define PIXELENTITY_H
#include "pixel.h"
#include "exception.h"

template <unsigned int S>//S:有几个Pixel
class Displayable {
  private:
	Pixel pixelArray[S];
	bool visibility{false};
  public:
	Pixel& operator[](const unsigned int ind);
	unsigned int size();
	void shift(const int horizontalShift, const int verticalShift);
	bool getVisibility() const;
	void setVisibility(bool newVisibility);
};

/**
 *  获取——物体是否可见
 *  注意！这只是一个用于判断的属性，具体是否可见需要在Display中实现
 * @brief Displayable::getVisibility
 * @return 物体是否可见
 */
template<unsigned int S>
inline bool Displayable<S>::getVisibility() const {
	return visibility;
}
/**
 *  设定——物体是否可见
 *  注意！这只是一个用于判断的属性，具体是否可见需要在Display中实现
 * @brief Displayable::setVisibility
 * @param newVisibility 物体是否可见
 */
template<unsigned int S>
inline void Displayable<S>::setVisibility(bool newVisibility) {
	visibility = newVisibility;
}

/**
 * 获取参考--代表此物体像素矩阵中的第ind个元素
 * @brief Displayable::operator []
 * @param ind 像素矩阵索引
 * @return 参考--代表此物体像素矩阵中的第ind个元素
 */
template<unsigned int S>
inline Pixel &Displayable<S>::operator[](const unsigned int ind) {
	if(ind >= S) Exception((char*)("Displayable[] -> outOfBound"));
	return pixelArray[ind];
}

/**
 * 获取——代表此物体的像素矩阵中元素的数量
 * 注意！像素矩阵中元素的数量是一个固定值，运行过程中不应该被修改
 * @brief Displayable::size
 * @return 代表此物体的像素矩阵中元素的数量
 */
template<unsigned int S>
inline unsigned int Displayable<S>::size() {
	return S;
}

/**
 * 将代表此物体的像素矩阵中所有元素移动指定个单位
 * 注意！在QML画板上的坐标是正值向下向右，负值向上向左；在QML中垂直方向移动行为和此函数相反
 * @brief Displayable::shift
 * @param horizontalShift 平行（X坐标方向）移动单位数量 正值向右 负值向左
 * @param verticalShift 垂直（Y坐标方向）移动单位数量 正值向上 负值向下
 */
template<unsigned int S>
inline void Displayable<S>::shift(const int horizontalShift, const int verticalShift) {
	for(Pixel& it : pixelArray) {
		it.set(it.getX() + horizontalShift, it.getY());
	}
}





#endif // PIXELENTITY_H

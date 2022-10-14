#ifndef PIXELENTITY_H
#define PIXELENTITY_H

/**
 * @brief The Displayable class
 * @tparam P 像素数组的长度
 * @tparam T 存储像素坐标的基本数据类型
 */
template <unsigned char P,typename T>
class Displayable {
public:
	struct Pixel {
		T x;//x 水平坐标；左负右正
		T y;//y 垂直坐标；下负上正
	};

	// 属性——代表物体的高电平像素坐标数组
	Pixel pixelArray[P];

	// 属性——物体是否可见(这只是一个用于判断的属性，具体是否可见需要在Display中实现)
	bool visibility{false};

	/**
	 * 将代表此物体的像素矩阵中所有元素移动指定个单位
	 * 注意！在QML画板上的坐标是正值向下向右，负值向上向左；在QML中垂直方向移动行为和此函数相反
	 * @brief Displayable::shift
	 * @param horizontalShift 平行（X坐标方向）移动单位数量 正值向右 负值向左
	 * @param verticalShift 垂直（Y坐标方向）移动单位数量 正值向上 负值向下
	 */
	void shift(const T horizontalShift, const T verticalShift);
};

template<unsigned char P,typename T>
inline void Displayable<P,T>::shift(const T horizontalShift, const T verticalShift) {
	for(Pixel& it : pixelArray) {
		it.x += horizontalShift;
		it.y += verticalShift;
	}
}

#endif // PIXELENTITY_H

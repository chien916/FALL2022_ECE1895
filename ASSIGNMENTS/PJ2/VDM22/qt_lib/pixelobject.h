#ifndef PIXELOBJECT_H
#define PIXELOBJECT_H

#include "pixel.h"


/**
 * 线宽和线高定义
 *
 * 【C镜下的坐标】
 *
 * =====================-===================== -
 * =====================-===================== → line width = 3
 * =====================-===================== -
 *                       → cr height * line width = 1*3 = 3
 *                       -
 *                       C
 *
 *
 * =====================+=====================
 * =====================-=====================
 * =====================-=====================
 * |--------↓----------|
 * cr width * line width = 7*3 = 21
 *
 * 【B镜下的坐标】
 *
 *        line width = 3
 *        |-↑-|
 *        ===== -                  ===== -
 *        ===== → line width = 3  ===== → br subheight * line width = 2*3 = 6
 *        ===== -                  ===== |
 *        =====                    ===== |
 *        =====                    ===== |
 *        =====                    ===== -
 *					     C
 * ===================== ===================== -
 * ===================== ===================== |
 * ===================== ===================== → br height * line width = 2*3 = 6
 * ===================== ===================== |
 * ===================== ===================== |
 * ===================== ===================== -
 * |---------↓--------|
 * br width * line width = 2*3 = 6
 *
 *
 * 【飞机坐标】
 *    plane width * line width = 1*3 = 3
 *    -↑-
 *    ===
 *    ===
 *    ===
 * ========= -
 * ====C==== → plane width * line width = 1*3 = 3
 * ========= -
 *    ===
 *    ===
 *    ===
 */
#define LINE_WIDTH 5
#define CR_HEIGHT 11
#define CR_WIDTH 5
#define BR_HEIGHT 5
#define BR_SUBHEIGHT 5
#define BR_WIDTH 5
#define PLANE_WIDTH 3

/**
 * 像素数组大小定义（自动判断）
 */
#define CR_ARRAY_SIZE CR_WIDTH*LINE_WIDTH*2*LINE_WIDTH*2
#define BR_ARRAY_SIZE LINE_WIDTH*2*BR_SUBHEIGHT*LINE_WIDTH\
	+BR_WIDTH*LINE_WIDTH*2*BR_HEIGHT*LINE_WIDTH
#define PLANE_ARRAY_SIZE PLANE_WIDTH*LINE_WIDTH*PLANE_WIDTH*LINE_WIDTH*5


class PixelObject {
  private:
	bool cReferenceVisible = false;
	bool bReferenceVisible = false;
	bool planeVisible = false;
	Pixel cReference[CR_ARRAY_SIZE];
	Pixel bReference[BR_ARRAY_SIZE];
	Pixel plane[PLANE_WIDTH * LINE_WIDTH];
  public:
	/**
	 * @brief 设置C镜头参考线是否可见
	 * @param v 是否可见
	 */
	void cReferenceSetVisibility(const bool v) {
		this->cReferenceVisible = v;
	}

	/**
	 * @brief 设置B镜头参考线是否可见
	 * @param v 是否可见
	 */
	void bReferenceSetVisibility(const bool v) {
		this->bReferenceVisible = v;
	}

	/**
	 * @brief 设置飞机是否可见
	 * @param v 是否可见
	 */
	void planeSetVisibility(const bool v) {
		this->planeVisible = v;
	}

	/**
	 * @brief 将C镜头参考线重新定位到指定位置
	 * @param x 预期的中点横坐标
	 * @param y 预期的中点纵坐标
	 */
	void cReferenceSetCenter(const int x, const int y) {

	}

	/**
	 * @brief 将B镜头参考线重新定位到指定位置
	 * @param x 预期的中点横坐标
	 * @param y 预期的中点纵坐标
	 */
	void bReferenceSetCenter(const int x, const int y) {

	}

	/**
	 * @brief 将飞机重新定位到指定位置
	 * @param x 预期的中点横坐标
	 * @param y 预期的中点纵坐标
	 */
	void planeSetCenter(const int x, const int y) {

	}

};

#endif // PIXELOBJECT_H

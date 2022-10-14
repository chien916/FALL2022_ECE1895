#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include "interface/displayable.h"
#include "interface/communicator.h"
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
#define LINE_WIDTH 1
#define CR_HEIGHT 10
#define CR_WIDTH 5
#define BR_HEIGHT 5
#define BR_SUBHEIGHT 5
#define BR_WIDTH 5
#define PLANE_WIDTH 5

/**
 * 像素数组大小定义（自动判断）
 */
#define CR_ARRAY_SIZE CR_WIDTH*LINE_WIDTH*2*LINE_WIDTH*2
#define BR_ARRAY_SIZE LINE_WIDTH*2*BR_SUBHEIGHT*LINE_WIDTH\
	+BR_WIDTH*LINE_WIDTH*2*BR_HEIGHT*LINE_WIDTH
#define PLANE_ARRAY_SIZE PLANE_WIDTH*LINE_WIDTH*PLANE_WIDTH*LINE_WIDTH*5

template <unsigned char B, typename T>
class GamePlay {
  private:
	Displayable<CR_ARRAY_SIZE, T> cReferenceDisplayable{};
	Displayable<BR_ARRAY_SIZE, T> bReferenceDisplayable{};
	Displayable<PLANE_ARRAY_SIZE, T> planeDisplayable{};
	struct Displayable<CR_ARRAY_SIZE, T>::Pixel cReferenceCenter{0,0};

	Communicator<B> *gameCommunicatorPointer{nullptr};
  public:
	GamePlay(Communicator<B>*gameCommunicatorPointer);
};

template <unsigned char B, typename T>
inline GamePlay<B, T>::GamePlay(Communicator<B> *gameCommunicatorPointer) {
	this->gameCommunicatorPointer = gameCommunicatorPointer;
	//C镜下的坐标初始化

}

#endif // GAMEPLAY_H

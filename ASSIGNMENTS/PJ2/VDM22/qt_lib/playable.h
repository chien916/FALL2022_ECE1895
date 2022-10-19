#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include "displayable.h"
#include "communicator.h"
/**
 * 线宽和线高定义
 *
 * 【C镜下的坐标】
 *
 * =========================================== -
 * =========================================== → line width = 3
 * =========================================== -
 *	                     -
 *                       → cr height * line width = 1*3 = 3
 *                       -
 *                       C
 *
 *
 *
 * ===========================================
 * ===========================================
 * ===========================================
 * |--------↓----------|
 * cr width * line width = 7*3 = 21
 *
 * 【B镜下的坐标】
 *
 *        line width = 3
 *        |-↑-|
 *        ===== -                  ===== -
 *        ===== → line width = 3  ===== → br height * line width = 2*3 = 6
 *        ===== -                  ===== |
 *        =====                    ===== |
 *        =====                    ===== |
 *        =====                    ===== -
 *					     C
 * ===================== ===================== -
 * ===================== ===================== → line width = 3
 * ===================== ===================== -
 * |---------↓--------|
 * br width * line width = 2*3 = 6
 *
 *
 * 【飞机坐标】
 *    plane width * line width = 1*3 = 3
 *    -↑-
 *     =
 *     =
 *     =
 *  ===C=== → plane width = 3
 *     =
 *     =
 *     =
 */
#define LINE_WIDTH 1
#define CR_HEIGHT 10
#define CR_WIDTH 5
#define BR_HEIGHT 2
#define BR_WIDTH 60
#define PLANE_WIDTH 5

/**
 * 像素数组大小定义（自动判断）
 */
#define CR_ARRAY_SIZE (CR_WIDTH*LINE_WIDTH*2+1)*LINE_WIDTH*2
#define BR_ARRAY_SIZE LINE_WIDTH*2*BR_HEIGHT*LINE_WIDTH\
	+BR_WIDTH*LINE_WIDTH*2*LINE_WIDTH
#define PLANE_ARRAY_SIZE PLANE_WIDTH*4+1

template <unsigned char B, typename T, typename D, typename A>
class Playable {
  private:

	struct Displayable<CR_ARRAY_SIZE, T>::Pixel cReferenceCenter {
		0, 0
	};
	struct Displayable<BR_ARRAY_SIZE, T>::Pixel bReferenceCenter {
		0, 0
	};
	struct Displayable<PLANE_ARRAY_SIZE, T>::Pixel planeCenter {
		0, 0
	};

	Communicator<B, D, A> *gameCommunicatorPointer{nullptr};

	bool initializeCReferenceDisplayable(T xCenter, T yCenter);

	bool initializeBReferenceDisplayable(T xCenter, T yCenter);

	bool initializePlaneDisplayable(T xCenter, T yCenter);

  public:
	Displayable<CR_ARRAY_SIZE, T> cReferenceDisplayable{};
	Displayable<BR_ARRAY_SIZE, T> bReferenceDisplayable{};
	Displayable<PLANE_ARRAY_SIZE, T> planeDisplayable{};
	Playable(Communicator<B, D, A>*gameCommunicatorPointer);
	virtual bool displayAllDisplayableToScreen() = 0;

};

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::initializeCReferenceDisplayable(T xCenter, T yCenter) {
	unsigned short iterationCount{0};
	T drawParameters[2][4] {
		//C坐标
		{
			xCenter - CR_WIDTH * LINE_WIDTH,
			xCenter + CR_WIDTH * LINE_WIDTH,
			yCenter + CR_HEIGHT * LINE_WIDTH + LINE_WIDTH,
			yCenter + CR_HEIGHT * LINE_WIDTH + 1
		},
		{
			xCenter - CR_WIDTH * LINE_WIDTH,
			xCenter + CR_WIDTH * LINE_WIDTH,
			yCenter - CR_HEIGHT * LINE_WIDTH - 1,
			yCenter - CR_HEIGHT * LINE_WIDTH - LINE_WIDTH

		}
	};
	bool toReturn = this->cReferenceDisplayable.initializePixelInformation(drawParameters);
	this->cReferenceCenter.x = xCenter;
	this->cReferenceCenter.y = yCenter;
	this->cReferenceDisplayable.visibility = false;
	gameCommunicatorPointer->buildCheckMessage("initializeCReferenceDisplayable:", toReturn);
	return toReturn;
}


template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::initializeBReferenceDisplayable(T xCenter, T yCenter) {
	unsigned short iterationCount{0};
	T drawParameters[4][4] {
		//B坐标
		{
			xCenter - BR_WIDTH * LINE_WIDTH,
			xCenter - BR_WIDTH * LINE_WIDTH,
			yCenter + BR_HEIGHT * LINE_WIDTH,
			yCenter + 1
		},
		{
			xCenter + BR_WIDTH * LINE_WIDTH,
			xCenter + BR_WIDTH * LINE_WIDTH,
			yCenter + BR_HEIGHT * LINE_WIDTH,
			yCenter + 1
		},
		{
			xCenter - BR_WIDTH * LINE_WIDTH,
			xCenter - 1,
			yCenter - 1,
			yCenter - 1
		},
		{
			xCenter + 1,
			xCenter + BR_WIDTH * LINE_WIDTH,
			yCenter - 1,
			yCenter - 1
		}
	};
	bool toReturn = this->bReferenceDisplayable.initializePixelInformation(drawParameters);
	this->bReferenceCenter.x = xCenter;
	this->bReferenceCenter.y = yCenter;
	this->bReferenceDisplayable.visibility = false;
	gameCommunicatorPointer->buildCheckMessage("initializeBReferenceDisplayable:", toReturn);
	return toReturn;
}

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::initializePlaneDisplayable(T xCenter, T yCenter) {
	unsigned short iterationCount{0};
	T drawParameters[3][4] {
		//飞机坐标
		{
			xCenter,
			xCenter,
			yCenter + PLANE_WIDTH,
			yCenter - PLANE_WIDTH
		},
		{
			xCenter - PLANE_WIDTH,
			xCenter - 1,
			yCenter,
			yCenter
		},
		{
			xCenter + 1,
			xCenter + PLANE_WIDTH,
			yCenter,
			yCenter
		}
	};
	bool toReturn = this->planeDisplayable.initializePixelInformation(drawParameters);
	this->planeCenter.x = xCenter;
	this->planeCenter.y = yCenter;
	this->planeDisplayable.visibility = true;
	gameCommunicatorPointer->buildCheckMessage("initializePlaneDisplayable:", toReturn);
	return toReturn;
}

template <unsigned char B, typename T, typename D, typename A>
inline Playable<B, T, D, A>::Playable(Communicator<B, D, A> *gameCommunicatorPointer) {
	this->gameCommunicatorPointer = gameCommunicatorPointer;
	//C镜下的坐标初始化
	this->initializeCReferenceDisplayable(0, 0);
	this->initializeBReferenceDisplayable(0, 0);
	this->initializePlaneDisplayable(0, 0);

}

#endif // GAMEPLAY_H

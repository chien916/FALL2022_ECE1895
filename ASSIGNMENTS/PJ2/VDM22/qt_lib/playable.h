#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include "displayable.h"
#include "communicator.h"
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
  public:

	Communicator<B, T, D, A>* communicatorPointer;

	struct Displayable<PLANE_ARRAY_SIZE, T>::Pixel planeCenter {
		0, 0
	};

	T bReferenceDistance{0};

	bool initializeCReferenceDisplayable();

	bool initializeBReferenceDisplayable(T distance);

	bool initializePlaneDisplayable(T xCenter, T yCenter);

	Displayable<CR_ARRAY_SIZE, T> cReferenceDisplayable{};
	Displayable<BR_ARRAY_SIZE, T> bReferenceDisplayable{};
	Displayable<PLANE_ARRAY_SIZE, T> planeDisplayable{};

	bool setCommunicator(Communicator<B, T, D, A> * communicatorPointer);
	bool flashAllDisplayable();
	bool startNewGame();
	bool processInputAndGenerateOutput();
	bool executeAndLoop();



};

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::initializeCReferenceDisplayable() {
	bool status{true};
	T xCenter{0}, yCenter{0};
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
	status &= this->cReferenceDisplayable.initializePixelInformation(drawParameters);
	this->cReferenceDisplayable.visibility = false;
	return status;
}


template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::initializeBReferenceDisplayable(T distance) {
	bool status{true};
	if(distance < 0 || distance > BR_WIDTH * LINE_WIDTH - LINE_WIDTH) return false;
	T xCenter{0}, yCenter{0};
	T drawParameters[4][4] {
		//B坐标
		{
			xCenter - BR_WIDTH * LINE_WIDTH + distance,
			xCenter - BR_WIDTH * LINE_WIDTH + distance,
			yCenter + BR_HEIGHT * LINE_WIDTH,
			yCenter + 1
		},
		{
			xCenter + BR_WIDTH * LINE_WIDTH - distance,
			xCenter + BR_WIDTH * LINE_WIDTH - distance,
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
	status &= this->bReferenceDisplayable.initializePixelInformation(drawParameters);
	this->bReferenceDistance = distance;
	this->bReferenceDisplayable.visibility = false;
	return status;
}

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::initializePlaneDisplayable(T xCenter, T yCenter) {
	bool status{true};
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
	status &= this->planeDisplayable.initializePixelInformation(drawParameters);
	this->planeCenter.x = xCenter;
	this->planeCenter.y = yCenter;
	this->planeDisplayable.visibility = true;
	return status;
}

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::setCommunicator(Communicator<B, T, D, A> *communicatorPointer) {
	if(communicatorPointer == nullptr) return false;
	this->communicatorPointer = communicatorPointer;
	return true;
}

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::flashAllDisplayable() {
	if(this->communicatorPointer == nullptr) return false;
	bool status{true};
	if(planeDisplayable.visibility)
		for(struct Displayable<PLANE_ARRAY_SIZE, T>::Pixel& pixelIt : planeDisplayable.pixelArray) {
			status &= communicatorPointer->platformSpecificFlashPixelToScreen(pixelIt.x, pixelIt.y);
		}
	if(bReferenceDisplayable.visibility)
		for(struct Displayable<BR_ARRAY_SIZE, T>::Pixel& pixelIt : bReferenceDisplayable.pixelArray) {
			status &= communicatorPointer->platformSpecificFlashPixelToScreen(pixelIt.x, pixelIt.y);
		}
	if(cReferenceDisplayable.visibility)
		for(struct Displayable<CR_ARRAY_SIZE, T>::Pixel& pixelIt : cReferenceDisplayable.pixelArray) {
			status &= communicatorPointer->platformSpecificFlashPixelToScreen(pixelIt.x, pixelIt.y);
		}
	return status;
}

template <unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::startNewGame() {
	bool status{true};
	//C镜下的坐标初始化
	status &= this->initializeCReferenceDisplayable(0, 0);
	status &= this->initializeBReferenceDisplayable(0, 0);
	status &= this->initializePlaneDisplayable(0, 0);
	return status;
}

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::processInputAndGenerateOutput() {

}

template<unsigned char B, typename T, typename D, typename A>
inline bool Playable<B, T, D, A>::executeAndLoop() {
	if(this->communicatorPointer == nullptr) return false;
	bool status{true};
	while(status) {
		communicatorPointer->platformSpecificUpdatePinsToBuffer();//获取输入
		this->processInputAndGenerateOutput(); //游戏处理
		communicatorPointer->platformSpecificUpdatePinsToBuffer();//推送输出
		this->flashAllDisplayable();//更新显示
	}

}

#endif // GAMEPLAY_H

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

#ifndef QTPLAYABLE_H
#define QTPLAYABLE_H

#include "playable.h"
#include "myquickpainteditem.h"
template <unsigned char B, typename T, typename D, typename A>
class QtPlayable: public Playable<B, T, D, A> {
  private:
	MyQuickPaintedItem* myQuickPaintedItemPointer;
  public:
	QtPlayable(Communicator<B, D, A>*gameCommunicatorPointer, MyQuickPaintedItem* myQuickPaintedItemPointer);
	bool displayAllDisplayableToScreen() override final {

		if(myQuickPaintedItemPointer == nullptr) return false;
//		myQuickPaintedItemPointer->helloWorld();
		myQuickPaintedItemPointer->clearBuffer();
		myQuickPaintedItemPointer->uploadDisplayableToBuffer<CR_ARRAY_SIZE, int>(this->cReferenceDisplayable);
		myQuickPaintedItemPointer->uploadDisplayableToBuffer<BR_ARRAY_SIZE, int>(this->bReferenceDisplayable);
		myQuickPaintedItemPointer->uploadDisplayableToBuffer<PLANE_ARRAY_SIZE, int>(this->planeDisplayable);
		myQuickPaintedItemPointer->uploadBufferToScreen();
		return true;
	}
};

template<unsigned char B, typename T, typename D, typename A>
inline QtPlayable<B, T, D, A>::QtPlayable(Communicator<B, D, A> *gameCommunicatorPointer, MyQuickPaintedItem *myQuickPaintedItemPointer):
	Playable<B, T, D, A>(gameCommunicatorPointer) {
	myQuickPaintedItemPointer = myQuickPaintedItemPointer;
	displayAllDisplayableToScreen();
}
#endif // QTPLAYABLE_H

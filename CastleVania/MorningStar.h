#ifndef __MORNINGSTAR_H__
#define __MORNINGSTAR_H__	

#include "Item.h"

#define _SPRITE L"item/3.png"
#define TYPE TypeGame::Item_morning_star

class MorningStar : public Item {
private:

public:
	MorningStar(int x, int y, int x2, int y2);
	MorningStar();
	~MorningStar();
};

#endif
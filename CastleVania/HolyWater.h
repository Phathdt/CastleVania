#ifndef __HOLYWATER_H__
#define __HOLYWATER_H__	

#include "Item.h"

#define _SPRITE L"item/9.png"
#define TYPE TypeGame::Item_holy_water

class HolyWater : public Item {
private:

public:
	HolyWater(int x, int y, int x2, int y2);
	HolyWater();
	~HolyWater();
};

#endif
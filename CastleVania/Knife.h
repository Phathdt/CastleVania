#ifndef __KNIFE_H__
#define __KNIFE_H__	

#include "Item.h"
#define _WIDTH	32
#define _HEIGHT	18
#define _SPRITE L"item/4.png"
#define TYPE TypeGame::Item_knife

class Knife : public Item {
private:

public:
	Knife(int x, int y, int x2, int y2);
	Knife();
	~Knife();
};

#endif
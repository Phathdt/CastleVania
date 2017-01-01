#ifndef __ROAST_H__
#define __ROAST_H__	

#include "Item.h"
#define _WIDTH	32
#define _HEIGHT	26
#define _SPRITE L"item/10.png"
#define TYPE TypeGame::Item_roast

class Roast : public Item {
private:

public:
	Roast(int x, int y, int x2, int y2);
	Roast();
	~Roast();
};

#endif
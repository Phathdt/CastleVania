#ifndef __AXE_H__
#define __AXE_H__

#include "Item.h"
#define _WIDTH	30
#define _HEIGHT	28
#define _SPRITE L"item/7.png"
#define TYPE TypeGame::Item_axe

class Axe : public Item {
private:

public:
	Axe(int x, int y, int x2, int y2);
	Axe();
	~Axe();
};

#endif
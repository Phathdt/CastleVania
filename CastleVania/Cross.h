#ifndef __CROSS_H__
#define __CROSS_H__

#include "GObject.h"
#include "GSprite.h"
#include "Item.h"
#define _WIDTH	30
#define _HEIGHT	28
#define _SPRITE L"item/8.png"
#define TYPE TypeGame::Item_cross

class Cross : public Item {
private:

public:
	Cross(int x, int y, int x2, int y2);
	Cross();
	~Cross();
};

#endif
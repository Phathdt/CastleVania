#ifndef __BIGHEART_H__
#define __BIGHEART_H__

#include "Item.h"
#define _WIDTH	24
#define _HEIGHT	20
#define _SPRITE L"item/1.png"
#define TYPE TypeGame::Item_big_heart

class BigHeart : public Item {
private:

public:
	BigHeart(int x, int y, int x2, int y2);
	BigHeart();
	~BigHeart();
};

#endif
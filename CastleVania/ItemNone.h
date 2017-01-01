#ifndef __ITEMNONE_H__
#define __ITEMNONE_H__

#include "Item.h"
#define _WIDTH	0
#define _HEIGHT	0
#define _SPRITE L"item/7.png"
#define TYPE TypeGame::Item_none

class ItemNone : public Item {
private:

public:
	ItemNone(int x, int y, int x2, int y2);
	void Draw();
	ItemNone();
	~ItemNone();
};

#endif
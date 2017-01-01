#ifndef __ROSARY_H__
#define __ROSARY_H__	

#include "Item.h"

#define _SPRITE L"item/6.png"
#define TYPE TypeGame::Item_rosary

class Rosary : public Item {
private:

public:
	Rosary(int x, int y, int x2, int y2);
	Rosary();
	~Rosary();
};

#endif
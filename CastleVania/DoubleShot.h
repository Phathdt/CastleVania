#ifndef __DOUBLESHOT_H__
#define __DOUBLESHOT_H__

#include "Item.h"
#define _WIDTH	42
#define _HEIGHT	42
#define _SPRITE_BLUE L"item/11.png" 
#define _SPRITE_RED L"item/12.png" 
#define TYPE TypeGame::Item_double_shot
enum DoubleShotColor{
	ShotRed = 0,
	ShotBlue = 1 
};
class DoubleShot : public Item {
private:
	int _doubleshotcolor; // mau xanh vs mau do, xu ly khac nhau thi dung cai nay phan biet.
public:
	DoubleShot(int x, int y, int x2, int y2);
	DoubleShot();
	~DoubleShot();
};

#endif
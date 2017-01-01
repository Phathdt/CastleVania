#ifndef __SMALLHEART_H__
#define __SMALLHEART_H__

#include "Item.h"

#define _SPRITE L"item/0.png"
#define SIZE 16
#define TYPE TypeGame::Item_small_heart

class SmallHeart : public Item {
private:

public:
	SmallHeart(int x, int y, int x2, int y2);
	void MoveUpdate(float deltaTime);
	void Update(float deltatime);

	SmallHeart();
	~SmallHeart();
};

#endif
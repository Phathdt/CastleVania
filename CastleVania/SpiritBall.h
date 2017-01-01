#ifndef __SPIRITBALL_H__
#define __SPIRITBALL_H__	

#include "Item.h"
#define _WIDTH	28
#define _HEIGHT	32
#define _SPRITE L"item/13.png"
#define TYPE TypeGame::Item_spirit_ball

class SpiritBall : public Item {
private:

public:
	SpiritBall(int x, int y, int x2, int y2);
	void SetFrame(float deltattime);
	SpiritBall();
	~SpiritBall();
};

#endif
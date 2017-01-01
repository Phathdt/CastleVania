#ifndef __FIRETOWER_H__
#define __FIRETOWER_H__

//Cây nến nhỏ

#include "Ground.h"
#define _smallWIDTH	16
#define _smallHEIGHT	32
#define _SPRITE L"ground/0.png"
#define TYPE TypeGame::Ground_Firetower

class Firetower : public Ground {
private:

public:
	Firetower(int x, int y);

	void SetFrame(float deltattime);
	
	Firetower();
	~Firetower();
};

#endif

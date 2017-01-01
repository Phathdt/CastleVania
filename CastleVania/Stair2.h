#ifndef __STAIR2_H__
#define __STAIR2_H__

//Cầu thang

#include "GObject.h"
#include "SweptAABB.h"
#include "Simon.h"
#define _stairWIDTH	16
#define _stairHEIGHT	16
#define _SPRITE L"ground/3.png"
#define TYPE TypeGame::Ground_Stair_Down

class Stair2 : public GObject {
private:
	int _parentW;
public:
	Stair2(int x, int y, int parentX, int parentY, int _parentW);
	bool canGoDown();
	CSweptAABB* swepyAABB;
	void Collistion(float deltatime);
	int parentX;
	int parentY;
	Stair2();
	~Stair2();
};

#endif

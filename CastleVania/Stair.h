#ifndef __STAIR_H__
#define __STAIR_H__

//Cầu thang

#include "GObject.h"
#include "SweptAABB.h"
#include "Simon.h"
#define _stairWIDTH	16
#define _stairHEIGHT	16
#define _SPRITE L"ground/3.png"
#define TYPE TypeGame::Ground_Stair_Up

class Stair : public GObject {
private:

public:
	Stair(int x, int y,int parentX,int parentY);
	bool canGoDown();
	CSweptAABB* swepyAABB;
	void Collistion(float deltatime);
	int parentX;
	int parentY;
	Stair();
	~Stair();
};

#endif

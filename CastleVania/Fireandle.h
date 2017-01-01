#ifndef __FIREANDLE_H__
#define __FIREANDLE_H__

//Cây nến bự

#include "Ground.h"
#include "SweptAABB.h"
#include "Simon.h"
#define _WIDTH	32
#define _HEIGHT	64
#define _SPRITE L"ground/1.png"
#define TYPE TypeGame::Ground_Fireandle

class Fireandle : public Ground {
private:
	CSweptAABB* swepyAABB;
public:
	Fireandle(int x, int y);

	void SetFrame(float deltattime);
	void Collistion(float deltatime);
	Fireandle();
	~Fireandle();
};

#endif

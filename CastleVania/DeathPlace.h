#ifndef __DEATH_PLACE_H__
#define __DEATH_PLACE_H__

#include "GObject.h"
#include "Simon.h"
#include "SweptAABB.h"
class DeathPlace :public GObject{
private:
	CSweptAABB* swepyAABB;
public:
	DeathPlace(){}
	DeathPlace(int x, int y, int w, int h);
	void Collistion(float deltatime);
};
#endif

#include "DeathPlace.h"
DeathPlace::DeathPlace(int x, int y, int w, int h)
:GObject(39, x, y, w, h){
	
	_box = Box(x, y, w-x, h-y, 0, 0);
	swepyAABB = new CSweptAABB();
}
void DeathPlace::Collistion(float deltatime){
	float x, y;
	if (swepyAABB->AABB(Simon::getCurrentSimon()->_box, this->_box, x, y)){
		Simon::getCurrentSimon()->Murder();
		THEME(THEME_GAMEOVER);
	}
}
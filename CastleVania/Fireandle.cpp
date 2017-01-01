#include "Fireandle.h"



Fireandle::Fireandle(int x, int y) :
Ground(TYPE, x, y)
{
	_box = Box(x, y, _WIDTH, _WIDTH);
	GTexture* texture = new GTexture(_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, _ANIMATE_RATE);
	swepyAABB = new CSweptAABB();
}


void Fireandle::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
		this->_sprite->_start = 0;
		this->_sprite->_end = 1;

#pragma endregion
}
void Fireandle::Collistion(float deltatime){
	float x, y;
	
	if (Simon::getCurrentSimon()->isFighting() 
		|| Boomerang::getCurrentBoomerang()->isFlying()
		|| WeaponKnife::getCurrentKnife()->isFlying()){
		if (swepyAABB->AABB(Whip::getCurrentWhip()->_box, this->_box, x, y)
			|| swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
			|| swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
			){
			this->_isDeath = true;
			
		}
	}
	
}

Fireandle::~Fireandle(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

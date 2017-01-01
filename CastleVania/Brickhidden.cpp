#include "Brickhidden.h"



Brickhidden::Brickhidden(int x, int y) :
Ground(TYPE, x, y)
{
	_box = Box(x, y, _WIDTH, _HEIGHT);
	GTexture* texture = new GTexture(_SPRITE, 1, 1, 1);
	_sprite = new GSprite(texture, 0);
	swepyAABB = new CSweptAABB();
}
void Brickhidden::Collistion(float deltatime){
	float x, y;
	
	if (Simon::getCurrentSimon()->_isDeath) return;
	if (_isDeath) return;
	int stateCollid = swepyAABB->CollideCheck(Simon::getCurrentSimon()->_box, this->_box, x, y);
	switch (stateCollid)
	{
	case COLLIDE_STATE::NONE:
		if (Simon::getCurrentSimon()->GetState() == STATE::IS_JOGGING&&!Simon::getCurrentSimon()->canGoStair())
		{
			Simon::getCurrentSimon()->ChangeState(STATE::IS_FALLING);
		}
		break;
	case COLLIDE_STATE::LEFT:
		Simon::getCurrentSimon()->canGoLeft(false);
		break;
	case COLLIDE_STATE::RIGHT:
		Simon::getCurrentSimon()->canGoRight(false);
	
		break;
	case COLLIDE_STATE::TOP:
		break;
	case COLLIDE_STATE::BOTTOM:
		if (Simon::getCurrentSimon()->isFighting()){
			Simon::getCurrentSimon()->ChangeState(STATE::IS_FIGHTING);
		}
		else{
			
			Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
		}
		break;
	default:
		break;
	}
	if (Simon::getCurrentSimon()->isFighting() 
		|| Boomerang::getCurrentBoomerang()->isFlying()
		|| WeaponKnife::getCurrentKnife()->isFlying()){
		if (swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y)
			|| swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
			|| swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
			){
			this->_isDeath = true;
			SOUND(SOUND_HIT);
		}
	}
}

void Brickhidden::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 0;

#pragma endregion
}


Brickhidden::~Brickhidden(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

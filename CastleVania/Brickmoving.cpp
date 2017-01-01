#include "Brickmoving.h"


Brickmoving::Brickmoving(int x, int y, int x2, int y2) :
Enemy(TYPE, x, y, x2, y2)
{	
	_vx = _mvbSPEED;
	_box = Box(x, y, _mvbWIDTH, _mvbHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(_SPRITE, 1, 1, 1);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	_activeArea.right = x2 - _mvbWIDTH;
}

void Brickmoving::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__

	if (_isMoveleft){
		if (_x <= _activeArea.left){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
			
		}
	}
	else{
		if (_x >= _activeArea.right){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
			
		}
	}
	this->_x += int(this->_vx * deltaTime);

#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Brickmoving::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
		this->_sprite->_start = 0;
		this->_sprite->_end = 0;
#pragma endregion
}

void Brickmoving::Update(float deltatime){
	this->MoveUpdate(deltatime);
	this->SetFrame(0);
	this->_sprite->Update(deltatime);
}

void Brickmoving::Collistion(float deltatime){
	float x, y;

	if (Simon::getCurrentSimon()->_isDeath) return;
	
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
		//Simon::getCurrentSimon()->canGoLeft(false);
		break;
	case COLLIDE_STATE::RIGHT:
		//Simon::getCurrentSimon()->canGoRight(false);

		break;
	case COLLIDE_STATE::TOP:
		//Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
		break;
	case COLLIDE_STATE::BOTTOM:
		if (Simon::getCurrentSimon()->isFighting()){
			Simon::getCurrentSimon()->ChangeState(STATE::IS_FIGHTING);
		}
		else{
			Simon::getCurrentSimon()->setBox(this->_box);
			Simon::getCurrentSimon()->_vx = this->_vx;
			Simon::getCurrentSimon()->ChangeState(STATE::ON_BRICK_MOVING);
		}
		break;
	default:
		break;
	}

}
void Brickmoving::Draw(){
	this->_sprite->Draw(_x , _y);
}
Brickmoving::~Brickmoving(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

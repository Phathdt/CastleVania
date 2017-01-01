#include "SmallHeart.h"



SmallHeart::SmallHeart(int x, int y, int x2, int y2) :
Item(TYPE, x, y, x2, y2)
{
	GTexture* texture = new GTexture(_SPRITE, 1, 1, 1,false);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	_box =Box(x, y, SIZE, SIZE*2,_vx,_vy);
	this->SetFrame(0); 
}

void SmallHeart::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	if (this->_lifeTime < 0){
		return;
	}
	this->_lifeTime += deltaTime;
	if (this->_isOnGround){
		return;
	}
	if (this->_y + this->_height >= this->_activeArea.bottom){
		this->_isOnGround = true;
		return;
	}
	else{
		this->_y += this->_vy*deltaTime;
		this->_x += int(6.5* sin(float(_y)));
	}
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void SmallHeart::Update(float deltatime){
	this->MoveUpdate(deltatime);
	this->_sprite->Update(deltatime);
}

SmallHeart::~SmallHeart(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

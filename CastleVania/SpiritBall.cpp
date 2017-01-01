#include "SpiritBall.h"



SpiritBall::SpiritBall(int x, int y, int x2, int y2) :
Item(TYPE, x, y, x2, y2)
{
	GTexture* texture = new GTexture(_SPRITE, 2, 1, 2, false);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	this->SetFrame(0);
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
}
void SpiritBall::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 1;
#pragma endregion
}


SpiritBall::~SpiritBall(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

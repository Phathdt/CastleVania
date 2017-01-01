#include "NextBall.h"



NextBall::NextBall(int x, int y) :
GObject(TYPE, x, y, _WIDTH, _HEIGHT)
{
	GTexture* texture = new GTexture(_SPRITE, 2, 1, 2, false);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	this->SetFrame(0);
	_box = Box(x, y, _WIDTH, _HEIGHT);
	_time = 50;
}
void NextBall::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 1;
#pragma endregion
}
void NextBall::Collistion(float deltaTime)
{
	float x, y;
	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		Simon::getCurrentSimon()->nextLV();
		GCamera::getCurrentCamera()->getCurrentCamera()->ChangeState(1);
	}
}
void NextBall::Update(float DeltaTime)
{
	_time -= DeltaTime;
	if (_time <= 0)
	{
		if (_y < _SpiritBall_y2)
		{
			_vy = 0.5f;
		}
		else
		if (_y >= _SpiritBall_y2)
		{
			_vy = 0;
		}
	}
	
	this->_y += int(this->_vy * DeltaTime);

	_box = Box(_x, _y, _WIDTH, _HEIGHT);
	this->SetFrame(DeltaTime);
	this->_sprite->Update(DeltaTime);
}

void NextBall::Draw(){
	this->_sprite->Draw(_x, _y);

}

NextBall::~NextBall(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

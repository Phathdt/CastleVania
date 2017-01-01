#include "Ghost.h"

Ghost::Ghost(int x, int y,int x2,int y2) :
Enemy(TYPE,x, y, x2, y2)
{
	GTexture* ghosttt = new GTexture(GHOST_SPRITE, 2, 1, 2);
	_sprite = new GSprite(ghosttt, ANIMATIONRATE);
	this->_vx = _ghostSPEED;
}
Ghost::Ghost(int x, int y, int x2, int y2, bool left) :
Enemy(TYPE, x, y, x2, y2, left)
{
	_vx = _ghostSPEED;
	_box = Box(_x, _y, _ghostWIDTH, _ghostHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(GHOST_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	if (left)
		_isMoveleft = false;
	else{
		_isMoveleft = true;
	}
	int w = abs(x2 - x)/2;
	int h = abs(y2 - y);
	if (!_isMoveleft){
		
		_awakeBox = Box(x + w, y, w, h, 0, 0);
	}
	else{
		_awakeBox = Box(x , y, w, h, 0, 0);
		_vx = -_vx;
	}
	this->SetFrame(0);
	_hp = HP;
	_isDead = false;
	_damage = DAMAGE;
}
void Ghost::MoveUpdate(float deltaTime){
	if (!_isSleep) Enemy::MoveUpdate(deltaTime);
}
void Ghost::Update(float deltatime){
	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}

	if (this->_isDead){
		return;
	}
	this->MoveUpdate(deltatime);
	this->_sprite->Update(deltatime);
}

void Ghost::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 1;
#pragma endregion
}
void Ghost::Collistion(float deltatime){
 	if (_isDead) return;
	float x, y;
	if (swepyAABB->AABB(this->_awakeBox, Simon::getCurrentSimon()->_box, x, y)){
		_isSleep = false;
	}
	if (!_isSleep) Enemy::Collistion(deltatime);

}
void Ghost::Draw(){
	if (!_isSleep)
		Enemy::Draw();
}
Ghost::~Ghost(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

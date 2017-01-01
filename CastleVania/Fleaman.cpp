#include "Fleaman.h"


Fleaman::Fleaman(int x, int y, int x2, int y2) :
Enemy(TYPE, x, y, x2, y2)
{
	_isSleep = true;
	_vx = _fleamanSPEED;
	_box = Box(x, y, _fleamanWIDTH, _fleamanHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	_awakeBox = Box(x-100, y-100, 200, 200, 0, 0);
	_hp = HP;
	_damage = DAMAGE;
}

void Fleaman::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__

	if (this->_currentState == FLEAMAN_STATE::WAIT){
		return;
	}
	this->_x += this->_vx*deltaTime;
	this->_y += this->_vy*deltaTime;
	if (_vy <= -0.2)
		_vy += 0.2;
	else
		_vy = GRAVITY;
	
		
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Fleaman::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (this->_isSleep){
		this->_sprite->_start = 0;
		this->_sprite->_end = 0;
	}
	else{
		this->_sprite->_start = 0;
		this->_sprite->_end = 1;
	}
#pragma endregion
}
void Fleaman::Collistion(float deltaTime)
{
	if (_isDead) return;
	float x, y;
	if (swepyAABB->AABB(this->_awakeBox, Simon::getCurrentSimon()->_box, x, y)){
		_firstActive = true;
	}
	if (Simon::getCurrentSimon()->isFighting() 
		|| Boomerang::getCurrentBoomerang()->isFlying() 
		|| WeaponKnife::getCurrentKnife()->isFlying()){
		if (swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y)
			|| swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
			|| swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
			){
			if (_hp>0)
				_hp--;
			SOUND(SOUND_HIT);
		}
	}

	if (!swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
		&& !swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
		&& !Simon::getCurrentSimon()->isFighting()){
		_isHurting = false;
	}
	if (Simon::getCurrentSimon()->cantHurt())
		return;
	

	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(_damage);
	}
}
void Fleaman::Update(float deltatime){
	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}

	if (this->_isDead){
		return;
	}
	if (_countdown >= TIME_WATING)
		ChangeState(FLEAMAN_STATE::MOVE);
	if ((_currentState == FLEAMAN_STATE::WAIT)&&_firstActive)
		_countdown += deltatime;
	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite->Update(deltatime);
}
void Fleaman::ExtendCollistion(GObject* brick){
	float x, y;
	int stateCollid = swepyAABB->CollideCheck(this, brick, x, y);
	switch (stateCollid)
	{
	
	case COLLIDE_STATE::BOTTOM:
		ChangeState(FLEAMAN_STATE::WAIT);
		break;
	default:
		break;
	}
}
void Fleaman::ChangeState(int state){
	
	_currentState = state;
	switch (state)
	{
	case FLEAMAN_STATE::WAIT:
		_isSleep = true;
		break;
	case FLEAMAN_STATE::MOVE:
		_isSleep = false;
		_countdown = 0;
		if (Simon::getCurrentSimon()->_x>this->_x)
		_vx = 1.5f;
		else
		{
			_vx = -1.5f;
		}
		_vy = -3.0f;
		break;
	}
}

Fleaman::~Fleaman(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

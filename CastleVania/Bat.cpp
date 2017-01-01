#include "Bat.h"


Bat::Bat(int x, int y, int x2, int y2) :
Enemy(TYPE, x, y, x2, y2)
{
	_isSleep = true;
	_vx = _batSPEED;
	_box = Box(x, y, _batWIDTH, _batHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(BAT_SPRITE, 4, 1, 4);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	int w = x2 - x;
	int h = y2 - y;
	_awakeBox = Box(x, y, w, h, 0, 0);
	_tamp = 0;
	_hp = HP;
	_damage = DAMAGE;
}

void Bat::MoveUpdate(float deltaTime)
{
	if (_isHurting) return;
#pragma region __XU_LY_CHUYEN_DONG__
	int ynek = Simon::getCurrentSimon()->_y ;

	if (this->_isSleep){
		return;
	}
	
	if (_isMoveleft){
		if (_x <= _activeArea.left ){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
			this->_y = _activeArea.top;
		}
	}
	else{
		if (_x >= _activeArea.right){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
			this->_y = _activeArea.top;
			//this->_y = ynek;
		}
	}
	
	this->_x += int(this->_vx * deltaTime);
	this->_tamp += (this->_vx * deltaTime / 10);
	
	if (!(_y <= _activeArea.top || _y >= _activeArea.bottom))
		this->_y += int(3 * sin(float(_tamp)));
	
	this->_y += int(3 * sin(float(_tamp)));
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Bat::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (this->_isSleep){
		this->_sprite->_start = 0;
		this->_sprite->_end = 0;
	}
	else{
		this->_sprite->_start = 1;
		this->_sprite->_end = 3;
	}
#pragma endregion
}
void Bat::Collistion(float deltaTime)
{
	if (_isDead) return;
	float x, y;
	if (Simon::getCurrentSimon()->isFighting() 
		|| Boomerang::getCurrentBoomerang()->isFlying()
		|| WeaponKnife::getCurrentKnife()->isFlying()){
		if (swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y)
			|| swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
			|| swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
			){
			_isHurting = true;
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
	if (swepyAABB->AABB(this->_awakeBox, Simon::getCurrentSimon()->_box, x, y)){
		_isSleep = false;
	}
	
	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(_damage);
	}
}
void Bat::Update(float deltatime){
	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}

	if (this->_isDead){
		return;
	}
	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite->Update(deltatime);
}

void Bat::ChangeState(int state){
	if (state == BATSATE::IsSleep){
		this->_isSleep = true;
	}
	else
	if (state == BATSATE::IsAwake){
		this->_isSleep = false;
	}
}
Bat::~Bat(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

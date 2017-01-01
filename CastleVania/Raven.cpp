#include "Raven.h"


Raven::Raven(int x, int y) :
Enemy(ravenTYPE, x, y,_ravenWIDTH,_ravenHEIGHT)
{
	_isSleep = true;
	_box = Box(x, y, _ravenWIDTH, _ravenHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(_ravenSPRITE, 4, 1, 4);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	_awakeBox = Box(x - Widthbox > 0 ? x - Widthbox : 0, y - Heightbox > 0 ? y - Heightbox:0, Widthbox, Heightbox, 0, 0);
	_hp = HP;
	_damage = DAMAGE;

	_vx = Simon::getCurrentSimon()->_x < _x ? -_ravenSPEED : _ravenSPEED;
	_vy = Simon::getCurrentSimon()->_y < _y ? -_ravenSPEED : _ravenSPEED;
	_attackmode = true;
}

void Raven::MoveUpdate(float deltaTime)
{
	if (_isHurting) return;
#pragma region __XU_LY_CHUYEN_DONG__
	if (this->_isSleep){
		return;
	}
	this->_x += this->_vx*deltaTime;
	this->_y += this->_vy*deltaTime;
	
	int xsimon = Simon::getCurrentSimon()->_x;
	int ysimon = Simon::getCurrentSimon()->_y;
	if (this->_y >= ysimon + Ry + 64 || this->_y <= ysimon - Ry){
		if (this->_x <= xsimon - Rx || this->_x >= xsimon + Rx){
			if (_attackmode){
				this->_vy = 0;
			}
			else{
				this->_vy = this->_y >= ysimon + Ry +64 ? -_ravenSPEED : _ravenSPEED; 
			}
			_attackmode = !_attackmode;
			this->_vx *= -1;
		}
	}

#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Raven::SetFrame(float deltaTime)
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

void Raven::Collistion(float deltaTime)
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
	else{
		_isHurting = false;
	}
	if (Simon::getCurrentSimon()->cantHurt())
		return;
	if (swepyAABB->AABB(this->_awakeBox, Simon::getCurrentSimon()->_box, x, y)){
		_isSleep = false;
	}

	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(_damage);
	}
}

void Raven::Update(float deltatime){
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


Raven::~Raven(){
	if (_sprite != NULL){
		delete _sprite;
	}
}


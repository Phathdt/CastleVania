#include "Enemy.h"

Enemy::Enemy(int type,int x, int y, int x2, int y2) :
GObject(type,x, y, _WIDTH, _HEIGHT)
{
	_isMoveleft = false;
	_isDead = false;
	_vy = GRAVITY;
	_vx = _SPEED;
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
	_activeArea.top = y;
	_activeArea.left = x;
	_activeArea.right = x2;
	_activeArea.bottom = y2;
	_isHurting = false;
	swepyAABB = new CSweptAABB();
	this->SetFrame(0);
}
Enemy::Enemy(int type, int x, int y, int x2, int y2,bool left) :
GObject(type, x, y, _WIDTH, _HEIGHT)
{
	if (!left){
		_x = x2;
	}
	_isMoveleft = false;
	_isDead = false;
	_isHurting = false;
	_vy = GRAVITY;
	_vx = _SPEED;
	_box = Box(_x, y, _WIDTH, _HEIGHT, _vx, _vy);
	_activeArea.top = y;
	_activeArea.left = x;
	_activeArea.right = x2;
	_activeArea.bottom = y2;
	swepyAABB = new CSweptAABB();
	this->SetFrame(0);
}
void Enemy::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	if (_isHurting) return;
	if (_isMoveleft){
		if (_x < _activeArea.left){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
		}
	}
	else{
		if (_x > _activeArea.right){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
		}
	}

	this->_x += int(this->_vx * deltaTime);
	int a = 0;
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Enemy::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	//
#pragma endregion
}

void Enemy::Update(float deltatime){
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


void Enemy::Draw(){
	if (this->_isDead){
		if (_timeDeath<=DEATH_TIME)
		this->DrawDeath();
		return;
	}
	switch (_type)
	{
	case TypeGame::Enemy_Medusahead:
		int a = 0;
		break;
	
	}
	if (!this->_isMoveleft){
		this->_sprite->DrawFlipX(_x, _y);
	}
	else{
		this->_sprite->Draw(_x, _y);
	}
}
Enemy::~Enemy(){
	if (_sprite != NULL){
		delete _sprite;
	}
}
void Enemy::Collistion(float deltaTime)
{
	if (_isDead ) return;
	float x, y;
	if (Simon::getCurrentSimon()->isFighting() 
		|| Boomerang::getCurrentBoomerang()->isFlying()
		|| WeaponKnife::getCurrentKnife()->isFlying()){
		if ((swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y) && !_isHurting)
			|| (swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y) && !_isHurting)
			|| (swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y) && !_isHurting)
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
	
	
	/*if (Simon::getCurrentSimon()->GetState() == STATE::CANT_HURT)
	return;*/
	if (Simon::getCurrentSimon()->cantHurt())
		return;
	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);

		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(_damage);
	}
}

#include "BonePillar.h"
#include "Simon.h"
#include "FireBall.h"

BonePillar::BonePillar(int x, int y) :
GObject(4, x, y, _bplWIDTH, _bplHEIGHT)
{
	_isMoveleft = false;
	_isDead = false;
	_box = Box(x, y, _bplWIDTH, _bplHEIGHT);
	_awakeBox = Box(x - 170, y, 340, _bplHEIGHT);
	_flag1 = false;
	_flag2 = false;
	_flag3 = false;

	GTexture* texture1 = new GTexture(_bplSPRITE, 1, 1, 1);
	GTexture* texture2 = new GTexture(_SPRITE1, 1, 1, 1);

	_sprite = new GSprite(texture1, 0);

	_fireball1 = new FireBall(_x, _y + 12);
	_fireball2 = new FireBall(_x, _y + 12);
	_fireball3 = new FireBall(_x, _y + 12);
	_hp = bplHP;
	


}

void BonePillar::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	if (Simon::getCurrentSimon()->_x < this->_x)
		_isMoveleft = true;
	else
		_isMoveleft = false;

}

void BonePillar::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	//
#pragma endregion
}

void BonePillar::Update(float deltatime){
	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}
	if (this->_isDead||this->_isSleep){
		return;
	}

	_time1 += deltatime;
	if (_flag1 == true)
		_fireball1->Update(deltatime);
	if (_flag2 == true)
		_fireball2->Update(deltatime);
	if (_flag3 == true)
		_fireball3->Update(deltatime);
	if (_time1 >= 200 || _time2>0)
		_time2 += deltatime;
	if (_time2 >= 200 || _time3 > 0)
		_time3 += deltatime;
	if (_time1 >= 600)
	{
		_fireball1 = new FireBall(_x, _y + 12);
		_flag1 = false;
		_time1 = 0;
	}
	if (_time2 >= 600)
	{
		_fireball2 = new FireBall(_x, _y + 12);
		_flag2 = false;
		_time2 = 0;
	}
	if (_time3 >= 600)
	{
		_fireball3 = new FireBall(_x, _y + 12);
		_flag3 = false;
		_time3 = 0;
	}
	this->MoveUpdate(deltatime);
	this->_sprite->Update(deltatime);
}

void BonePillar::Draw(){
	if (this->_isDead){
		if (_timeDeath <= DEATH_TIME)
			this->DrawDeath();
		return;
	}
	if (!this->_isMoveleft){
		this->_sprite->DrawFlipX(_x, _y);
	}
	else{
		this->_sprite->Draw(_x, _y);
	}
	if (_isSleep) return;
	if (_time1 > 0)
	{
		_fireball1->Draw();
		_flag1 = true;
	}
	if (_time2 >  0)
	{
		_fireball2->Draw();
		_flag2 = true;
	}
	if (_time3 > 0)
	{
		_fireball3->Draw();
		_flag3 = true;
	}
}

void BonePillar::Collistion(float deltaTime){
	if (_isDead) return;
	float x, y;
	if (Simon::getCurrentSimon()->isFighting() 
		|| Boomerang::getCurrentBoomerang()->isFlying() 
		|| WeaponKnife::getCurrentKnife()->isFlying()){
		if ((swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y) &&!_isHurting) 
			|| (swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y) &&!_isHurting )
			|| (swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y) &&!_isHurting )
			){
			_isHurting = true;
			if (_hp>0)
				_hp--;
			SOUND(SOUND_HITCANON);
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
	if (_isSleep) return;
	
	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(DAMAGE);
	}

	if (_flag1==true && swepyAABB->AABB(_fireball1->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(_fireball1->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(DAMAGE);
		_flag1 == false;
		_fireball1 = new FireBall(_x, _y + 12);

	}

	if (_flag2 == true && swepyAABB->AABB(_fireball2->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(_fireball2->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(DAMAGE);
		_flag2 == false;
		_fireball2 = new FireBall(_x, _y + 12);


	}

	if (_flag3 == true && swepyAABB->AABB(_fireball1->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(_fireball3->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(DAMAGE);
		_flag3 == false;
		_fireball3 = new FireBall(_x, _y + 12);


	}

}

BonePillar::~BonePillar(){
	if (_sprite != NULL){
		delete _sprite;
	}
}


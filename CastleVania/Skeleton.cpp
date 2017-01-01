#include "Skeleton.h"


Skeleton::Skeleton(int x, int y) :
Enemy(_skeletonTYPE, x, y, _skeletonWIDTH, _skeletonHEIGHT)
{
	_isSleep = true;
	_vx = 0;
	_vy = 0;
	_box = Box(x, y, _skeletonWIDTH, _skeletonHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(_skeletonSPRITE, 2, 1, 4);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	_awakeBox = Box(x - 100, y - 100, 200, 200, 0, 0);
	_hp = _skeletonHP;
	_damage = _skeletonDAMAGE;
	_isMoveleft = false;


	_timeMove = 0;
}

void Skeleton::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__

	if (this->_currentState == SKELETON_STATE::_WAIT){
		return;
	}

	if (this->_currentState == SKELETON_STATE::_MOVE){
		return;
	}

	if (this->_currentState == SKELETON_STATE::_DAMAGE)
	{
		_timeMove += deltaTime;
		if (_timeMove >= 18)
			_vx = 0.4f;
		else
			_vx = -0.4f;
		if (_timeMove >= 45)
			_timeMove = 0;


		this->_x += this->_vx*deltaTime;
		_box.x = _x;
		_box.y = _y;
		_box.vx = _vx;
		_box.vy = _vy;
		return;
	}
	else		
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

void Skeleton::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (this->_isSleep){
		this->_sprite->_start = 0;
		this->_sprite->_end = 1;
	}
	else{
		this->_sprite->_start = 0;
		this->_sprite->_end = 1;
	}
#pragma endregion
}
void Skeleton::Collistion(float deltaTime)
{
	if (_isDead) return;
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
	if (Simon::getCurrentSimon()->cantHurt())
		return;
	if (_checkbone == true && swepyAABB->AABB(_bone->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(_bone->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(_skeletonDAMAGE);
		_checkbone == false;
		_bone = new Bone(_x, _y);
		_timeExists = 0;
		_checkbone = false;

	}
	


	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
		Simon::getCurrentSimon()->Hurt(_damage);
	}
}
void Skeleton::Update(float deltatime){
	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}

	if (this->_isDead){
		return;
	}
	if (_currentState == SKELETON_STATE::_DAMAGE)
	{
		if ((Simon::getCurrentSimon()->_x <= this->_x))
			_isMoveleft = true;
		else
			_isMoveleft = false;

	}
	if (abs(Simon::getCurrentSimon()->_y - _y) <= 200 && abs(Simon::getCurrentSimon()->_x - _x) <= 250)
	{
		_firstActive = true;
	}

	if (_countdown >= _skeletonTIME_WATING)
		ChangeState(SKELETON_STATE::_JUMP);
	if ((_currentState == SKELETON_STATE::_WAIT) && _firstActive)
		_countdown += deltatime;

#pragma region Xử lý Skeleton ném xương

	if (_firstbone && _firstdame)
	{
		_bone = new Bone(_x, _y);
		_firstbone = false;
	}

	if (_timeExists > 0)
	{
		_checkbone = true;
		_bone->Update(deltatime);
	}

	if (_isThrow)
	{
		_timeExists += deltatime;

	}

	if (_timeExists >= 600)
	{
		_timeExists = 0;
		_bone = new Bone(_x, _y);
		_checkbone = false;
	}

#pragma endregion


	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite->Update(deltatime);
}
void Skeleton::ExtendCollistion(GObject* brick){
	float x, y;
	int stateCollid = swepyAABB->CollideCheck(this, brick, x, y);
	switch (stateCollid)
	{

	case COLLIDE_STATE::BOTTOM:
		if (_isSleep)
			return;
		else
			ChangeState(SKELETON_STATE::_JUMP);
		break;
	case COLLIDE_STATE::TOP:
		if (_isSleep)
			return;
		else
			ChangeState(SKELETON_STATE::_JUMP);
		break;
	case COLLIDE_STATE::LEFT:
		if (_isSleep)
			return;
		else
			ChangeState(SKELETON_STATE::_JUMP);
		break;
	case COLLIDE_STATE::RIGHT:
		if (_isSleep)
			return;
		else
			ChangeState(SKELETON_STATE::_JUMP);
		break;
	default:
		break;
	}
}
void Skeleton::ChangeState(int state){

	_currentState = state;
	switch (state)
	{
	case SKELETON_STATE::_WAIT:
		_isSleep = true;
		break;
	case SKELETON_STATE::_JUMP:
		_isSleep = false;
		_countdown = 0;
		if (Simon::getCurrentSimon()->_y <= this->_y && abs(Simon::getCurrentSimon()->_x - _x) <= 300)
		{
			if (abs(Simon::getCurrentSimon()->_x - _x) <= _dDame)
			{
				ChangeState(SKELETON_STATE::_DAMAGE);

			}
			else
				ChangeState(SKELETON_STATE::_MOVE);


		}
		if (Simon::getCurrentSimon()->_x>this->_x)
			_vx = 1.6f;
		else
		{
			_vx = -1.6f;
		}
		_vy = -3.0f;
		break;
	case SKELETON_STATE::_DAMAGE:
		_isSleep = true;
		_isThrow = true;
		if (!_firstbone && !_firstdame)
		{
			_firstbone = true;
			_firstdame = true;
		}
		//ChangeState(SKELETON_STATE::_WAIT);

		break;
	case SKELETON_STATE::_MOVE:
		if (Simon::getCurrentSimon()->_y <= this->_y && abs(Simon::getCurrentSimon()->_x - _x) <= 300)
		{
			if (abs(Simon::getCurrentSimon()->_x - _x) <= _dDame)
			{
				ChangeState(SKELETON_STATE::_DAMAGE);

			}
		}
		break;
	}
}


void Skeleton::Draw()
{
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
	if (_timeExists > 0)
	{
		_bone->Draw();
	}
}

Skeleton::~Skeleton(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

#include "Simon.h"



Simon* Simon::_simon = 0;
Simon::Simon(int x, int y) :
GObject(TYPE, x, y, SIMON_WIDTH, SIMON_HEIGHT)
{
	_isMoveleft = true;
	_isMoveright = false;
	_isOnStair = false;
	_isJumping = false;
	_isFalling = true;
	_isSiting = false;
	_canGoStair = false;
	_isOnStair2 = false;
	_currentStateGame = 1;
	_canGoLeft = true;
	_canGoRight = true;
	onGoto = false;
	_hp = 16;
	_heart = 5;
	_cantHurt = false;
	_timeCantHurt = false;
	_currentLV = 2;
	this->_drawhurt = 0;
	_stateCurrent = STATE::IS_FALLING;
	_vy = GRAVITY;
	_box = Box(x, y, SIMON_WIDTH, SIMON_HEIGHT,_vx,_vy);
	
	GTexture* simonTT = new GTexture(SIMON_SPRITE, 8, 3, 24,false);
	_sptrite = new GSprite(simonTT, SIMON_Animation_RATE);
}

void Simon::MoveUpdate(float deltaTime)
{
	if (_hp <= 0) return;
#pragma region __XU_LY_CHUYEN_DONG__

	if (this->_isFighting ) {
		if (this->_isOnMovingBrick)
		{
			this->_x += int(this->_vx * deltaTime);
			_box.x = _x;
			_box.y = _y;
			_box.vx = _vx;
			_box.vy = _vy;
		}

		if (!(this->_isJumping||this->_isFalling))
			return;
	}

	if (this->_stateCurrent == STATE::CANT_HURT){
		//this->_x += int(this->_vx * deltaTime);
		if (_isMoveleft&&_canGoRight){
			this->_x += int(this->_vx * deltaTime);
		}
		if (_isMoveright&&_canGoLeft)
		{
			this->_x += int(this->_vx * deltaTime);
		}
		this->_y += int(this->_vy * deltaTime);
		if (_vy<HURT_FALL_SPEED)
		_vy += 0.2f;
		this->onGoto = false;
		_box.x = _x;
		_box.y = _y;
		_box.vx = _vx;
		_box.vy = _vy;
		return;
	}
	if (this->_stateCurrent == STATE::ON_BRICK_MOVING)
	{
		this->_x += int(this->_vx * deltaTime );
		//this->_vx = _currentMoving.vx;
		_box.x = _x;
		_box.y = _y;
		_box.vx = _vx;
		_box.vy = _vy;
		return;
	}
	//Kiem tra doi tuong co nhay duoc hay ko
	if (this->_isOnStair)
	{
		if (KeyBoard::getCurrentKeyBoard()->keyDown())
			int a = 0;
		this->_x += int(this->_vx * deltaTime);
		this->_y += int(this->_vy * deltaTime);
		
		if ((this->_x >= this->xDestinate) && (this->_vx>0))
		this->_vx = 0;
		if ((this->_y >= this->yDestinate) && (this->_vy>0))
			this->_vy = 0;
		if ((this->_x <= this->xDestinate) && (this->_vx<0))
			this->_vx = 0;
		if ((this->_y <= this->yDestinate) && (this->_vy<0))
			this->_vy = 0;
		
		if (this->_vx == 0 && this->_vx == 0)
			this->onGoto = false;
	}
	else
	{
		
		if (this->_stateCurrent == STATE::IS_STANDING)
		{
			this->_vx = 0;
			_vy = GRAVITY;
		}
		else
		{
			if (this->_isFalling){
				_vy = GRAVITY;
				this->_y += int(_vy*deltaTime);
				if (this->_lastState == STATE::IS_JUMPING || this->_lastState == STATE::IS_JUMPFIGH)
				if ((this->_vx>0 && this->_canGoRight) || (this->_vx<0 && this->_canGoLeft))
				this->_x += int(this->_vx * deltaTime/1.5f );
			}
		}

		if (this->_isMoveleft&&this->_canGoLeft&&!this->_isFalling)
		{
			if (this->_vx < 0)
			{
				this->_x += int(this->_vx * deltaTime );
			}
		}
		else if (this->_isMoveright&&this->_canGoRight&&!this->_isFalling)
		{
			if (this->_vx > 0)
			{
				this->_x += int(this->_vx * deltaTime );
			}
		}
		if (this->_stateCurrent == STATE::IS_JUMPING || this->_stateCurrent == STATE::IS_JUMPFIGH){
			this->_y += int(this->_vy * deltaTime);
			if ((this->_vx>0 && this->_canGoRight) || (this->_vx<0 && this->_canGoLeft))
				this->_x += int(this->_vx * deltaTime / 1.5f);
			if (_vy < -0.3)
				_vy += 0.2f;
			else {
				this->_stateCurrent = STATE::IS_FALLING;
				this->_lastState = STATE::IS_JUMPING;
				_isFalling = true;
				_isJumping = false;
			}
		}
		_canGoRight = true;
		_canGoLeft = true;
	}

	
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;

	this->_y += dy;
	_box.y += dy;
	dy = 0;
}

void Simon::SetFrame(float deltaTime)
{
	if (_hp <= 0){
		this->_sptrite->_start = 9;
		this->_sptrite->_end = 9;
		return;
	}

#pragma region __XU_LY_CHUYEN_DOI_FRAME__

	if (!this->_isOnStair) //dang o duoi dat
	{
		this->_sptrite->_start = 0;
		this->_sptrite->_end = 0;
		switch (this->_stateCurrent)
		{
		case STATE::IS_STANDING:
		{
								   this->_sptrite->_start = 0;
								   this->_sptrite->_end = 0;
								   if (_isFighting ){
									   this->_sptrite->_start = 5;
									   this->_sptrite->_end = 7;
								   }
								   if ((_isFighting) && this->_isSiting){
									   this->_sptrite->_start = 15;
									   this->_sptrite->_end = 17;
								   }
								   break;
		}
		case STATE::IS_JOGGING://Chay bo
		{
								   this->_sptrite->_start = 0;
								   this->_sptrite->_end = 3;
								   break;
		}
		case STATE::IS_JUMPING: 
		case STATE::IS_SITTING :
		{
								  this->_sptrite->_start = 4;
								  this->_sptrite->_end = 4;
								  if (_isFighting ){
									  this->_sptrite->_start = 15;
									  this->_sptrite->_end = 17;
								  }
								  break;
		}
		case STATE::IS_FIGHTING:
		{
									this->_sptrite->_start = 5;
									this->_sptrite->_end = 7;
									break;
		}
		case STATE::IS_PASSGATE	:
		{
									this->_sptrite->_start = 9;
									this->_sptrite->_end = 9;
									break;
		}
		case STATE::IS_SITFIGHT: 
		case STATE::IS_JUMPFIGH:
		{
								   this->_sptrite->_start = 15;
								   this->_sptrite->_end = 17;
								   break;
		}
		case STATE::CANT_HURT:{
								  this->_sptrite->_start = 8;
								  this->_sptrite->_end = 8;
								  break;
		}
		default:
		{
				   break;
		}
		}
	}
	else //tren cau thang
	{
		switch (this->_stateCurrent)
		{
		
		case STATE::IS_UPING:
		{
								if (onGoto){
									this->_sptrite->_start = 12;
									this->_sptrite->_end = 13;
								}
								else
								{
									this->_sptrite->_start = 12;
									this->_sptrite->_end = 12;
								}								
								break;
		}
		case STATE::IS_DOWNING:
		{
								  if (onGoto){
									  this->_sptrite->_start = 10;
									  this->_sptrite->_end = 11;
								  }
								  else
								  {
									  this->_sptrite->_start = 10;
									  this->_sptrite->_end = 10;
								  }
								  break;
		}
		case STATE::IS_UPFIGHT:
		{
								  this->_sptrite->_start = 21;
								  this->_sptrite->_end = 23;
								  break;
		}
		case STATE::IS_DOWNFIGHT:
		{
									this->_sptrite->_start = 18;
									this->_sptrite->_end = 20;
									break;
		}
		case STATE::CANT_HURT:{
								  this->_sptrite->_start = 8;
								  this->_sptrite->_end = 8;
								  break;
		}
		default:
			break;
		}
	}
#pragma endregion
}

void Simon::Jump(){
	if (_hp <= 0)
		return;
	if (!_isJumping){
		if (this->_isFighting){
			this->_stateCurrent = STATE::IS_JUMPFIGH;
		}
		else
		{
			this->_stateCurrent = STATE::IS_JUMPING;
		}
		_vy = -3.0f;
		_isJumping = true;
		if (KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_RIGHT))
			this->_vx = SIMON_SPEED;
		if (KeyBoard::getCurrentKeyBoard()->IsKeyDown(DIK_LEFT))
			this->_vx = -SIMON_SPEED;
	}
}

void Simon::Fight(int weapon){
	if (_hp <= 0)
		return;
	SOUND(SOUND_WHIPATK);
	FightWith = weapon;
#pragma region __XU_LY_PHIM_DANH <state va frame>__
	if (!this->_isFighting )
	{
		this->_lastState = this->_stateCurrent;
		this->_isFighting = true;

		switch (this->_stateCurrent)
		{
		case STATE::IS_JUMPING:
			this->_stateCurrent = STATE::IS_JUMPFIGH;
			break;
		case STATE::IS_SITTING:
			this->_stateCurrent = STATE::IS_SITFIGHT;
			break;
		case STATE::IS_DOWNING:
			this->_stateCurrent = STATE::IS_DOWNFIGHT;
			break;
		case STATE::IS_UPING:
			this->_stateCurrent = STATE::IS_UPFIGHT;
			break;
		case STATE::IS_STANDING:
		case STATE::ON_BRICK_MOVING:
			this->_stateCurrent = STATE::IS_FIGHTING;
			break;
		default:
			break;
		}
	}
#pragma endregion
	if (FightWith == 1)
		Boomerang::getCurrentBoomerang()->Fly();
	if (FightWith == 2)
		WeaponKnife::getCurrentKnife()->Fly();
}

void Simon::InputUpdate(float deltaTime)
{
	if (_hp <= 0)
		return;
	if (this->_isFighting){
		return;
	}
	
#pragma region __KHONG_CO_SU_KIEN_PHIM__
	
	this->_keyDown = KeyBoard::getCurrentKeyBoard()->GetKeyDown();
	this->_keyUp = KeyBoard::getCurrentKeyBoard()->GetKeyUp();
	if (!this->_isJumping)
	{
		
		//this->_vy = 0;

		if (!this->_isOnStair&&!this->_isFalling && (this->_stateCurrent != STATE::CANT_HURT) && (this->_stateCurrent != STATE::ON_BRICK_MOVING))
		{
			this->_vx = 0;
			//this->_stateCurrent = STATE::IS_FALLING;
		}
		else
		{

		}
		if (this->_stateCurrent != STATE::IS_FALLING 
			&& (!this->_isFighting )
			&& (this->_stateCurrent != STATE::IS_UPING)
			&& (this->_stateCurrent != STATE::IS_DOWNING)
			&& (this->_stateCurrent != STATE::CANT_HURT)
			&& (this->_stateCurrent != STATE::ON_BRICK_MOVING)
			)
			_stateCurrent = STATE::IS_STANDING;
	}
	this->_isSiting = false;
#pragma endregion


#pragma region __XU_LY_PHIM_DI_QUA_TRAI_HOAC_PHAI__
	if (this->_stateCurrent == STATE::CANT_HURT) return;
	if (this->_isOnStair) return;
	if ((KeyBoard::getCurrentKeyBoard()->keyLeft() || KeyBoard::getCurrentKeyBoard()->keyRight())
		&& this->_stateCurrent != STATE::IS_JUMPING&& this->_stateCurrent != STATE::IS_FALLING)
	{
		this->_stateCurrent = STATE::IS_JOGGING;
		if (KeyBoard::getCurrentKeyBoard()->keyRight())
		{
			this->_isMoveright = true;
			this->_isMoveleft = false;
			this->_vx = SIMON_SPEED;
		}
		else
		{
			this->_isMoveright = false;
			this->_isMoveleft = true;
			this->_vx = -SIMON_SPEED;
		}
	}
#pragma endregion

	//this->_stateCurrent = STATE::IS_FIGHTING;

#pragma region __XU_LY_PHIM_DI_LEN_ XUONG__
	if (KeyBoard::getCurrentKeyBoard()->keyUp()){
		
	}
	if (KeyBoard::getCurrentKeyBoard()->keyDown()){
		if (_canGoStair){
			this->_stateCurrent = STATE::IS_DOWNING;
		}
		else{
				this->_stateCurrent = STATE::IS_SITTING;
				this->_isSiting = true;
		}
	}
#pragma endregion


}

void Simon::Reset(){
	if (_currentLV == 2){
		_x = 3742;
		_y = 1453;
		GCamera::getCurrentCamera()->getCurrentCamera()->ChangeState(1);
		_cantHurt = false;
		_stateCurrent = STATE::IS_FALLING;
		_isFalling = true;
		_currentStateGame = 1;
		_bossHP = 16;
		reset = true;
		THEME(THEME_STATE1);
	}
	else{
		_x = 1373;
		_y = 1030;
		GCamera::getCurrentCamera()->getCurrentCamera()->ChangeState(1);
		_cantHurt = false;
		_stateCurrent = STATE::IS_FALLING;
		_isFalling = true;
		_currentStateGame = 1;
		_bossHP = 16;
		reset = true;
		THEME(THEME_STATE4);
	}
}

void Simon::Cheat(){
	SOUND(SOUND_CHEATE);
	if (_currentLV == 2){
		_x = 1308;
		_y = 236;
		GCamera::getCurrentCamera()->getCurrentCamera()->ChangeState(4);
		_cantHurt = false;
		_stateCurrent = STATE::IS_FALLING;
		_isFalling = true;
	}

	if (_currentLV == 3){
		_x = 6625;
		_y = 150;
		_cantHurt = false;
		GCamera::getCurrentCamera()->getCurrentCamera()->ChangeState(3);
		_stateCurrent = STATE::IS_FALLING;
		_isFalling = true;
	}
}

void Simon::Update(float deltatime){

	if (_hp <= 0){
		_life--;
		if (_life > 0){
			_hp = 16;
			Reset();
		}
			
	}
	if (_life <= 0){
		_timeDeath += deltatime;
		_isDeath = true;
	}
	if (_cantHurt){
		_drawhurt += deltatime;
	}
	else
	{
		_drawhurt = 0;
	}
	this->InputUpdate(deltatime);
	this->SetFrame(deltatime);
	this->MoveUpdate(deltatime);
	MoveState();
	this->_sptrite->Update(deltatime);
	if (_isFighting && FightWith==0){
		Whip::getCurrentWhip()->Update(deltatime);
	}
	Boomerang::getCurrentBoomerang()->Update(deltatime);
	WeaponKnife::getCurrentKnife()->Update(deltatime);
	
}

void Simon::MoveState(){
	if (_hp <= 0)
		return;
	if (!_isOnStair) return;
	if (_currentLV == 2){
		switch (_currentStateGame)
		{
		case 1:
			if (_y < 1220){
				this->ChangeState(STATE::IS_UPING);
				this->isMoveLeft(false);
				this->isMoveRight(true);
				this->_isOnStair = true;
				this->onGoto = true;
				this->_x = 3841;
				this->_y = 1140;
				GCamera::getCurrentCamera()->ChangeState(2);
				_currentStateGame = 2;
				return;
			}
			break;
		case 2:
			if (_y < 833){
				this->ChangeState(STATE::IS_UPING);
				this->isMoveLeft(false);
				this->isMoveRight(true);
				this->_isOnStair = true;
				this->onGoto = true;
				this->_x = 1664;
				this->_y = 753;
				GCamera::getCurrentCamera()->ChangeState(3);
				_currentStateGame = 3;
				return;
			}
			break;
		case 3:
			if (_y < 450){
				this->ChangeState(STATE::IS_UPING);
				this->isMoveLeft(false);
				this->isMoveRight(true);
				this->_isOnStair = true;
				this->onGoto = true;
				this->_x = 1343;
				this->_y = 369;
				GCamera::getCurrentCamera()->ChangeState(4);
				_currentStateGame = 4;
				return;
			}
			break;
		default:
			break;
		}
	}
else
{
	switch (_currentStateGame)
	{
	case 1:
		if (_y < 852){
			this->ChangeState(STATE::IS_UPING);
			this->isMoveLeft(true);
			this->isMoveRight(false);
			this->_isOnStair = true;
			this->_isOnStair2 = true;
			this->onGoto = true;
			this->_x = 162;
			this->_y = 819-64;
			GCamera::getCurrentCamera()->ChangeState(2);
			_currentStateGame = 2;
			return;
		}
		break;
	case 2:
		if (_y < 472){
			this->ChangeState(STATE::IS_UPING);
			this->isMoveLeft(true);
			this->isMoveRight(false);
			this->_isOnStair = true;
			this->onGoto = true;
			this->_x = 2721;
			this->_y = 366;
			GCamera::getCurrentCamera()->ChangeState(3);
			_currentStateGame = 3;
			return;
		}
		break;
	
	default:
		break;
	}
}

}

void Simon::Draw(){
if (_timeDeath > DEATH_TIME)
		return;
if (_cantHurt){
		if (_drawhurt <= TIME_CANT_HURT){
			if ((_drawhurt % 30) <= (20)){
				return;
			}
		}
else
		_cantHurt = !_cantHurt;
	}
	/*if ((_drawhurt  %30) <= (20)){
		_drawhurt +=3;
		return;
	}
	_drawhurt +=3;*/

if (this->_isMoveright){
		//this->_sptrite->DrawFlipX(_x-10, _y);
		this->_sptrite->DrawFlipX(_x-10, _y);
	}
	else{
		//this->_sptrite->Draw(_x-11, _y);
		this->_sptrite->Draw(_x-14, _y);
	}
	if (FightWith==0)
	 Whip::getCurrentWhip()->Draw();
	Boomerang::getCurrentBoomerang()->Draw();
	WeaponKnife::getCurrentKnife()->Draw();
}

void Simon::ChangeState(int state){
	/*if (_stateCurrent == STATE::IS_UPING&& state == STATE::IS_STANDING &&_canGoStair)
		return;*/
	_lastState = _stateCurrent;
	/*if (_lastState == STATE::CANT_HURT){
		this->_hp -= 1;
	}*/
	this->_stateCurrent = state;
	switch (state) {
	case STATE::IS_STANDING:
		this->_isFalling = false; 
		this->_isJumping = false; 
		if (this->_isSiting)
			this->_stateCurrent = STATE::IS_SITTING;
		this->_isOnMovingBrick = false;
		break;
	case STATE::IS_FALLING: this->_isFalling = true;
		this->_isJumping = false;  break;
	case STATE::IS_UPING: this->_isOnStair = true;
		if (this->_vy == GRAVITY) this->_vy = 0; break;
	case STATE::IS_DOWNING: this->_isOnStair = true;
		if (this->_vy == GRAVITY) this->_vy = 0; break;
	case STATE::CANT_HURT: 
		this->_isOnStair = false;
		this->_cantHurt = true;
		if (_isMoveleft&&_canGoRight){
			this->_vx = 1.2f;
			this->_x += int(this->_vx * 3);
		}
		if (_isMoveright&&_canGoLeft)
		{
			this->_vx = -1.2f;
			this->_x += int(this->_vx * 3);
		}
		this->_vy = -2.0f;
		
		this->_y += int(this->_vy * 3);
		this->_box.x = this->_x;
		this->_box.y = this->_y;
		this->_box.vx = this->_vx;
		this->_box.vy = this->_vy;
		break;
	case STATE::ON_BRICK_MOVING:
		this->_isFalling = false;
		this->_isJumping = false; 
		this->_isOnMovingBrick = true;
		break;
	}
}

Simon* Simon::getCurrentSimon(){
	if (!_simon)
		_simon = new Simon(3742, 1453);
	return _simon;
}


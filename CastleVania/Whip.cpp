#include "Whip.h"
#include <string>
Whip* Whip::_whip = 0;
Whip::Whip(int x, int y) :
GObject(TYPE, x, y, _WIDTH, _HEIGHT)
{
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
	GTexture* ttleft = new GTexture(_SPRITE_LEFT, 4, 3, 12,false);
	GTexture* ttright = new GTexture(_SPRITE_RIGHT, 4, 3, 12,false);
	_sprite_left = new GSprite(ttleft, SIMON_Animation_RATE);
	_sprite_right = new GSprite(ttright, SIMON_Animation_RATE);
	SetFrame(0); //1 kieu roi

	//vi tri dau tien theo con simon
	MoveUpdate(0);
}

void Whip::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	this->_x = Simon::getCurrentSimon()->_x;
	this->_y = Simon::getCurrentSimon()->_y;
	
	if (Simon::getCurrentSimon()->isFighting()) {
		if (Simon::getCurrentSimon()->isMoveLeft()){
			switch (this->_sprite_left->Done)
			{
			case-1:this->_x -= 80;
				_box.x = _x+135;
				_box.y = _y;
				_box.w = 23;
				_box.h = 58;
				break;
			case 0:this->_x -= 85;
				_box.x = _x + 120;
				_box.y = _y;
				_box.w = 40;
				_box.h = 46;
				break;
			case 1:case 2:
				this->_x -= 85;
				_box.x = _x +30;
				_box.y = _y;
				_box.w = 66;
				_box.h = 31; break;
			}

		}
		if (Simon::getCurrentSimon()->isMoveRight()){
			switch (this->_sprite_right->Done)
			{
			case-1:
				this->_x -= 140;
				_box.x = _x + 135;
				_box.y = _y;
				_box.w = 23;
				_box.h = 58; break;
			case 0:
				this->_x -= 140;
				_box.y = _y;
				_box.x = _x + 120;
				_box.w = 40;
				_box.h = 46; 
				break;
			case 1: case 2:
				this->_x += 35;
				_box.y = _y;
				_box.x = _x;
				_box.w = 66;
				_box.h = 31; break;
			}
		}
	}
	else{
		_box.y = 0;
		_box.x = 0;
		_box.w = 0;
		_box.h = 0;
	}
#pragma endregion
	//_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Whip::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite_left->_start = 0;
	this->_sprite_left->_end = 2;

	this->_sprite_right->_start = 0;
	this->_sprite_right->_end = 2;
#pragma endregion
}

void Whip::Update(float deltatime){
	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite_left->Update(deltatime);
	this->_sprite_right->Update(deltatime);
	
	if (this->_sprite_left->Done==2){
		Simon::getCurrentSimon()->ChangeState(deltatime);
		this->_sprite_left->Done = -1;
		this->_sprite_left->Reset();
		OutputDebugString((LPCWSTR)"\n");
	}
	if (this->_sprite_right->Done == 2){
		Simon::getCurrentSimon()->ChangeState(deltatime);
		this->_sprite_right->Done = -1;
		this->_sprite_right->Reset();
		OutputDebugString((LPCWSTR)"\n");
	}
}

void Whip::Draw(){
	if (!Simon::getCurrentSimon()->isFighting())
		return;
	
	if (Simon::getCurrentSimon()->isMoveRight()){
		this->_sprite_right->Draw(_x, _y);
		
		wchar_t buffer[256];
		wsprintfW(buffer, L"x=%d,done=%d|", _x,_sprite_right->Done);
		OutputDebugString((LPCWSTR)buffer);
	}
	else{
		this->_sprite_left->Draw(_x, _y);
		wchar_t buffer[256];
		wsprintfW(buffer, L"x=%d,done=%d|", _x, _sprite_left->Done);
		OutputDebugString((LPCWSTR)buffer);
	}
}

Whip* Whip::getCurrentWhip(){
	if (!_whip)
		_whip = new Whip(Simon::getCurrentSimon()->_x, Simon::getCurrentSimon()->_y);
	return _whip;
}






#include "WeaponKnife.h"
#include <string>
WeaponKnife* WeaponKnife::_weaponknife = 0;
WeaponKnife::WeaponKnife(int x, int y) :
GObject(TYPE, x, y, _WIDTH, _HEIGHT)
{
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
	GTexture* tt= new GTexture(_SPRITE, 1, 1, 1, false);
	_sprite = new GSprite(tt, SIMON_Animation_RATE);
	SetFrame(0); //1 kieu roi
	//vi tri dau tien theo con simon
	MoveUpdate(0);
	_flying = false;
	_turnlef = Simon::getCurrentSimon()->isMoveLeft();
}

void WeaponKnife::Fly(){
	
	if (_flying)
		return;

	_flying = true;
	_vy = 0;
	_vx = Simon::getCurrentSimon()->isMoveLeft() ? -1.9f : 1.9f;
	_turnlef = this->_vx > 0 ? false : true;

	this->_x = Simon::getCurrentSimon()->_x;
	this->_y = Simon::getCurrentSimon()->_y;
	done = false;
}

void WeaponKnife::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	if (!_flying)
		return;
	this->_x += int(this->_vx*deltaTime);

	if (this->_x <= GCamera::getCurrentCamera()->x
		|| this->_x >= GCamera::getCurrentCamera()->x + GCamera::getCurrentCamera()->width
		)
	{
		_flying = false;
		this->_sprite->Done = -1;
	}
	
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void WeaponKnife::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 0;
#pragma endregion
}

void WeaponKnife::Update(float deltatime){
	
	if (!this->_flying)
		return;
	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite->Update(deltatime);

	if (this->_sprite->Done == 2 && !this->done){
		this->done = true;
		Simon::getCurrentSimon()->ChangeState(deltatime);
		this->_sprite->Done = -1;
		OutputDebugString((LPCWSTR)"\n");
		if(!this->_flying)
			Fly();
	}
}

void WeaponKnife::Draw(){
	if (!this->_flying )
		return;
	if (this->_turnlef)
		this->_sprite->Draw(_x, _y);
	else
		this->_sprite->DrawFlipX(_x, _y);
}

WeaponKnife* WeaponKnife::getCurrentKnife(){
	if (!_weaponknife)
		_weaponknife = new WeaponKnife(Simon::getCurrentSimon()->_x, Simon::getCurrentSimon()->_y);
	return _weaponknife;
}







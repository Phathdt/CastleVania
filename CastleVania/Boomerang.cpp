#include "Boomerang.h"
#include <string>
Boomerang* Boomerang::_boomerang = 0;
Boomerang::Boomerang(int x, int y) :
GObject(TYPE, x, y, _WIDTH, _HEIGHT)
{
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
	GTexture* tt= new GTexture(_SPRITE, 3, 1, 3, false);
	_sprite = new GSprite(tt, SIMON_Animation_RATE);
	SetFrame(0); //1 kieu roi
	//vi tri dau tien theo con simon
	MoveUpdate(0);
	_flying = false;
	_turnlef = Simon::getCurrentSimon()->isMoveLeft();
}

void Boomerang::Fly(){
	
	if (_flying)
		return;

	_flying = true;
	_vy = 0;
	_vx = Simon::getCurrentSimon()->isMoveLeft() ? -1.5f : 1.5f;
	_going = true;
	d = 0;
	_turnlef = this->_vx > 0 ? false : true;

	this->_x = Simon::getCurrentSimon()->_x;
	this->_y = Simon::getCurrentSimon()->_y;
	done = false;
}

void Boomerang::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	if (!_flying)
		return;
	d += int(this->_vx*deltaTime);
	this->_x += int(this->_vx*deltaTime);

	if (_going) //neu dang di quay lai
	{
		if ((d < -_Rage && this->_turnlef)
			|| (d > _Rage && !this->_turnlef)
			) //quay nguoc lai
		{
			d = 0;
			this->_vx *= -1;
			this->_turnlef = !this->_turnlef;
			_going = false;
		}
	}
	else{
			int simony = Simon::getCurrentSimon()->_y;
			int simonh = Simon::getCurrentSimon()->_height/2;
			if (
				   (_turnlef && ((this->_x < Simon::getCurrentSimon()->_x && this->_y >= simony && this->_y <= simony+simonh)
					|| this->_x < GCamera::getCurrentCamera()->x )) // quay ve
				|| (!_turnlef && ((this->_x >= Simon::getCurrentSimon()->_x && this->_y >= simony && this->_y <= simony + simonh)
					|| this->_x >= GCamera::getCurrentCamera()->x + GCamera::getCurrentCamera()->width))
				){
				_flying = false;
				this->_sprite->Done = -1;
		}
	}
	
	
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Boomerang::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 2;
#pragma endregion
}

void Boomerang::Update(float deltatime){
	
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

void Boomerang::Draw(){
	if (!this->_flying )
		return;
	this->_sprite->Draw(_x, _y);
}

Boomerang* Boomerang::getCurrentBoomerang(){
	if (!_boomerang)
		_boomerang = new Boomerang(Simon::getCurrentSimon()->_x, Simon::getCurrentSimon()->_y);
	return _boomerang;
}






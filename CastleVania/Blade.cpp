#include "Blade.h"
#include "Simon.h"



Blade::Blade(int x, int y) :
GObject(bladeTYPE, x, y, _bladeWIDTH, _bladeHEIGHT)

{
	left = true;
	last_x = x;
	_vx = 0;
	_box = Box(x, y, _bladeWIDTH, _bladeHEIGHT);
	GTexture* texture1 = new GTexture(_bladeSPRITE, 2, 1, 2);
	_sprite = new GSprite(texture1, 0);
	_vx = _bladeSPEED;

	_tamp = 0;
}

void Blade::ChangeState(int state){
	//
}

void Blade::Update(float DeltaTime)
{
	if (Simon::getCurrentSimon()->_x < last_x)
		left = true;
	else
		left = false;



	if (Simon::getCurrentSimon()->_x < this->last_x && flag1 == false)
	{
		_vx = -_vx;
		flag = true;
		flag1 = true;
	}
	else
	if (flag == false)
	{
		_vx = _vx;
		flag1 = true;
		flag = true;

	}

	this->_x += int(this->_vx * DeltaTime);
	this->_tamp += (this->_vx * DeltaTime / 30);
	this->_y += int(2 * (3 * sin(float(abs(_tamp)))));

	_box = Box(_x, _y, _bladeWIDTH, _bladeHEIGHT);
	_sprite->Update(DeltaTime);

}

void Blade::Draw()
{
	if (left == false)
		this->_sprite->DrawFlipX(_x, _y);
	else
		this->_sprite->Draw(_x, _y);
}
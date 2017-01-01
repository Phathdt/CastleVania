#include "FireBall.h"
#include "Simon.h"



FireBall::FireBall(int x, int y) :
GObject(fbTYPE, x, y, _fbWIDTH, _fbHEIGHT)

{
	last_x = x;
	_vx = _fbSPEED;
	_box = Box(x, y, _WIDTH, _HEIGHT);
	GTexture* texture1 = new GTexture(_fbSPRITE, 1, 1, 1);
	_sprite = new GSprite(texture1, 0);


}

void FireBall::ChangeState(int state){
	//
}

void FireBall::Update(float DeltaTime)
{
	if (flag == true && flag1 == true)
	{
		flag = false;
		flag = false;
	}

	if (Simon::getCurrentSimon()->_x < this->last_x && flag1 == false)
	{
		_vx = -_fbSPEED;
		flag = true;
	}
	else
	if (flag == false)
	{
		_vx = _fbSPEED;
		flag1 = true;
	}

	this->_x += int(this->_vx * DeltaTime);

	_box = Box(_x, _y, _fbWIDTH, _fbHEIGHT);
}

void FireBall::Draw()
{
	_sprite->Draw(_x, _y);
}
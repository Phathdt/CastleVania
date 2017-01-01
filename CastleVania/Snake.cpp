#include "Snake.h"
#include "Simon.h"



Snake::Snake(int x, int y) :
GObject(snakeTYPE, x, y, _snakeWIDTH, _snakeHEIGHT)

{
	left = true;
	last_x = x;
	_vx = 0;
	_box = Box(x, y, _snakeWIDTH, _snakeHEIGHT);
	GTexture* texture1 = new GTexture(_snakeSPRITE, 1, 1, 1);
	_sprite = new GSprite(texture1, 0);


}

void Snake::ChangeState(int state){
	//
}

void Snake::Update(float DeltaTime)
{
	if (Simon::getCurrentSimon()->_x < last_x)
		left = true;
	else
		left = false;

		if (_x<450 && _y < _Y_Sanke)
			_vy = 0.5f;
		else
		if (_x < 450 && _y == _Y_Sanke)
			{
				_vy = 0;
				_vx = _snakeSPEED;
			}
			else
			if (_x >= 450 && _y == _Y_Sanke)
				{
					_vy = 0.5f;
					_vx = 0;
				}
			else
			if (_y > _Y_Sanke)
			{
				_vy = 0.5f;
				_vx = 0;
			}

		if (flag == true && flag1 == true)
		{
			flag = false;
			flag = false;
		}

		if (Simon::getCurrentSimon()->_x < this->last_x && flag1 == false)
		{
			_vx = -_vx;
			flag = true;
		}
		else
		if (flag == false)
			{
				_vx = _vx;
				flag1 = true;
			}

	this->_y += _vy*DeltaTime;
	this->_x += int(this->_vx * DeltaTime);

	_box = Box(_x, _y, _snakeWIDTH, _snakeHEIGHT);
}

void Snake::Draw()
{
	if (left == false)
		this->_sprite->DrawFlipX(_x, _y);
	else
		this->_sprite->Draw(_x, _y);
}
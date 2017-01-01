#include "Bone.h"
#include "Simon.h"



Bone::Bone(int x, int y) :
GObject(_boneTYPE, x, y, _boneWIDTH, _boneHEIGHT)

{
	last_x = x;
	_vx = _boneSPEED;
	_box = Box(x, y, _WIDTH, _HEIGHT);
	GTexture* texture1 = new GTexture(_boneSPRITE, 2, 1, 2);
	_sprite = new GSprite(texture1, 40);

	_top = 0;
	_tamp = 0;
}

void Bone::ChangeState(int state){
	//
}

void Bone::Update(float DeltaTime)
{
	int dx = abs(Simon::getCurrentSimon()->_x - _x) / 2;

	if (Simon::getCurrentSimon()->_x < _x && flag == false)
	{
		_mid = Simon::getCurrentSimon()->_x + dx;
		_top = Simon::getCurrentSimon()->_y + 30;
		flag = true;
		left = true;
	}
	if (Simon::getCurrentSimon()->_x > _x && flag == false)
	{
		_mid = _x + dx;
		_top = Simon::getCurrentSimon()->_y;
		flag = true;
		left = false;
	}
	if (left)
	{
		if (_x>_mid)
		{
			_vx = -0.2f;
			
			if (_y < _top - 20)
			{
				_vy = -0.4f;
			}
			else
				_vy = -0.8f;
		}
		else
		{
			_vx = -0.2f;
			if (_y > _top - 20)
			{
				_vy = 0.4f;
			}
			else
				_vy = 0.8f;
		}

	}
	if (!left)
	{
		if (_x > _mid)
		{
			_vx = 0.4f;

			if (_y > _top - 20)
			{
				_vy = 1.2f;

			}
			else
				_vy = 0.4f;
		}
		else
		{
			_vx = 0.4f;
			if (_y < _top + 20)
			{
				_vy = -0.4f;
			}
			else
			if (_y <= _top)
			{
				_vy = 0.4f;

			}
			else
				_vy = -1.2f;
		}

	}
	

	this->_x += this->_vx*DeltaTime;
	this->_y += this->_vy*DeltaTime;


	_box = Box(_x, _y, _boneWIDTH, _boneHEIGHT);
	_sprite->Update(DeltaTime);
}

void Bone::Draw()
{
	if (left)
	{
		_sprite->DrawFlipX(_x, _y);
	}
	else
		_sprite->Draw(_x, _y);
}
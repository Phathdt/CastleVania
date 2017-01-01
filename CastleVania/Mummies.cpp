#include "Mummies.h"

Mummies::Mummies(int x, int y, int x1, int x2) :
GObject(43, x, y, _mumWIDTH, _mumHEIGHT)
{
	_isMoveleft = false;
	_isMoveright = true;
	last_x = x;
	_isSleep = true;
	_box = Box(x, y, _mumWIDTH, _mumHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(_mumSPRITE, 6, 1, 6);
	_sprite = new GSprite(texture, 30);
	_tamp = 0;
	_hp = _mumHP;

	_timelive = 0;
	_vx = 0;
	_vy = 0;
	_timedame = 0;
	_dx = 0;
	_old_x = x;
	_vx = _mumSPEED;

	_firtdame = false;
	_firtblade = false;

	_comeback = false;
	_checkspirit = false;
	_timespirit = 50;

	_checkdame = false;

	_isFirst = false;
}

void Mummies::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__

	if (Simon::getCurrentSimon()->_x >= _mid_x)
	{
		_flag = true;
	}

	if (this->_isSleep){
		return;
	}

	if (!_comeback)
	{
		if (!_isFirst)
		{
			if (_x < _mid_x)
			{
				_vx = 0.4f;
			}
			else
			{
				_vx = -0.4f;
			}

			
		}
		else
		{
			int ySimon = Simon::getCurrentSimon()->_y;
			int xSimon = Simon::getCurrentSimon()->_x;

			if (xSimon <= _mid_x)
			{
				if (_count == 0)
				{
					_gox = xSimon + 100;
					_count++;
					_vx = -0.4f;

				}
				if (_count == 1)
				{
					_vx = -0.4f;

					if (_x <= _gox)
					{
						_count++;
						_vx = 0.4f;
						_dx = 0;
					}
				}
				if (_count == 2)
				{
					_vx = 0.4f;
					if (_x >= _mid_x + 100)
					{
						_count = 0;
						_dx = 0;
					}
				}
			}
			else
			{
				if (_count == 0)
				{
					_gox = xSimon - 50;
					_count++;
					_vx = 0.4f;

				}
				if (_count == 1)
				{
					_vx = 0.4f;

					if (_x >= _gox)
					{
						_count++;
						_vx = -0.4f;
						_dx = 0;
					}
				}
				if (_count == 2)
				{
					_vx = -0.4f;
					if (_x >= _mid_x - 100)
					{
						_count = 0;
						_dx = 0;
					}
				}
			}
		}
	}


	if (_x <= _start_x)
	{
		_vx = 0.5f;
		_comeback = true;

	}
	else
	if (_x >= _finish_x)
	{
		_vx = -0.5f;
		_comeback = true;

	}

#pragma region Xử lý delay

	

#pragma endregion

	if (_isDame)
	{
		_vx = 0;
	}

	this->_x += _vx*deltaTime;

	if (this->_x == _mid_x)
	{
		_isFirst = true;
		_comeback = false;
	}



	_dx += (abs(_old_x - _x));
	_old_x = _x;
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Mummies::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	if (this->_isSleep){
		this->_sprite->_start = 0;
		this->_sprite->_end = 0;
	}
	else
	if (this->_isDame)
	{
		this->_sprite->_start = 0;
		this->_sprite->_end = 5;
	}
	else
	{
		this->_sprite->_start = 0;
		this->_sprite->_end = 5;
	}

#pragma endregion
}

void Mummies::Update(float deltatime){
	
	if (this->_isDead){
		if (Simon::getCurrentSimon()->getCountMum() == 2)
		{
			if (!_checkspirit)
			{
				_nextBall = new NextBall(6910, 350);
				_checkspirit = true;
			}
			else
			{
				if (!_eatspirit)
				{
					_nextBall->Update(deltatime);
				}
				else
				{
					//xử lý qua màn
					return;
				}
			}
		}



		return;
	}

	if (_hp == 0) {
		this->_isDead = true;
		Simon::getCurrentSimon()->MumDeath();

		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}


	if (_flag == true && _timesleep >= 0)
		_timesleep -= deltatime;
	if (_timesleep < 0)
		ChangeState(2);
	if (_isLive)
	{
		if (!_checkdame)
		{
			_blade = new Blade(_x, _y);
			_checkdame = true;
			_isDame = true;
		}
		else
		{
			if (_checkdame)
			{
				_timedame += deltatime;
			}
			if (_timedame > 50)
				_isDame = false;
			if (_timedame > 400)
			{
				_blade = new Blade(_x, _y);
				_isDame = true;
				_timedame = 0;
				
			}
			else
				_blade->Update(deltatime);
		}
	}	
	this->MoveUpdate(deltatime);
	this->SetFrame(deltatime);
	this->_sprite->Update(deltatime);
}

void Mummies::ChangeState(int state){
	if (state == MUMMIESSTATE::is_SLEEPING){
		{
			this->_isSleep = true;
			this->_isLive = false;
			this->_isDame = false;
		}
	}
	else
	if (state == MUMMIESSTATE::is_LIVING){
		this->_isSleep = false;
		this->_isLive = true;
		this->_isDame = false;

	}
	else
	if (state == MUMMIESSTATE::is_DAMING)
	{
		_isDame = true;
		this->_isLive = false;
		this->_isSleep = false;

	}
}

void Mummies::Draw(){
	if (this->_isDead){
		if (_timeDeath <= DEATH_TIME)
		{
			this->DrawDeath();

			//Vẽ Spirit Ball
			if (_checkspirit)
			{
				_nextBall->Draw();
			}
		}
		return;
	}

	if (_timedame > 0)
	{
		_blade->Draw();
	}
	if (_vx > 0)
	{
		this->_sprite->DrawFlipX(_x, _y);
	}
	else
		this->_sprite->Draw(_x, _y);
}

void Mummies::Collistion(float deltaTime){
	float x, y;

	if (_isDead){
		if (!_eatspirit)
		{
			if (_checkspirit == true && swepyAABB->AABB(_nextBall->_box, Simon::getCurrentSimon()->_box, x, y)){
				swepyAABB->AABB(_nextBall->_box, Simon::getCurrentSimon()->_box, x, y);
				_eatspirit = true;
				Simon::getCurrentSimon()->nextLV();
				GCamera::getCurrentCamera()->getCurrentCamera()->ChangeState(1);
			}
		}
		return;
	}
	if (_isSleep == false)
	{
		if (Simon::getCurrentSimon()->isFighting()){
			if (swepyAABB->AABB(this->_box, Whip::getCurrentWhip()->_box, x, y) && !_isHurting){
				_isHurting = true;
				if (_hp > 0)
					_hp--;
				Simon::getCurrentSimon()->DameMum();
			}
		}
		else {
			_isHurting = false;
		}

		/*if (Simon::getCurrentSimon()->GetState() == STATE::CANT_HURT)
		return;*/

		if (Simon::getCurrentSimon()->cantHurt())
			return;

		if (swepyAABB->AABB(_blade->_box, Simon::getCurrentSimon()->_box, x, y)){
			swepyAABB->AABB(_blade->_box, Simon::getCurrentSimon()->_box, x, y);
			Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
			Simon::getCurrentSimon()->Hurt(DAMAGAE);
		}

		if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
			swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y);
			Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
			Simon::getCurrentSimon()->Hurt(DAMAGAE);
		}


	}
	else
		return;
}


Mummies::~Mummies(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

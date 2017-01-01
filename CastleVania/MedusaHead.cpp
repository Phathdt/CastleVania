#include "MedusaHead.h"


MedusaHead::MedusaHead(int x, int y, int x2, int y2) :
Enemy(TYPE, x, y, x2, y2)
{
	_vx = _medusaheadSPEED;
	_box = Box(x, y, _medusaheadWIDTH, _medusaheadHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(MEDUSAHEAD_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	this->SetFrame(0);
	_hp = HP;
	_damage = DAMAGE;
}
MedusaHead::MedusaHead(int x, int y, int x2, int y2,bool left) :
Enemy(TYPE, x, y, x2, y2,left)
{
	_vx = _medusaheadSPEED;
	_box = Box(_x, _y, _medusaheadWIDTH, _medusaheadHEIGHT, _vx, _vy);
	GTexture* texture = new GTexture(MEDUSAHEAD_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	this->SetFrame(0);
	_hp = HP;
	_damage = DAMAGE;
}
void MedusaHead::MoveUpdate(float deltaTime)
{
	if (_isHurting) return;
#pragma region __XU_LY_CHUYEN_DONG__
	

#pragma region Fix MedusaHead Move

	if (_isMoveleft){
		if (_x <= _activeArea.left){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
			_tamp = 0;
			//this->_y = _activeArea.top;
		}
	}
	else{
		if (_x >= _activeArea.right - 25){
			_vx *= -1;
			this->_isMoveleft = !this->_isMoveleft;
			_tamp = 0;

			//this->_y = _activeArea.top;
			//this->_y = ynek;
		}
	}

	this->_x += int(this->_vx * deltaTime);
	this->_tamp += (this->_vx * deltaTime / 30);	
	if (!(_y <= _activeArea.top || _y >= _activeArea.bottom))
		this->_y += int(3 * sin(float(_tamp)));
	this->_y += int(3 * sin(float(_tamp)));
#pragma endregion

#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void MedusaHead::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 1;
#pragma endregion
}

void MedusaHead::Update(float deltatime){
	if (_hp == 0) {
		this->_isDead = true;
		this->_timeDeath += deltatime;
		this->_spriteDeath->Update(deltatime);
	}

	if (this->_isDead){
		return;
	}
	this->MoveUpdate(deltatime);
	this->_sprite->Update(deltatime);
}

MedusaHead::~MedusaHead(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

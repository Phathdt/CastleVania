#include "Spearguard.h"


Spearguard::Spearguard(int x, int y, int x2, int y2) :
Enemy(TYPE, x, y, x2, y2)
{
	GTexture* tt = new GTexture(SPEARGAURD_SPRITE, 4, 1, 4,false);
	_sprite = new GSprite(tt, 30);
	this->_vx = _guardSPEED;
	this->SetFrame(0);
	_box = Box(x, y, _guardWIDTH, _guardHEIGHT, _vx, _vy);
	_hp = HP;
	_damage = DAMAGE;
	_activeArea.right = x2 - _guardWIDTH;
}

void Spearguard::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 3;
#pragma endregion
}

Spearguard::~Spearguard(){
	if (_sprite != NULL){
		delete _sprite;
	}
}


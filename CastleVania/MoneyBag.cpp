#include "MoneyBag.h"



MoneyBag::MoneyBag(int x, int y, int x2, int y2) :
Item(TYPE, x, y, x2, y2)
{
	GTexture* texture = new GTexture(_SPRITE, 3, 1, 3);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	this->_moneycolor = (int)(100*time(NULL)) % 3; 
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
}
void MoneyBag::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	switch (_moneycolor)
	{
	case MoneyColor::Red : 
		this->_sprite->_start = 0;
		this->_sprite->_end = 0;
		break;
	case MoneyColor::White:
		this->_sprite->_start = 1;
		this->_sprite->_end = 1;
		break;
	case MoneyColor::Blue:
		this->_sprite->_start = 2;
		this->_sprite->_end = 2;
		break;
	default:
		break;
	}
	
#pragma endregion
}

void MoneyBag::Update(float deltatime){
	this->SetFrame(deltatime);
	this->MoveUpdate(deltatime);
	this->_sprite->Update(deltatime);
}

MoneyBag::~MoneyBag(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

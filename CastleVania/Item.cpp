#include "Item.h"


Item::Item(int type, int x, int y, int x2, int y2) :
GObject(type, x, y, _WIDTH, _HEIGHT)
{
	_isOnGround = false;
	_lifeTime = -1;
	_vy = GRAVITY;
	_vx = 0;
	_activeArea.top = y;
	_activeArea.left = x;
	_activeArea.right = x2;
	_activeArea.bottom = y2;
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
	swepyAABB = new CSweptAABB();
}
void Item::MoveUpdate(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DONG__
	if (this->_lifeTime < 0){
		return;// neu chua xuat hien.
	}
	this->_lifeTime += deltaTime;
	if (this->_isOnGround){
		return;
	}
	if (this->_y + this->_height >= this->_activeArea.bottom){
		this->_isOnGround = true;
		return;
	}
	else{
		this->_y += this->_vy*deltaTime;
	}
#pragma endregion
	_box.x = _x;
	_box.y = _y;
	_box.vx = _vx;
	_box.vy = _vy;
}

void Item::SetFrame(float deltaTime)
{
#pragma region __XU_LY_CHUYEN_DOI_FRAME__
	this->_sprite->_start = 0;
	this->_sprite->_end = 0;
#pragma endregion
}

void Item::Update(float deltatime){
	this->MoveUpdate(deltatime);
	this->_sprite->Update(deltatime);
}

void Item::Draw(){
	if (this->_lifeTime < 0){
		return; //chua xuat hien.
	}
	if (this->_lifeTime >= _LIFETIME){
		return;
	}
	else{
		this->_sprite->Draw(_x, _y);
	}
}

void Item::ChangeState(int state){
	if (state == ItemState::_ItemHidding){
		this->_lifeTime = -1;
	}
	else{
		if (this->_lifeTime<=0)
			this->_lifeTime = 0;
	}
}

void Item::Collistion(float deltatime){
	float x, y;
	if (swepyAABB->AABB(Whip::getCurrentWhip()->_box, this->_box, x, y)
		|| swepyAABB->AABB(Boomerang::getCurrentBoomerang()->_box, this->_box, x, y)
		|| swepyAABB->AABB(WeaponKnife::getCurrentKnife()->_box, this->_box, x, y)
		){
		this->WakeUp();
	}
	if (this->_lifeTime > 0 && this->_lifeTime <= _LIFETIME){
		if (swepyAABB->AABB(Simon::getCurrentSimon()->_box, this->_box, x, y)){
			switch (_type)
			{
			case TypeGame::Item_small_heart:

				Simon::getCurrentSimon()->Heal(1); 
				SOUND(SOUND_EATITEM);
				break;
			case TypeGame::Item_axe:
			case TypeGame::Item_knife:
			case TypeGame::Item_cross:
			case TypeGame::Item_holy_water:
				SOUND(SOUND_EATWEAPON);
				break;
			default:
				SOUND(SOUND_EATITEM);
				break;
			}
			this->_lifeTime += (_LIFETIME + 1);
		}
	}
}

Item::~Item(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

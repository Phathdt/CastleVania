#include "Door.h"
Door::Door(int x, int y) :
GObject(9, x, y, _WIDTH, _HEIGHT)
{
	_box = Box(x, y, _WIDTH, _HEIGHT);
	GTexture* texture = new GTexture(_SPRITE, 2, 1, 2);
	_sprite = new GSprite(texture, _ANIMATE_RATE);
	swepyAABB = new CSweptAABB();
	_lifeTime = -1;
	_isShow = false;
	_sprite->_start = 0;
	_sprite->_start = 1;
}
void Door::Update(float deltatime){
	if (_isShow) _lifeTime += deltatime;
}
void Door::Draw(){
	if ((_lifeTime >= 0) && (_lifeTime <= _LIFETIME)){
		if (Simon::getCurrentSimon()->getCurrentLV()==2)
		this->_sprite->Draw(_x - 64, _y);
		else
		{
			this->_sprite->DrawFlipX(_x, _y);
		}
	
	}
		
}
void Door::Collistion(float deltatime){
	
	float x, y;
	if (Simon::getCurrentSimon()->GetState() == STATE::CANT_HURT)
		return;
	
	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		if (!_isShow){
			Simon::getCurrentSimon()->canGoLeft(false);
			this->_isShow = true;
			SOUND(SOUND_OPENDOOR);
			return;
		}
	
		GCamera::getCurrentCamera()->xDestinate = this->_x;
		GCamera::getCurrentCamera()->onGoto = true;
		Simon::getCurrentSimon()->canGoLeft(true);
		_lifeTime = 0;
	}
}
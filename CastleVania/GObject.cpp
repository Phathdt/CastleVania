#include "GObject.h"

GObject::GObject(int type, int x, int y, int width, int height)
{
	_type = type;
	_x = x;
	_y = y;
	_vx = 0;
	_vy = 0;
	_gravity = GRAVITY;

	_width = width;
	_height = height;
	_bound.left = _x;
	_bound.top = _y;
	_bound.right = _x + width;
	_bound.bottom = _y + height;
	_isDeath = false;
	_timeDeath = 0;

	GTexture* texture = new GTexture(_SPRITE_DEATH, 3, 1, 3);
	_spriteDeath = new GSprite(texture, 7);

	this->_spriteDeath->_start = 0;
	this->_spriteDeath->_end = 3;
}


void GObject::UpdatePosition(int time)
{
	_vy += _gravity * time;
	_x += int(_vx * time);
	_y += int(_vy * time);
}



GObject::~GObject()
{

}
GObject::GObject()
{

}
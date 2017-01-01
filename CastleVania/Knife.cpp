#include "Knife.h"



Knife::Knife(int x, int y, int x2, int y2) :
Item(TYPE, x, y, x2, y2)
{
	GTexture* texture = new GTexture(_SPRITE, 1, 1, 1);
	_sprite = new GSprite(texture, ANIMATIONRATE);
	this->SetFrame(0); 
	_box = Box(x, y, _WIDTH, _HEIGHT, _vx, _vy);
}
Knife::~Knife(){
	if (_sprite != NULL){
		delete _sprite;
	}
}

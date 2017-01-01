#include "Brick.h"
#include <d3dx9.h>
#include <stdio.h>

Brick::Brick(int X, int Y) :
GObject(11, X, Y, BRICK_WIDTH, BRICK_HEIGHT)
{
	
	_vx = 0; _vy = 0;
	_gravity = 0;
	GTexture* tamp = new GTexture(BRICK_SPRITE, 1, 1, 1);
	_sprite = new GSprite(tamp,0);
}

void Brick::Update(int DeltaTime)
{
	
}
void Brick::Render()
{
	
}
void Brick::Draw()
{
	_sprite->Draw(_x, _y);
}
Brick::Brick() :GObject()
{

}
Brick::~Brick()
{

}
#include "Trap.h"
#include "Simon.h"


Trap::Trap(int x, int y) :
GObject(trapTYPE, x, y, 64, 16)
{
	_Str_Y = y;
	_Offset = y + 36;
	var = 4;

	_box = Box(x, y, _trapWIDTH, _trapHEIGHT);
	GTexture* texture1 = new GTexture(_SPRITE, 2, 1, 2);
	GTexture* texture2 = new GTexture(_SPRITE1, 1, 1, 1);
	_sprite1 = new GSprite(texture1, 1);
	_sprite2 = new GSprite(texture2, 1);

}

void Trap::ChangeState(int state){
	//
}

void Trap::Update(float DeltaTime)
{
	check += var / 4;
	_y += var;
	if (_Offset - _y >= 128)
	{
		var = 1;
	}

	if (_Offset - _y <= 28)
	{
		var = -1;
	}
	_box = Box(_x, _y, _trapWIDTH, _trapHEIGHT);

}

void Trap::Collistion(float deltaTime){
	float x, y;
	if (Simon::getCurrentSimon()->cantHurt())
		return;
	if (swepyAABB->AABB(this->_box, Simon::getCurrentSimon()->_box, x, y)){
		Simon::getCurrentSimon()->ChangeState(STATE::CANT_HURT);
	}
}


void Trap::Draw()
{
	_sprite1->Draw(_x, _y);
	for (int i = 0; i < 18; i++)
	{
		if (_Offset - (_y - (28 + i * 8)) <= 164)
			_sprite2->Draw((float)_x, (float)_y - (28 + i * 8));

	}
}
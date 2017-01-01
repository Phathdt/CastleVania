#ifndef __Whip_H__
#define __Whip_H__

#include "Simon.h"
//cai nay cung vay
#define _WIDTH 61
#define _HEIGHT 49
#define _SPRITE_LEFT L"morningstar_left.png"
#define _SPRITE_RIGHT L"morningstar_right.png"
#define TYPE TypeGame::MxD
class Whip : public GObject {
private:
	bool _turnlef;
	static Whip* _whip;
	
public:

	GSprite* _sprite_right, *_sprite_left;
	Whip(int x, int y);
	static Whip* getCurrentWhip();
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Draw();
	Whip();
	~Whip();
};

#endif
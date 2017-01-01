#ifndef __Boomerang_H__
#define __Boomerang_H__

#include "Simon.h"
//cai nay cung vay
#define _WIDTH 32
#define _HEIGHT 32
#define _SPRITE L"weapon/4.png"
#define _Rage 256

#define TYPE TypeGame::Weapon_Boomerang
class Boomerang : public GObject {
private:
	bool _turnlef;
	bool _flying;
	int d = 0;
	bool _going = false;
	static Boomerang* _boomerang;
	bool done = true;

public:

	GSprite* _sprite;
	Boomerang(int x, int y);
	static Boomerang* getCurrentBoomerang();
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Draw();
	void Fly();
	bool isFlying(){ return _flying; }
	Boomerang();
	~Boomerang();
};

#endif

#ifndef __WeaponKnife_H__
#define __WeaponKnife_H__

#include "Simon.h"
//cai nay cung vay
#define _WIDTH 32
#define _HEIGHT 32
#define _SPRITE L"weapon/1.png"
#define _Rage 256

#define TYPE TypeGame::Weapon_Kife
class WeaponKnife : public GObject {
private:
	bool _turnlef;
	bool _flying;
	static WeaponKnife* _weaponknife;
	bool done = true;

public:

	GSprite* _sprite;
	WeaponKnife(int x, int y);
	static WeaponKnife* getCurrentKnife();
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Draw();
	void Fly();
	bool isFlying(){ return _flying; }
	WeaponKnife();
	~WeaponKnife();
};

#endif

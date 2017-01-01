#ifndef __OBJECT_H__
#define __OBJECT_H__



#include <d3d9.h>
#include <d3dx9.h>
#include "GSprite.h"
#include "Box.h"
#include "GAudio.h"
#define GRAVITY			1.5f
#define ANIMATIONRATE 30
#define _SPRITE_DEATH L"other/1.png"
#define DEATH_TIME 100
enum TypeGame {
	Boss_Bat = 0,
	Boss_Medusa = 1,
	Boss_Simon = 2,
	Enemy_Bat = 3,
	Enemy_Bonepilla = 4,
	Enemy_Ghost = 5,
	Enemy_Medusahead = 6,
	Enemy_Merman = 7,
	Enemy_Panther = 8,
	Enemy_Spearguard = 9,
	Enemy_Zombie = 10,
	Ground_Brick = 11,
	Ground_Fireandle = 12,
	Ground_Firetower = 13,
	Ground_Go_In_Castle = 14,
	Ground_Hidden = 15,
	Ground_Lockdoor = 16,
	Ground_Moving_Brick = 17,
	Ground_Next = 18,
	Ground_Opendoor = 19,
	Ground_Stair_Down = 20,
	Ground_Stair_Up = 21,
	Ground_Trap = 22,
	Item_axe = 23,
	Item_cross = 24,
	Item_knife = 25,
	Item_holy_water = 26,
	Item_stop_watch = 27,
	Item_morning_star = 28,
	Item_double_shot = 29,
	Item_small_heart = 30,
	Item_big_heart = 31,
	Item_money_bag = 32,
	Item_roast = 33,
	Item_rosary = 34,
	Item_spirit_ball = 35,
	Item_none = 36,

	Item_fire_ball = 40,//Đạn của Bone Pillar
	Medusa_snake = 41,//Rắn của Medusa

	Other_kill = 37,
	MxD = 38, //roi
	Death_Place=39,
	Enemy_Fleaman=40,
	Enemy_Raven=41,

	Enemy_Skeleton=42,
	Skeleton_Bone = 55,//Xương của Skeleton

	Boss_Mummies=43,
	Mummies_Blade = 56,//Dao của Mummies

	Weapon_Boomerang = 44,
	Weapon_Kife = 45,
	Weapon_Holy = 46
};

class GObject {
protected:

public:
	int _x;
	int _y;
	int _width;
	int _height;
	int _id;
	int _timeDeath;
	bool _isDeath;
	float _vx;
	float _vy;
	float _gravity;
	GSprite* _spriteDeath;
	int _type;

	RECT _bound;

	Box _box;



	GObject::GObject(int type, int x, int y, int width, int height);
	virtual void Update(float deltatime){}
	virtual void Draw(){}
	virtual void Collistion(float deltatime){}
	virtual void ChangeState(int state){}
	virtual void ExtendCollistion(GObject* brick){}
	void DrawDeath(){
		this->_spriteDeath->Draw(_x + _width / 2 - 16, _y + _height-44);
	}
	/*virtual void LoadResource();
	virtual void Update(int Delta);
	virtual void Render();
	virtual void Damaged(int damage, int x, int y);*/

	GObject();

	void UpdatePosition(int time);
	//void FixPositionCollid(G_OBJECT * o, int CollidPos);


	~GObject();
};

#endif
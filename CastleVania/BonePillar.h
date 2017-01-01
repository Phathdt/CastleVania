#ifndef __BONEPILLAR_H__
#define __BONEPILLAR_H__


#include "GObject.h"
#include "GSprite.h"
#include "FireBall.h"
#include "SweptAABB.h"
#include "Box.h"


#define _bplWIDTH	32
#define _bplHEIGHT	64
#define _ANIMATE_RATE	7
#define _ATTACK_RATE	10
#define _bplSPRITE L"enemy/8.png"
#define _SPRITE1 L"other/0.png"
#define bplHP 5
#define DAMAGE 2



class BonePillar : public GObject {
protected:
	bool _isMoveleft;
	int _isHurting = false;
	bool _flag1, _flag2, _flag3;
	bool _isDead;// da chet chua nek.
	float _time1 = 0;
	float _time2 = 0;
	float _time3 = 0;
	bool _isSleep = true;
	Box _awakeBox;
	CSweptAABB* swepyAABB;
	int _hp;

public:
	GSprite* _sprite;
	FireBall* _fireball1, *_fireball2, *_fireball3;
	BonePillar(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Draw();
	void Collistion(float deltaTime);

	BonePillar();
	~BonePillar();
};

#endif
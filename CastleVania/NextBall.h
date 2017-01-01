#ifndef __NEXTBALL_H__
#define __NEXTBALL_H__	

#include "GObject.h"
#include "GSprite.h"
#include "Simon.h"
#include "Simon.h"
#include "SweptAABB.h"
#define _WIDTH	28
#define _HEIGHT	32
#define _SPRITE L"item/13.png"
#define TYPE TypeGame::Item_spirit_ball

#define _SpiritBall_x1 250
#define _SpiritBall_y1 275

#define _SpiritBall_x2 250
#define _SpiritBall_y2 323

class NextBall : public GObject {
private:
	float _time;

public:
	GSprite* _sprite;
	CSweptAABB* swepyAABB;
	NextBall(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltatime);
	void Draw();
	NextBall();
	~NextBall();
};

#endif
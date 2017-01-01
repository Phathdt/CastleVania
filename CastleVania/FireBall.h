#ifndef __FIREBALL_H__
#define __FIREBALL_H__

//Đạn của Bone Pillar

#define _fbWIDTH	16
#define _fbHEIGHT	20
#define _fbSPRITE L"other/0.png"
#define fbTYPE TypeGame::Item_fire_ball
#define _fbSPEED 1.2f

#include "GObject.h"
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "SweptAABB.h"

class FireBall : public GObject {
protected:
	int _Str_Y;
	int _Offset;
	int check = 30;
	bool left, right;
	int last_x;

	int a[10];
	CSweptAABB* swepyAABB;


	int var;
	bool flag = false;
	bool flag1 = false;

public:
	GSprite* _sprite;
	FireBall(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void ChangeState(int state);
	void Draw();

	FireBall();
	~FireBall();
};

#endif

#ifndef __TRAP_H__
#define __TRAP_H__

//Bẫy

#define _trapWIDTH	64
#define _trapHEIGHT	28
#define _SPRITE1 L"ground/7_2.png"
#define _SPRITE L"ground/7_3.png"
#define trapTYPE TypeGame::Ground_Trap

#include "GObject.h"
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "SweptAABB.h"

class Trap : public GObject {
protected:
	int _Str_Y;
	int _Offset;
	int check = 30;

	int a[10];
	CSweptAABB* swepyAABB;


	int var;
	bool flag = false;
	RECT _activeArea; // ô chữ nhật mà con này chạy trong đó.
public:
	GSprite* _sprite1, *_sprite2;
	Trap(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void ChangeState(int state);
	void Draw();
	void Collistion(float deltaTime);

	Trap();
	~Trap();
};

#endif

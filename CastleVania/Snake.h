#ifndef __SNAKE_H__
#define __SNAKE_H__

//Rắn của Medusa

#define _snakeWIDTH	64
#define _snakeHEIGHT	20
#define _snakeSPRITE L"boss/2.png"
#define snakeTYPE TypeGame::Medusa_snake
#define _snakeSPEED 1.2f
#define _Y_Sanke 335


#include "GObject.h"
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

class Snake : public GObject {
protected:
	int _Str_Y;
	int _Offset;
	int check = 30;
	bool left, right;
	int last_x;
	int last_y;
	float _timelive;

	int a[10];


	int var;
	bool flag = false;
	bool flag1 = false;

public:
	GSprite* _sprite;
	Snake(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void ChangeState(int state);
	void Draw();

	Snake();
	~Snake();
};

#endif

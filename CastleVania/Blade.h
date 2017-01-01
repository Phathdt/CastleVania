#ifndef __BLADE_H__
#define __BLADE_H__

//Dao của Mummies

#define _bladeWIDTH	34
#define _bladeHEIGHT	20
#define _bladeSPRITE L"boss/3_1.png"
#define bladeTYPE TypeGame::Mummies_Blade
#define _bladeSPEED 1.2f



#include "GObject.h"
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

class Blade : public GObject {
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
	float _tamp;

public:
	GSprite* _sprite;
	Blade(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void ChangeState(int state);
	void Draw();

	Blade();
	~Blade();
};

#endif

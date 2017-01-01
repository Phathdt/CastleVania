#ifndef __MOVINGBRICK_H__
#define __MOVINGBRICK_H__


#include "Enemy.h"

#define _mvbWIDTH	64
#define _mvbHEIGHT	16
#define _mvbSPEED	0.6f
#define _SPRITE L"ground/9.png"
#define TYPE TypeGame::Enemy_Bat


class Brickmoving : public Enemy {

public:
	Brickmoving(int x, int y, int x2, int y2);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltatime);
	void Draw();
	Brickmoving();
	~Brickmoving();
};

#endif
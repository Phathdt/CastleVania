#ifndef __RA_H__
#define __RA_H__


#include "Enemy.h"
#include "Simon.h"
#include "Whip.h"
#include "Box.h"

#define _ravenWIDTH	32
#define _ravenHEIGHT	32
#define _ravenSPEED	1.0f
#define _ravenSPRITE L"enemy/Raven2.png"
#define ravenTYPE TypeGame::Enemy_Raven
#define HP 1
#define DAMAGE 3
#define Rx 156
#define Ry 24
#define Widthbox 177
#define Heightbox 1024

class Raven : public Enemy {
private:
	Box _awakeBox;
	bool _isSleep; // dang dung im tren tuong.
	bool _attackmode = true;
public:
	Raven(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltatime);
	Raven(){}
	~Raven();
};

#endif
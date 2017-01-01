#ifndef __FLEAMAN_H__
#define __FLEAMAN_H__


#include "Enemy.h"
#include "Simon.h"
#include "Whip.h"
#include "Box.h"

#define _fleamanWIDTH	37
#define _fleamanHEIGHT	37
#define _fleamanSPEED	0.4f
#define _SPRITE L"enemy/Fleaman.png"
#define TYPE TypeGame::Enemy_Fleaman
#define HP 1
#define TIME_WATING 200
#define DAMAGE 2

enum FLEAMAN_STATE{
	WAIT = 0,
	MOVE = 1
};
class Fleaman : public Enemy {
private:
	Box _awakeBox;
	bool _isSleep; // dang dung im tren tuong.
	int _xDestinate=0;
	int _yDestinate=0;
	int _countdown=0;
	int _currentState=FLEAMAN_STATE::WAIT;
	bool _firstActive=false;
public:
	Fleaman(int x, int y, int x2, int y2);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltatime);
	void ExtendCollistion(GObject* brick);
	void ChangeState(int state);
	Fleaman();
	~Fleaman();
};

#endif
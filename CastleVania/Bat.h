#ifndef __BAT_H__
#define __BAT_H__


#include "Enemy.h"
#include "Simon.h"
#include "Whip.h"
#include "Box.h"

#define _batWIDTH	32
#define _batHEIGHT	32
#define _batSPEED	0.4f
#define _SPEEDY 0.3f
#define BAT_SPRITE L"enemy/0.png"
#define TYPE TypeGame::Enemy_Bat
#define HP 1
#define DAMAGE 2

enum BATSATE{
	IsSleep = 0,
	IsAwake = 1
};
class Bat : public Enemy {
private:
	Box _awakeBox;
	bool _isSleep; // dang dung im tren tuong.
	float _tamp;
public:
	Bat(int x, int y, int x2, int y2);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltatime);
    void ChangeState(int state);
	Bat();
	~Bat();
};

#endif
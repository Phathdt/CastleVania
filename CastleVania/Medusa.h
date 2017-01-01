#ifndef __MEDUSA_H__
#define __MEDUSA_H__


#include "GObject.h"
#include "GSprite.h"
#include "Simon.h"
#include "SweptAABB.h"
#include "Snake.h"
#include "NextBall.h"

#define _medusaWIDTH	64
#define _medusaHEIGHT	65
#define _ANIMATE_RATE	7
#define _ATTACK_RATE	10
#define _medusaSPEED	0.5f

#define _medusaSPRITE L"boss/1.png"
#define _medusaHP 16
#define _timeDelay 50;
#define DAMAGAE 2
enum MEDUSASTATE
{
	IS_SLEEPING = 1, // Ngủ
	IS_LIVING = 2, // Sống lại

};


class Medusa : public GObject {
protected:
	bool _isSleep;//Medusa ngủ
	bool _isLive;//Medusa sống
	bool _isSnake;//Medusa thả rắn
	CSweptAABB* swepyAABB;


	float _timesleep = 200;
	int last_x;
	bool flag = false;
	bool check = false;
	bool _isHurting = false;
	bool _isMoveleft, _isMoveright;
	bool _point_left, _point_right;
	bool _flag1, _flag2, _flag3;
	bool _isDead;// da chet chua nek.
	float _time = 0;
	float _tamp;
	int _hp;
	bool _snake, snake1, snake2, snake3;
	float _time1, _time2, _time3;
	bool _comeback;

	float _timespirit;
	bool _checkspirit;//kiểm tra trái bóng Spirit đã tạo chưa
	bool _eatspirit;//kiểm tra Simon đã ăn trái bóng Spirit chưa

	float _timesnake;//thời gian thả rắn
	float _timelive;//thời gian rắn sống

	float _timedelay;//thời gian medusa delay
	bool _checkdelay;//Medusa đến simon lần 2 thì bị delay
	float _dx;//đoạn đường Medusa đi đc
	int _old_x;//vị trí cũ của Medusa
	bool _playing = false;
	bool _playingwin = false;
public:
	Snake *_snake1, *_snake2, *_snake3;
	GSprite* _sprite;
	NextBall *_nextBall;

	Medusa(int x, int y);
	void MoveUpdate(float deltatime);
	void ChangeState(int state);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltaTime);
	void UpdateBoard(){
		Simon::getCurrentSimon()->setBossHP(_hp);
	}
	void Draw();
	Medusa();
	~Medusa();
};

#endif
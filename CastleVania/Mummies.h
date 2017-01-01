#ifndef __MUMMIES_H__
#define __MUMMIES_H__


#include "GObject.h"
#include "GSprite.h"
#include "Simon.h"
#include "SweptAABB.h"
#include "NextBall.h"
#include "Blade.h"

#define _mumWIDTH	33
#define _mumHEIGHT	80
#define _ANIMATE_RATE	7
#define _ATTACK_RATE	10
#define _mumSPEED	0.4f

#define _mumSPRITE L"boss/3.png"
#define _mumHP 8
#define _timeDame 150;
#define DAMAGAE 1

#define _start_x 6685
#define _finish_x 7115
#define _mid_x 6915

enum MUMMIESSTATE
{
	is_SLEEPING = 1, // Ngủ
	is_LIVING = 2, // Sống lại
	is_DAMING = 3//đánh

};


class Mummies : public GObject {
protected:
	bool _isSleep;//Mummies ngủ
	bool _isLive;//Mummies sống
	bool _isDame;//Mummies đánh
	bool _isSnake;//Mummies bắn dao
	CSweptAABB* swepyAABB;

	Blade *_blade;

	float _timesleep = 200;
	int last_x;
	bool _flag;//biến đánh dấu sự thức tỉnh của Mummies
	int _count = 0;
	int _no = 0;
	int _gox;
	int _deah = 0;

	int _Start_x, _Finish_x;

	bool _isHurting = false;
	bool _isMoveleft, _isMoveright;

	bool _isDead;// da chet chua nek.
	float _time = 0;
	float _tamp;
	int _hp;
	bool _isFirst;//lần thức tỉnh đầu tiên

	bool _comeback;

	bool _firtdame;//lần đánh đầu tiên
	bool _firtblade;

	float _timespirit;
	bool _checkspirit;//kiểm tra trái bóng Spirit đã tạo chưa
	bool _eatspirit;//kiểm tra Simon đã ăn trái bóng Spirit chưa

	float _timeblade;//thời gian bắn dao
	float _timelive;//thời gian dao tồn tại

	float _timedame;//thời gian đánh delay
	bool _checkdame;//Medusa đến simon lần 2 thì bị delay
	float _dx;//đoạn đường Mummies đi đc
	int _old_x;//vị trí cũ của Mummies
public:

	GSprite* _sprite;
	NextBall *_nextBall;

	Mummies(int x, int y, int x1, int x2);
	void MoveUpdate(float deltatime);
	void ChangeState(int state);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltaTime);
	void UpdateBoard(){
		Simon::getCurrentSimon()->setBossHP(_hp);
	}
	void Draw();
	Mummies();
	~Mummies();
};

#endif
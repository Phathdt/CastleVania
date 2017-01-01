#ifndef __SKELETON_H__
#define __SKELETON_H__


#include "Enemy.h"
#include "Simon.h"
#include "Whip.h"
#include "Box.h"
#include "Bone.h"

#define _skeletonWIDTH	34
#define _skeletonHEIGHT	64
#define _skeletonSPEED	0.4f
#define _skeletonSPRITE L"enemy/7_3.png"
#define _skeletonTYPE TypeGame::Enemy_Skeleton
#define _skeletonHP 1
#define _skeletonTIME_WATING 10
#define _skeletonDAMAGE 3


enum SKELETON_STATE{
	_WAIT = 0,
	_JUMP = 1,
	_MOVE = 2,
	_DAMAGE = 3
};
class Skeleton : public Enemy {
private:
	Box _awakeBox;
	bool _isSleep; // dang dung im tren tuong.
	int _xDestinate = 0;
	int _yDestinate = 0;
	int _countdown = 0;
	bool _isMoveleft;
	int _currentState = SKELETON_STATE::_WAIT;
	bool _firstActive = false;

	bool _isThrow = false;
	bool _checkbone = false;
	bool _firstbone = false;
	bool _firstdame = false;
	float _timeExists = 0;
	int _dDame = 180;
	float _timeMove;
	int count = 3;
public:
	Bone* _bone;
	Skeleton(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void Collistion(float deltatime);
	void ExtendCollistion(GObject* brick);
	void ChangeState(int state);
	void Draw();
	Skeleton();
	~Skeleton();
};

#endif
#ifndef __GHOST_H__
#define __GHOST_H__

#include "Enemy.h"
#include "Box.h"
#define _ghostWIDTH	28
#define _ghostHEIGHT	28
#define _ghostSPEED	0.4f
#define GHOST_SPRITE L"enemy/9.png"
#define TYPE TypeGame::Enemy_Ghost
#define HP 2
#define DAMAGE 2

class Ghost : public Enemy {
private:
	bool _isSleep =true;
	bool _isMoveRight = true;
	Box _awakeBox;
public:
	Ghost(int x, int y,int x2, int y2);
	Ghost(int x, int y, int x2, int y2, bool left);
	void Collistion(float deltatime);
	void Update(float deltaTime);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	//void Update(float deltatime);
	void Draw();
	Ghost();
	~Ghost();
};

#endif
#ifndef __DOOR_H__
#define __DOOR_H__

#include "GObject.h"
#include "GSprite.h"
#include "SweptAABB.h"
#include "Simon.h"
#include "GCamera.h"


#define _WIDTH	44
#define _HEIGHT	96
#define _ANIMATE_RATE	30
#define _LIFETIME 300
#define _SPRITE L"ground/Gate.png"

class Door : public GObject {
protected:

	int _lifeTime; 
	bool _isShow;
	CSweptAABB* swepyAABB;

public:
	GSprite* _sprite;
	Door( int x, int y);
	void Update(float deltatime);
	void Collistion(float deltatime);
	void Draw();
	Door();
	~Door();
};

#endif
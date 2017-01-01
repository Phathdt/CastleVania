#ifndef __GROUND_H__
#define __GROUND_H__

#include "GObject.h"
#include "GSprite.h"
#include "GAudio.h"



#define _WIDTH	16
#define _HEIGHT	32
#define _ANIMATE_RATE	7
#define _ATTACK_RATE	10
#define _LIFETIME 3000

class Ground : public GObject {
protected:

	float _lifeTime; // lifetime <0 là đang ẩn sau gạch hay sau j đó. lifetime >= _LIFETIME thì là biết mất.
	bool _isOnGround;
	bool _isLife;


public:
	GSprite* _sprite;
	Ground(int type, int x, int y);

	void SetFrame(float deltattime);
	void Update(float deltatime);
	void ChangeState(int state);
	void Draw();
	Ground();
	~Ground();
};

#endif
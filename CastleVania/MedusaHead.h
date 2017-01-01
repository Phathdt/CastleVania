#ifndef __MEDUSAHEAD_H__
#define __MEDUSAHEAD_H__


#include "Enemy.h"

#define _medusaheadWIDTH	32
#define _medusaheadHEIGHT	32
#define _medusaheadSPEED	0.6f
#define MEDUSAHEAD_SPRITE L"enemy/6.png"
#define TYPE TypeGame::Enemy_Medusahead
#define HP 1
#define DAMAGE 2

class MedusaHead : public Enemy {
private:
	float _tamp;
	
public:
	MedusaHead(int x, int y, int x2, int y2);
	MedusaHead(int x, int y, int x2, int y2,bool left);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	MedusaHead();
	~MedusaHead();
};

#endif
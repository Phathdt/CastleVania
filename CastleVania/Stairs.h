#ifndef _STAIRS_H_
#define _STAIRS_H_
#include "Stair.h"
#include "GObject.h"
#include <vector>
#include "SweptAABB.h"
#include "KeyBoard.h"
#include "Simon.h"
using namespace std;
class Stairs:public GObject{
	
private:
	vector<Stair*> _listStair;
	CSweptAABB* swepyAABB;
public:
	Stairs();
	Stairs(int x, int y, int w, int h);
	void Collistion(float deltatime);
	Stair* getLast(){
		return _listStair.back();
	}
	~Stairs();
};
#endif
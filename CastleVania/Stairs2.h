#ifndef _STAIRS2_H_
#define _STAIRS2_H_
#include "Stair2.h"
#include "GObject.h"
#include <vector>
#include "SweptAABB.h"
#include "KeyBoard.h"
#include "Simon.h"
using namespace std;
class Stairs2 :public GObject{

private:
	vector<Stair2*> _listStair;
	CSweptAABB* swepyAABB;
public:
	Stairs2();
	Stairs2(int x, int y, int w, int h);
	void Collistion(float deltatime);
	Stair2* getLast(){
		return _listStair[0];
	}
	~Stairs2();
};
#endif
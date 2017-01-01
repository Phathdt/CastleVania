#ifndef __BRICKS_H__
#define __BRICKS_H__
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <vector>
#include "GObject.h"
#include "GSprite.h"
#include "Brick.h"
#include "Simon.h"
#include "SweptAABB.h"
using namespace std;
class Bricks :public GObject{
private:
	vector<Brick*> _listBrick;

	CSweptAABB* swepyAABB;
public:
	Bricks();
	Bricks(int x, int y, int w, int h); 
	void Collistion(float deltatime);
	void Draw();
	~Bricks();
};
#endif
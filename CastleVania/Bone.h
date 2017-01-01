#ifndef __BONE_H__
#define __BONE_H__

//Xương của Skeleton

#define _boneWIDTH	32
#define _boneHEIGHT	32
#define _boneSPRITE L"enemy/7_32.png"
#define _boneTYPE TypeGame::Skeleton_Bone
#define _boneSPEED 1.2f

#include "GObject.h"
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "SweptAABB.h"

class Bone : public GObject {
protected:

	bool left, right;
	int last_x;

	CSweptAABB* swepyAABB;

	int _top;
	int _mid;

	float _tamp;
	int var;
	bool flag = false;
	bool flag1 = false;

public:
	GSprite* _sprite;
	Bone(int x, int y);
	void MoveUpdate(float deltatime);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	void ChangeState(int state);
	void Draw();

	Bone();
	~Bone();
};

#endif

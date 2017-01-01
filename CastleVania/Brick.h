#ifndef __BRICK_H__
#define __BRICK_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "GObject.h"
#include "GSprite.h"

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32
#define BRICK_SPRITE L"ground/2-3.png"

class Brick : public GObject {
public:
	Brick( int X, int Y);
	virtual void Update(int DeltaTime);
	virtual void Render();
	void Draw();
	GSprite* _sprite;
	Brick();
	~Brick();
};

#endif

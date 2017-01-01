#pragma once
#include "Graphics.h"
class Surface
{
	LPDIRECT3DSURFACE9 _surFace;
public:
	void colorFill(D3DCOLOR color);
	void draw(int x, int y, int w, int);
	void drawBackground();
	Surface(LPCWSTR filepath);
	Surface();
	~Surface();
};
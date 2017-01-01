#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <d3d9.h>
#include <d3dx9.h>
#include"GameConfig.h"
#include"Graphics.h"

class GTexture
{
public:
	LPCWSTR FileName; //đường dẫn tới file ảnh
	RECT Size;		//độ phân giải ảnh
	LPDIRECT3DTEXTURE9 Texture;
	int Cols;		//số cột frame
	int Rows;		//số hàng frame
	int Count;		//tổng số frame
	int FrameWidth;		//width of 1 frame
	int FrameHeight;	//height of 1 frame
	bool green;
	GTexture(const GTexture &ctexture);
	GTexture(LPCWSTR _fileName, int cols = 1, int rows = 1, int count = 1);

	GTexture(LPCWSTR _fileName, int cols, int rows, int count, bool green);
	~GTexture();
	//vẽ texture tại vị trí (x, y) trên màn hình
	void Draw(int x, int y);

protected:
	void Load();
};

#endif
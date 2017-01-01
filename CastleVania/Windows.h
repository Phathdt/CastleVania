#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "GameConfig.h"
class Windows
{
	static Windows* _windows;
public:

	HINSTANCE _hInstance;
	HWND _hWindows;

	int _width;
	int _height;

	static Windows* getCurrentWindows();
	bool initWindows();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	Windows();
	~Windows();
};


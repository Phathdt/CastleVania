#pragma once
#define GAME_NAME L"CastleVania"
#define SCREEN_WIDTH 515
#define SCREEN_HEIGHT 440
#define FRAME_RATE 30

#define CAMERAX 0
#define CAMERAY 0
#define CAMERAWIDTH 266
#define CAMERAHEIGHT 192
#define GAME_SPEED 2


#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#include"Windows.h"


#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class GameConfig{
public:
	GameConfig();
	//write string to a tracing file
	static void GLTrace(char* format, ...);

	//show a message box
	static void GLMessage(LPCWSTR text);

	//show string to the caption of window
	static void GLTitle(LPCWSTR text);
	~GameConfig();
};

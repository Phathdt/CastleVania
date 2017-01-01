#include "Game.h"
#include "State.h"
#include "Brick.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstace,
	LPSTR lpStrCmdLine,
	int nShowCmd)
{
	
	Game* myGame = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
	myGame->GameInit();
	myGame->GameLoad();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	DWORD frame_start = GetTickCount();
	DWORD count_per_frame = 100 / FRAME_RATE;

	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD now = GetTickCount();
			float deltaTime = now - frame_start;
			

			myGame->_ProcessKeyBoard();
			if (deltaTime >= count_per_frame)
			{
				//frameStart = now;
				frame_start = now;
				//float delta_time = (float)deltaTime / 1000;
				if (deltaTime > count_per_frame)
					deltaTime = count_per_frame;

				KeyBoard::getCurrentKeyBoard()->PollKeyboard();
				myGame->GameRun(deltaTime);
				Graphics::getCurGraphics()->BeginGraphics();
				myGame->GameDraw();
				Graphics::getCurGraphics()->EndGraphics();
				Sleep(GAME_SPEED);
			}
		}
	}


	return 0;
}
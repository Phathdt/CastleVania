
#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"
#include "SoundPath.h"
#define Audio GAudio::GetCurrent()
#define THEME(X) GAudio::GetCurrent()->PlayTheme(X)
#define SOUND(X) GAudio::GetCurrent()->Play(Audio->LoadSound(X))

class GAudio
{
	static GAudio *_instance;
public:
	GSoundManager *dsound;
	GSound * _theme;

	int Init_DirectSound(HWND);
	GSound *LoadSound(char *);
	void Play(GSound *);
	void PlayTheme(char* name);
	void Loop(GSound *);
	void Stop(GSound *);
	static GAudio * GetCurrent();

};
#endif


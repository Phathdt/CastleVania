
#include "GAudio.h"

#include <cstdlib>
#pragma warning(disable : 4996)

GAudio * GAudio::_instance = 0;
int GAudio::Init_DirectSound(HWND hwnd)
{
    HRESULT result;

    //create DirectSound manager object
    dsound = new GSoundManager();

    //initialize DirectSound
    result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
    if (result != DS_OK)
    {
		return 0;
	}

    //set the primary buffer format
    result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
    if (result != DS_OK)
    {
		 return 0;
	}
    //return success
    return 1;
}

GSound* GAudio::LoadSound(char *filename)
{
    HRESULT result;

    //create local reference to wave data
    GSound *wave;

    //attempt to load the wave file

	//this shit make me so piss off
	wchar_t wtext[100];
	std::mbstowcs(wtext, filename, strlen(filename) + 1);//Plus null
	LPWSTR ptr = wtext;
	//

	result = dsound->Create(&wave, ptr);
	//result = dsound->Create(&wave, L"1.wav");
    if (result != DS_OK)
    {
		 return NULL;
	}
    //return the wave
    return wave;
}

void GAudio::Play(GSound *sound)
{
    sound->Play();
}

void GAudio::Loop(GSound *sound)
{
    sound->Play(0, DSBPLAY_LOOPING);
}

void GAudio::Stop(GSound *sound)
{
    sound->Stop();
}

GAudio* GAudio::GetCurrent(){
	if (!_instance)
		_instance = new GAudio();
	return _instance;
}

void GAudio::PlayTheme(char* name)
{
	if (_theme == nullptr)
		_theme = this->LoadSound(name);
	if (_theme->IsSoundPlaying()){
		_theme->Stop();
	}
	_theme = this->LoadSound(name);
	this->Loop(_theme);

}

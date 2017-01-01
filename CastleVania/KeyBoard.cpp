#include "KeyBoard.h"


KeyBoard* KeyBoard::_keyboard = 0;

KeyBoard* KeyBoard::getCurrentKeyBoard(){
	if (_keyboard == 0)
		_keyboard = new KeyBoard();
	return _keyboard;
}

int KeyBoard::InputKeyBoard(){

	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL)
		, DIRECTINPUT_VERSION
		, IID_IDirectInput8
		, (void**)&_input
		, NULL);
	_input->CreateDevice(GUID_SysKeyboard, &_inputDevice, NULL);

	HRESULT hr1 = _inputDevice->SetDataFormat(&c_dfDIKeyboard);
	HRESULT hr2 = _inputDevice->SetCooperativeLevel(Windows::getCurrentWindows()->_hWindows, DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024;

	_inputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	_inputDevice->Acquire();

	for (int i = 0; i < 256; i++)
	{
		_keyStates[i] = 0x00;
	}

	if (FAILED(hr1))
	{
		MessageBox(0, L"Không tạo định dạng được dữ liệu", L"Lỗi", MB_ICONERROR);
		return 0;
	}

	return 1;
}



void KeyBoard::UpdateKeyboard()
{
	BYTE keys[256];
	_inputDevice->GetDeviceState(256, keys);
	for (int i = 0; i < 256; i++)
	{
		_keyStates[i] = keys[i];
		if ((_keyStates[i] & 0x80) > 0){
			_keyDown = i;
		}
		else{
			_keyUp = i;
		}
	}
}

void KeyBoard::PollKeyboard()
{
	
	_inputDevice->Poll();
	if (FAILED(_inputDevice->GetDeviceState(sizeof(_keyStates), (LPVOID)&_keyStates)))
	{
		_inputDevice->Acquire();
		_inputDevice->GetDeviceState(sizeof(_keyStates), (LPVOID)&_keyStates);
	}
	else
	{
		_inputDevice->GetDeviceState(sizeof(_keyStates), (LPVOID)&_keyStates);
	}

}



bool KeyBoard::IsKeyDown(BYTE keyCode)
{
	return (_keyStates[keyCode] & 0x80) > 0;
}

bool KeyBoard::IsKeyUp(BYTE keyCode)
{
	return !((_keyStates[keyCode] & 0x80) > 0);
}

bool KeyBoard::keyLeft()
{
	return IsKeyDown(DIK_LEFT);
}

bool KeyBoard::keyRight()
{
	return IsKeyDown(DIK_RIGHT);
}

bool KeyBoard::keyUp()
{
	return IsKeyDown(DIK_UP);
}

bool KeyBoard::keyDown()
{
	return IsKeyDown(DIK_DOWN);
}

bool KeyBoard::keySpace()
{
	return IsKeyDown(DIK_SPACE);
}

bool KeyBoard::keyS()
{
	return IsKeyDown(DIK_S);
}

bool KeyBoard::keyW()
{
	return IsKeyDown(DIK_W);
}

bool KeyBoard::keyX()
{
	return IsKeyDown(DIK_X);
}

bool KeyBoard::keyC()
{
	return IsKeyDown(DIK_C);
}

KeyBoard::KeyBoard(void)
{
}


KeyBoard::~KeyBoard(void)
{
}

#include "Graphics.h"


Graphics* Graphics::_graphics = 0;
Graphics::Graphics()
{

}


Graphics::~Graphics()
{
	if (_Direct3D != NULL)
		_Direct3D->Release();
	if (_Direct3DDevice != NULL)
		_Direct3DDevice->Release();
	if (_backBuffer != NULL)
		_backBuffer->Release();
	if (_sprite != NULL)
		_sprite->Release();
}

Graphics * Graphics::getCurGraphics()
{
	if (_graphics == 0)
		_graphics = new Graphics();
	return _graphics;
}

bool Graphics::initDirectX3D()
{
	this->_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (_Direct3D) {
		return true;
	}
	return false;
}

bool Graphics::initDirect3DDevice()
{
	HRESULT result;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	d3dpp.Windowed = 1; // 1 la cua so , 0 la full man hinh
	d3dpp.hDeviceWindow = Windows::getCurrentWindows()->_hWindows;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_Direct3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		Windows::getCurrentWindows()->_hWindows,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&_Direct3DDevice);
	if (FAILED(_Direct3DDevice))
		return false;

	D3DXCreateSprite(_Direct3DDevice, &_sprite);


	HRESULT hr = _Direct3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
		&_backBuffer);

	return true;
}

void Graphics::BeginGraphics()
{
	_Direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(185, 61, 255), 1.0f, 0);
	_Direct3DDevice->BeginScene();
	_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Graphics::EndGraphics()
{
	_sprite->End();
	_Direct3DDevice->EndScene();
	_Direct3DDevice->Present(0, 0, 0, 0);

	if (KEY_DOWN(VK_ESCAPE))
		PostMessage(Windows::getCurrentWindows()->_hWindows, WM_DESTROY, 0, 0);
}

void Graphics::PrintText(const char * str, int size, int x, int y, DWORD color)
{
	ID3DXFont* dxfont;
	RECT textbox;
	SetRect(&textbox, x, y, SCREEN_WIDTH, SCREEN_HEIGHT);
	D3DXCreateFont(_Direct3DDevice,
		size,
		0,
		FW_NORMAL,
		1,
		false,    // italic font
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Arial",   // font su dung
		&dxfont);
	dxfont->DrawTextA(NULL,
		str,
		strlen(str),
		&textbox,
		DT_LEFT | DT_TOP,
		color);

	dxfont->Release();
}



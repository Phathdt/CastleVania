#include "Surface.h"


void Surface::colorFill(D3DCOLOR color)
{
	Graphics::getCurGraphics()->_Direct3DDevice->ColorFill(_surFace, NULL, color);
}

void Surface::draw(int x, int y, int w, int h)
{
	RECT r;
	r.left = x;
	r.top = y;
	r.right = r.left + w;
	r.bottom = r.top + h;
	Graphics::getCurGraphics()->_Direct3DDevice->StretchRect(_surFace,
		0,
		Graphics::getCurGraphics()->_backBuffer,
		&r,
		D3DTEXF_NONE);
}

void Surface::drawBackground()
{
	Graphics::getCurGraphics()->_Direct3DDevice->StretchRect(_surFace,
		0,
		Graphics::getCurGraphics()->_backBuffer,
		0,
		D3DTEXF_NONE);
}

Surface::Surface(LPCWSTR filepath)
{
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(filepath, &info);

	int result =
		Graphics::getCurGraphics()->_Direct3DDevice->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&_surFace,
		NULL);
	result = D3DXLoadSurfaceFromFile(
		_surFace,
		NULL,
		NULL,
		filepath,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),
		NULL);
}

Surface::Surface()
{
	int result =
		Graphics::getCurGraphics()->_Direct3DDevice->CreateOffscreenPlainSurface(
		300,
		300,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&_surFace,
		NULL);
}

Surface::~Surface()
{
	if (_surFace)
	{
		_surFace->Release();
		_surFace = 0;
	}
}

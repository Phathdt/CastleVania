#include "GSprite.h"

GSprite::GSprite()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
}

GSprite::GSprite(const GSprite &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
}

GSprite::GSprite(GTexture* texture, int start, int end, int timeAnimation)
: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
}

GSprite::GSprite(GTexture* texture, int timeAnimation)
: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
}

GSprite::~GSprite()
{
	if (_texture != NULL)
		delete _texture;
}

void GSprite::Next()
{
	_index++;
	if (_index > _end)
		_index = _start;
}

void GSprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void GSprite::SelectIndex(int index)
{
	_index = index;
}

void GSprite::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		this->Next();
		Done =  (Done + 1) % 3;
	}
}

void GSprite::Draw(int X, int Y)
{
	RECT srect;
	if (_index < _start) _index = _start;
	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;
	//D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	//position.x = X - _texture->FrameWidth / 2;
	position.x = X;
	position.y = Y+90;
	//D3DXMATRIX mat;
	//D3DXVECTOR2 centers((float)(X + _texture->FrameWidth / 2), (float)(Y + _texture->FrameHeight / 2));
	//D3DXVECTOR2 scale = D3DXVECTOR2(2.0f, 2.0f);
	//D3DXMatrixTransformation2D(&mat, &centers, 0.0f, &scale, NULL, 0.0f, NULL);
	//Graphics::getCurGraphics()->_sprite->SetTransform(&mat);
	//position.y = Y - _texture->FrameHeight / 2;
	Graphics::getCurGraphics()->_sprite->Draw(
		_texture->Texture,
		&srect,
		//&center,
		0,
		&position,
		0xFFFFFFFF //color
		);
}
void GSprite::Draw(int X, int Y,float scalex)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;
	//D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	//position.x = X - _texture->FrameWidth / 2;
	position.x = X;
	position.y = Y;
	D3DXMATRIX mat;
	D3DXVECTOR2 centers((float)(X + _texture->FrameWidth / 2), (float)(Y + _texture->FrameHeight / 2));
	D3DXVECTOR2 scale = D3DXVECTOR2(scalex, scalex);
	D3DXMatrixTransformation2D(&mat, &centers, 0.0f, &scale, NULL, 0.0f, NULL);
	Graphics::getCurGraphics()->_sprite->SetTransform(&mat);
	position.y = Y - _texture->FrameHeight / 2;
	Graphics::getCurGraphics()->_sprite->Draw(
		_texture->Texture,
		&srect,
		//&center,
		0,
		&position,
		0xFFFFFFFF //color
		);
}

void GSprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	Graphics::getCurGraphics()->_sprite->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Graphics::getCurGraphics()->_sprite->SetTransform(&finalMt);

	//x += _texture->FrameWidth;
	this->Draw(x, y );

	Graphics::getCurGraphics()->_sprite->SetTransform(&oldMt);
}
void GSprite::DrawFlipX(int x, int y,float scalex)
{
	D3DXMATRIX oldMt;
	Graphics::getCurGraphics()->_sprite->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Graphics::getCurGraphics()->_sprite->SetTransform(&finalMt);

	//x += _texture->FrameWidth;
	this->Draw(x, y,scalex);

	Graphics::getCurGraphics()->_sprite->SetTransform(&oldMt);
}

void GSprite::DrawFlipY(int x, int y)
{
	D3DXMATRIX oldMt;
	Graphics::getCurGraphics()->_sprite->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Graphics::getCurGraphics()->_sprite->SetTransform(&finalMt);

	this->Draw(x, y);

	Graphics::getCurGraphics()->_sprite->SetTransform(&oldMt);
}
void GSprite::DrawFlipY(int x, int y,float scalex)
{
	D3DXMATRIX oldMt;
	Graphics::getCurGraphics()->_sprite->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	Graphics::getCurGraphics()->_sprite->SetTransform(&finalMt);

	this->Draw(x, y,scalex);

	Graphics::getCurGraphics()->_sprite->SetTransform(&oldMt);
}

void GSprite::DrawRect(int X, int Y, RECT SrcRect)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	Graphics::getCurGraphics()->_sprite->Draw(
		_texture->Texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}

void GSprite::DrawIndex(int index, int X, int Y)
{
	RECT srect;

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	Graphics::getCurGraphics()->_sprite->Draw(
		_texture->Texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
		);
}

int GSprite::GetIndex()
{
	return _index;
}
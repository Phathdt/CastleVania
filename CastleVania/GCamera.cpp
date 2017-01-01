#include "GCamera.h"

GCamera* GCamera::_camera = 0;


GCamera::~GCamera(){

}
GCamera::GCamera(int width, int height,int x, int y)
{
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
	_currentState = 1;
	onGoto = false;
}
GCamera::GCamera()
{
}
void GCamera::Move(){
	if (onGoto){
		if (Simon::getCurrentSimon()->getCurrentLV() == 2){
			if (x <= (xDestinate - 0.5*width)){
				onGoto = false;
				return;
			}
			x -= 3;
		}
		else{
			if (x >= (xDestinate - 0.5*width)){
				onGoto = false;
				return;
			}
			x += 3;
		}
		
	}
}
void GCamera::Update(float deltatime)
{
	int cameraX, cameraY;
	Move();
	if (Simon::getCurrentSimon()->getCurrentLV() == 2){
		switch (_currentState)
		{
		case 1:
			this->_isFollowing = false;
			break;
		case 2:
			if (((Simon::getCurrentSimon()->_x > (1536 + 0.5*width)) && (Simon::getCurrentSimon()->_x < (4096 - 0.5*width)))
			&& (!((Simon::getCurrentSimon()->_x >3102) && (Simon::getCurrentSimon()->_x < 3328))))
				_isFollowing = true;
			else
			{
				this->_isFollowing = false;
				break;
			}
			break;
		case 3:
			if (((Simon::getCurrentSimon()->_x >(0 + 0.5*width)) && (Simon::getCurrentSimon()->_x < (3072 - 0.5*width)))
			&& (!((Simon::getCurrentSimon()->_x >1550) && (Simon::getCurrentSimon()->_x < 1777) && (Simon::getCurrentSimon()->_y < 677))))
				_isFollowing = true;
			else
			{
				this->_isFollowing = false;
				break;
			}

			break;
		case 4:
			if ((Simon::getCurrentSimon()->_x >(0 + 0.5*width)) && (Simon::getCurrentSimon()->_x < (1536 - 0.5*width)))
				_isFollowing = true;
			else
			{
				this->_isFollowing = false;
				break;
			}

			break;
		default:
			break;
		}
	}
	else{
		switch (_currentState)
		{
		case 1:
			if ((Simon::getCurrentSimon()->_x > (0 + 0.5*width)) && (Simon::getCurrentSimon()->_x < (1532 - 0.5*width)))
				_isFollowing = true;
			else
			{
				this->_isFollowing = false;
				break;
			}
			break;
		case 2:
			if (((Simon::getCurrentSimon()->_x > (0 + 0.5*width)) && (Simon::getCurrentSimon()->_x < (3071 - 0.5*width)))
			&& (!((Simon::getCurrentSimon()->_x >1263) && (Simon::getCurrentSimon()->_x < 1523))))
				_isFollowing = true;
			else
			{
				this->_isFollowing = false;
				break;
			}
			break;
		case 3:
			if ((Simon::getCurrentSimon()->_x >(2047 + 0.5*width)) && (Simon::getCurrentSimon()->_x < (7168 - 0.5*width)) 
				&& !((Simon::getCurrentSimon()->_x >3831) && (Simon::getCurrentSimon()->_x < 4073)))
			//if (!((Simon::getCurrentSimon()->_x >3831) && (Simon::getCurrentSimon()->_x < 4073) ))
				_isFollowing = true;
			else
			{
				this->_isFollowing = false;
			}
			if (checkBoss) _isFollowing = false;
			if ((Simon::getCurrentSimon()->_x >6910) && !checkBoss)
				checkBoss = true;
			break;
		
		default:
			break;
		}
	}
	
	
	if (onGoto) _isFollowing = false;
	cameraX = x + this->width / 2;
	cameraY = y + this->height / 2;
	if (this->_isFollowing)
	{
		cameraX = Simon::getCurrentSimon()->_x;
		this->x = cameraX - this->width / 2;
	}

	this->viewMatrix = D3DXMATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-cameraX, -cameraY, 0, 1
		);
}

void GCamera::Follow()
{
	
}

void GCamera::Unfollow()
{
	
}

bool GCamera::IsFollowing() const
{
	
	return true;
}

void GCamera::SetTransform() const
{
	Graphics::getCurGraphics()->_Direct3DDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	Graphics::getCurGraphics()->_Direct3DDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	Graphics::getCurGraphics()->_Direct3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}
GCamera* GCamera::getCurrentCamera(){
	if (!_camera)
		_camera = new GCamera(515, 440,STATE1_X,STATE1_Y);
	return _camera;
}
void GCamera::ChangeState(int state){
	_currentState = state;
	if (Simon::getCurrentSimon()->getCurrentLV() == 2){
		switch (state)
		{
		case 1:
			x = STATE1_X;
			y = STATE1_Y;
			break;
		case 2:
			x = STATE2_X;
			y = STATE2_Y;
			break;
		case 3:
			x = STATE3_X;
			y = STATE3_Y;
			break;
		case 4:
			x = STATE4_X;
			y = STATE4_Y;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (state)
		{
		case 1:
			x = STATE1_X_3;
			y = STATE1_Y_3;
			break;
		case 2:
			x = STATE2_X_3;
			y = STATE2_Y_3;
			break;
		case 3:
			x = STATE3_X_3;
			y = STATE3_Y_3;
			break;
		
		default:
			break;
		}
	}
	
}
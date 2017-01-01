#include "Stair2.h"



Stair2::Stair2(int x, int y, int parentX, int parentY, int _parentW) :
GObject(TYPE, x, y, _stairWIDTH, _stairHEIGHT)
{
	_box = Box(x, y, _stairWIDTH, _stairHEIGHT);
	this->parentX = parentX;
	this->parentY = parentY;
	this->_parentW = _parentW;
}

bool Stair2::canGoDown(){
	float x, y;

	if (swepyAABB->AABB(Simon::getCurrentSimon()->_box, this->_box, x, y)){
		return true;
	}

	return false;
}
void Stair2::Collistion(float deltatime){
	float x, y;

	if (swepyAABB->AABB(Simon::getCurrentSimon()->_box, this->_box, x, y)){
		if (Simon::getCurrentSimon()->GetState() != STATE::IS_DOWNING)
			Simon::getCurrentSimon()->ChangeState(STATE::IS_UPING);
		Simon::getCurrentSimon()->isOnStair2(true);
		if (KeyBoard::getCurrentKeyBoard()->keyUp() && !Simon::getCurrentSimon()->onGoto){
			if (this->_x + _stairWIDTH == Simon::getCurrentSimon()->_x)
				return;
			Simon::getCurrentSimon()->onGoto = true;
			Simon::getCurrentSimon()->isMoveLeft(true);
			Simon::getCurrentSimon()->isMoveRight(false);
			Simon::getCurrentSimon()->xDestinate = this->_x - _stairWIDTH;
			Simon::getCurrentSimon()->yDestinate = this->_y - SIMON_HEIGHT;
			Simon::getCurrentSimon()->_vy = -0.4;
			Simon::getCurrentSimon()->_vx = -0.4;
			
		}
		if (KeyBoard::getCurrentKeyBoard()->keyDown() && !Simon::getCurrentSimon()->onGoto){
			if (this->_x + _stairWIDTH == Simon::getCurrentSimon()->_x)
				return;
			if (this->_y + _stairHEIGHT == this->parentY+this->_parentW){
				Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
				Simon::getCurrentSimon()->isOnStair(false);
				Simon::getCurrentSimon()->isOnStair2(false);
				return;
			}
			Simon::getCurrentSimon()->ChangeState(STATE::IS_DOWNING);
			Simon::getCurrentSimon()->isMoveLeft(false);
			Simon::getCurrentSimon()->isMoveRight(true);
			Simon::getCurrentSimon()->onGoto = true;
			Simon::getCurrentSimon()->xDestinate = this->_x + _stairHEIGHT;
			Simon::getCurrentSimon()->yDestinate = this->_y + 2*_stairHEIGHT - SIMON_HEIGHT;
			Simon::getCurrentSimon()->_vy = 0.4;
			Simon::getCurrentSimon()->_vx = 0.4;

			/*if (this->_y + _stairHEIGHT == this->parentY){
			Simon::getCurrentSimon()->yDestinate = this->_y - SIMON_HEIGHT;
			Simon::getCurrentSimon()->_vy = 0;
			}*/

		}
	}
	else
	{
		Simon::getCurrentSimon()->canGoStair(false);

	}

}


Stair2::~Stair2(){

}

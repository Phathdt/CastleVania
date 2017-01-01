#include "Stairs2.h"
Stairs2::Stairs2(){
	swepyAABB = new CSweptAABB();
}
Stairs2::~Stairs2(){}
Stairs2::Stairs2(int x, int y, int w, int h)
:GObject(21, x, y, w, h){
	int size = w / _stairWIDTH;
	for (int i = 0; i < size; i++){
		Stair2* tamp = new Stair2(x + i*_stairWIDTH, y + (i )*_stairWIDTH, x, y,w);
		_listStair.push_back(tamp);
	}

	_box = Box(x, y, w, h, 0, 0);
	swepyAABB = new CSweptAABB();
}
void Stairs2::Collistion(float deltatime){
	float x, y;
	if (Simon::getCurrentSimon()->GetState() == STATE::CANT_HURT)
		return;
	if (Simon::getCurrentSimon()->isOnStair1()) return;
	if (swepyAABB->AABB(Simon::getCurrentSimon()->_box, this->_box, x, y)){
		Simon::getCurrentSimon()->canGoStair(true);
		if (x + y != 0){
			//
			if (KeyBoard::getCurrentKeyBoard()->keyUp()){


				float dx = (_x+this->_width)-Simon::getCurrentSimon()->_x - _stairWIDTH;
				if (dx == 0){
					Simon::getCurrentSimon()->onGoto = false;
					Simon::getCurrentSimon()->isMoveLeft(true);
					Simon::getCurrentSimon()->isMoveRight(false);
					for each (Stair2 * b in _listStair)
						b->Collistion(deltatime);
				}

				else if (!Simon::getCurrentSimon()->isOnStair()){
					Simon::getCurrentSimon()->onGoto = true;
					Simon::getCurrentSimon()->_x += dx / deltatime;
					if (dx < deltatime)
						Simon::getCurrentSimon()->_x += dx;
				}

			}
			if (Simon::getCurrentSimon()->isOnStair()){
				for each (Stair2 * b in _listStair)
					b->Collistion(deltatime);
			}

		}
		else
		{

			//Simon::getCurrentSimon()->canGoStair(false);
			if (getLast()->canGoDown()){
				if (KeyBoard::getCurrentKeyBoard()->keyDown()){

					Simon::getCurrentSimon()->ChangeState(STATE::IS_DOWNING);
					Simon::getCurrentSimon()->isMoveLeft(false);
					Simon::getCurrentSimon()->isMoveRight(true);
					Simon::getCurrentSimon()->onGoto = true;
					Simon::getCurrentSimon()->xDestinate = this->_x - SIMON_HEIGHT;
					Simon::getCurrentSimon()->yDestinate = this->_y + _stairHEIGHT - SIMON_HEIGHT;
					Simon::getCurrentSimon()->_vy = 0.4;
					Simon::getCurrentSimon()->_vx = 0.4;
					return;
				}
			}
			if (!Simon::getCurrentSimon()->onGoto){
				Simon::getCurrentSimon()->isOnStair(false);
				Simon::getCurrentSimon()->isOnStair2(false);
				if ((Simon::getCurrentSimon()->GetState() == STATE::IS_UPING || Simon::getCurrentSimon()->GetState() == STATE::IS_DOWNING)
					&& !(KeyBoard::getCurrentKeyBoard()->keyUp()))
					Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
			}
		
		}

	}
	else
	{
		Simon::getCurrentSimon()->canGoStair(false);		
	}
	int stateCollid = swepyAABB->CollideCheck(Simon::getCurrentSimon()->_box, this->_box, x, y);
	if ((stateCollid == COLLIDE_STATE::BOTTOM) && !(Simon::getCurrentSimon()->onGoto)){
		if (Simon::getCurrentSimon()->isFighting()){
			Simon::getCurrentSimon()->ChangeState(STATE::IS_FIGHTING);
		}
		else{
			Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
		}
	}
}
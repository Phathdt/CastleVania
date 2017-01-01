#include "Stairs.h"
Stairs::Stairs(){
	swepyAABB = new CSweptAABB();
}
Stairs::~Stairs(){}
Stairs::Stairs(int x, int y, int w, int h)
:GObject(21, x, y, w, h){
	int size = w / _stairWIDTH;
	for (int i = 0; i < size; i++){
		Stair* tamp = new Stair(x + i*_stairWIDTH, y-(i+1)*_stairWIDTH,x,y);
		_listStair.push_back(tamp);
	}
	
	_box = Box(x, y-h, w, h, 0, 0);
	swepyAABB = new CSweptAABB();
}
void Stairs::Collistion(float deltatime){
	float x, y;
	if (Simon::getCurrentSimon()->GetState() == STATE::CANT_HURT)
		return;
	if (Simon::getCurrentSimon()->isOnStair2()) return;
	if (swepyAABB->AABB(Simon::getCurrentSimon()->_box, this->_box, x, y)){
		Simon::getCurrentSimon()->canGoStair(true);
		if (x + y != 0){
			//
			if (KeyBoard::getCurrentKeyBoard()->keyUp()){

				
				float dx = _x - Simon::getCurrentSimon()->_x - _stairWIDTH;
				if (dx == 0){
					Simon::getCurrentSimon()->onGoto = false;
					Simon::getCurrentSimon()->isMoveLeft(false);
					Simon::getCurrentSimon()->isMoveRight(true);
					for each (Stair * b in _listStair)
						b->Collistion(deltatime);
				}

				else if (!Simon::getCurrentSimon()->isOnStair()){
					Simon::getCurrentSimon()->onGoto = true;
					Simon::getCurrentSimon()->_x += dx / deltatime;
					if (abs(dx) < deltatime)
						Simon::getCurrentSimon()->_x += dx;
				}

			}
			if (Simon::getCurrentSimon()->isOnStair()){
				for each (Stair * b in _listStair)
					b->Collistion(deltatime);
			}
			
		}
		else
		{
			
			//Simon::getCurrentSimon()->canGoStair(false);
			if (getLast()->canGoDown()){
				if (KeyBoard::getCurrentKeyBoard()->keyDown()){
					
					Simon::getCurrentSimon()->ChangeState(STATE::IS_DOWNING);
					Simon::getCurrentSimon()->isMoveLeft(true);
					Simon::getCurrentSimon()->isMoveRight(false);
					Simon::getCurrentSimon()->onGoto = true;
					Simon::getCurrentSimon()->xDestinate = _x + this->_width - _stairWIDTH ;
					Simon::getCurrentSimon()->yDestinate = _y - this->_width - SIMON_HEIGHT + _stairWIDTH;
					Simon::getCurrentSimon()->_vy = 0.4;
					Simon::getCurrentSimon()->_vx = -0.4;
					return;
				}
			}
			if (!Simon::getCurrentSimon()->onGoto){
				Simon::getCurrentSimon()->isOnStair(false);
				Simon::getCurrentSimon()->isOnStair1(false);
				if (Simon::getCurrentSimon()->GetState() == STATE::IS_UPING || Simon::getCurrentSimon()->GetState() == STATE::IS_DOWNING)
					Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
			}
		
		}
		
	}
	else
	{
		Simon::getCurrentSimon()->canGoStair(false);
		
	}
	int stateCollid = swepyAABB->CollideCheck(Simon::getCurrentSimon()->_box, this->_box, x, y);
	if (stateCollid == COLLIDE_STATE::BOTTOM){
		if (Simon::getCurrentSimon()->isFighting()){
			Simon::getCurrentSimon()->ChangeState(STATE::IS_FIGHTING);
		}
		else{
			Simon::getCurrentSimon()->ChangeState(STATE::IS_STANDING);
		}
	}
}
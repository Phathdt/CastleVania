#include "SweptAABB.h"


CSweptAABB::CSweptAABB()
{
}

float CSweptAABB::SweptAABB(Box b1, Box b2, float& normalx, float& normaly, float deltatime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	int a = 0;
	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (b1.vx*deltatime);
		xExit = xInvExit / (b1.vx*deltatime);
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry /( b1.vy*deltatime);
		yExit = yInvExit / (b1.vy*deltatime);
	}

	// find the earliest/latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if ((xEntry > yEntry) && (b1.y >= b2.y&&b1.y <= (b2.y + b2.h) || (((b1.y + b1.h) >= b2.y && (b1.y + b1.h) <= (b2.y + b2.h)))))
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else if ((b1.x >= b2.x&&b1.x <= (b2.x + b2.w) || (((b1.x + b1.w) >= b2.x && (b1.x + b1.w) <= (b2.x + b2.w)))))
		{
			if ((yInvEntry < 0.0f))
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}

	
}
Box CSweptAABB::GetSweptBroadphaseBox(Box b)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphasebox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphasebox.w = b.vx > 0 ? b.vx + b.w : b.w - b.vx;
	broadphasebox.h = b.vy > 0 ? b.vy + b.h : b.h - b.vy;

	return broadphasebox;
}
bool CSweptAABB::AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return false;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

int CSweptAABB::CollideCheck(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;
	if ((b2.x == 3200) && (b2.y = 1058))
		int a = 0;
	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return COLLIDE_STATE::NONE;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;
	if (moveX == 0 && moveY!=0){
		if (l == 0) return COLLIDE_STATE::RIGHT;
		return COLLIDE_STATE::LEFT;
	}
	if (moveY == 0 && moveX!=0){
		if (t == 0)return COLLIDE_STATE::BOTTOM;
		return COLLIDE_STATE::TOP;
	}
	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;
	int fix = std::min(r, std::min(l, std::min(t, b)));
	/*if (moveY<0) return COLLIDE_STATE::BOTTOM;
	if (moveX>0) return COLLIDE_STATE::TOP;
	if (moveX>0) return COLLIDE_STATE::LEFT;
	return COLLIDE_STATE::RIGHT;*/
	if (moveY<0 && moveY >= -3){
		if (!Simon::getCurrentSimon()->isOnStair())
			Simon::getCurrentSimon()->_y += moveY;
		return COLLIDE_STATE::BOTTOM;
	}
		
	if (moveY>0 && moveY <= 3) 
		return COLLIDE_STATE::TOP;
	if (moveX>0 && moveX <= 3) 
		return COLLIDE_STATE::LEFT;
	if (moveX<0 && moveX >= -3)
		return COLLIDE_STATE::RIGHT;
	return COLLIDE_STATE::NONE;
}
int CSweptAABB::CollideCheck(GObject* bo1, GObject* bo2, float& moveX, float& moveY)
{
	Box b1 = bo1->_box;
	Box b2 = bo2->_box;
	moveX = moveY = 0.0f;
	if ((b2.x == 3200) && (b2.y = 1058))
		int a = 0;
	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0)
		return COLLIDE_STATE::NONE;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;
	if (moveX == 0 && moveY != 0){
		if (l == 0) return COLLIDE_STATE::RIGHT;
		return COLLIDE_STATE::LEFT;
	}
	if (moveY == 0 && moveX != 0){
		if (t == 0)return COLLIDE_STATE::BOTTOM;
		return COLLIDE_STATE::TOP;
	}
	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;
	int fix = std::min(r, std::min(l, std::min(t, b)));
	
	if (moveY<0 && moveY >= -3){
		
		//bo1->_y += moveY;
		return COLLIDE_STATE::BOTTOM;
	}

	if (moveY>0 && moveY <= 3)
		return COLLIDE_STATE::TOP;
	if (moveX>0 && moveX <= 3)
		return COLLIDE_STATE::LEFT;
	if (moveX<0 && moveX >= -3)
		return COLLIDE_STATE::RIGHT;
	return COLLIDE_STATE::NONE;
}
CSweptAABB::~CSweptAABB()
{
}

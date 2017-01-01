#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__	

#include "Item.h"
#define _WIDTH	30
#define _HEIGHT	32
#define _SPRITE L"item/5.png"
#define TYPE TypeGame::Item_stop_watch

class StopWatch : public Item {
private:

public:
	StopWatch(int x, int y, int x2, int y2);
	StopWatch();
	~StopWatch();
};

#endif
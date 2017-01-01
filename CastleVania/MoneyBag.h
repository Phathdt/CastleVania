#ifndef __MONEYBAG_H__
#define __MONEYBAG_H__	

#include "Item.h"
#define _WIDTH	30
#define _HEIGHT	30
#define _SPRITE L"item/2.png"
#define TYPE TypeGame::Item_money_bag

enum MoneyColor{
	Red = 0,
	White = 1,
	Blue = 2
};
class MoneyBag : public Item {
private:
	int _moneycolor;
public:
	MoneyBag(int x, int y, int x2, int y2);
	void SetFrame(float deltattime);
	void Update(float deltatime);
	MoneyBag();
	~MoneyBag();
};

#endif
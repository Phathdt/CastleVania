
#define QUADTREE_REF "Maps/quad.txt"
#define OBJECT_REF "Maps/object.txt"

#define QUADTREE_REF_3 "Maps/quad2.txt"
#define OBJECT_REF_3 "Maps/object2.txt"

#include "Rect.h"
#include "Quadnode.h"
#include "GObject.h"
#include "Simon.h"

#include "Bat.h"
#include "Spearguard.h"
#include "Bricks.h"
#include "Ghost.h"
#include "MedusaHead.h"
#include "BonePillar.h"
#include "Fleaman.h"
#include "Raven.h"
#include "Skeleton.h"

#include "Brickhidden.h"
#include "Brickmoving.h"
#include "Fireandle.h"
#include "Firetower.h"
#include "Stair.h"
#include "Stairs.h"
#include "Stairs2.h"
#include "Door.h"
#include "Trap.h"

#include "Axe.h"
#include "BigHeart.h"
#include "Cross.h"
#include "DoubleShot.h"
#include "HolyWater.h"
#include "Item.h"
#include "ItemNone.h"
#include "Knife.h"
#include "MoneyBag.h"
#include "MorningStar.h"
#include "Roast.h"
#include "Rosary.h"
#include "SmallHeart.h"
#include "SpiritBall.h"
#include "StopWatch.h"

#include "Medusa.h"
#include "Mummies.h"

#include "DeathPlace.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
class Quadtree{
private:
	GObject** _listObject;
	static Quadtree* _currentQuadtree;
	static int _lastLV;
public:
	Quadtree();
	~Quadtree();
	QuadNode* _root;
	static Quadtree* getCurrentQuadtree();
	void load();
	void loadObject();
	GObject* getObject(int type, int x, int y, int width, int height,bool left=true);
};
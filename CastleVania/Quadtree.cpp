#include "Quadtree.h"
Quadtree::Quadtree(){
}
Quadtree::~Quadtree(){}
Quadtree* Quadtree::_currentQuadtree = 0;
int Quadtree::_lastLV = 2;
void Quadtree :: load(){
	loadObject();
	string currentQuad = "";
	string currentObject = "";
	switch (Simon::getCurrentSimon()->getCurrentLV())
	{
	case 2:
		currentQuad = QUADTREE_REF;
		currentObject = OBJECT_REF;
		break;
	case 3:
		currentQuad = QUADTREE_REF_3;
		currentObject = OBJECT_REF_3;
	default:
		break;
	}
	ifstream myfile(currentQuad);
	vector<QuadNode*> list;
	while (!myfile.eof())
	{
		QuadNode* tamp = new QuadNode();
		myfile >> tamp->id;
		myfile >> tamp->bound->x;
		myfile >> tamp->bound->y;
		myfile >> tamp->bound->witdh;
		myfile >> tamp->bound->height;
		int count = 0;
		myfile >> count;
		for (int i = 0; i < count; i++){
			int id;
			myfile >> id;
			tamp->listObject.push_back(_listObject[id]);
		}
		list.push_back(tamp);
	}
	for each (QuadNode * b in list){
		if (b->id == 1){
			_root = b;
			continue;
		}
		int rootId = b->id / 10;
		for each(QuadNode* tamp in list){
			if (tamp->id == rootId){
				switch (b->id%10)
				{
					case 1:
						tamp->_nodeTL = b;
					break;
					case 2:
						tamp->_nodeTR = b;
						break;
					case 3:
						tamp->_nodeBL = b;
						break;
					case 4:
						tamp->_nodeBR = b;
						break;
				}
				break;
			}
		}
	}
}
void Quadtree::loadObject(){
	string currentQuad = "";
	string currentObject = "";
	switch (Simon::getCurrentSimon()->getCurrentLV())
	{
	case 2:
		currentQuad = QUADTREE_REF;
		currentObject = OBJECT_REF;
		break;
	case 3:
		currentQuad = QUADTREE_REF_3;
		currentObject = OBJECT_REF_3;
	default:
		break;
	}
	ifstream myfile(currentObject);
	int count = 0;
	myfile >> count;
	_listObject = new GObject*[count];
	for (int i = 0; i < count; i++){	
	
		int x, y, width, height, type, id, y2, x2 = 0;
		myfile >> id;
		myfile >> type;
		myfile >> x;
		myfile >> y;
		myfile >> width;
		myfile >> height;
		if (type>10 && type<23)
			_listObject[i] = getObject(type, x, y, width, height);



		myfile >> x2;
		myfile >> y2;
		myfile >> width;
		myfile >> height;
		if ((type <= 10 || type >= 23) && type != 6&&type!=5){
			_listObject[i] = getObject(type, x2, y2, width, height);
		}
		else{
			if (type == 6 || type == 5){
				if (x != x2){
					_listObject[i] = getObject(type, width, height, x2, y2, false);
				}
				else
					_listObject[i] = getObject(type, x2, y2, width, height);

			}
		} 

		_listObject[i]->_id = id;
	}
}
 Quadtree* Quadtree::getCurrentQuadtree(){
	if (_currentQuadtree == 0){
		_currentQuadtree = new Quadtree();
		_currentQuadtree->load();
	}
	if (Simon::getCurrentSimon()->getCurrentLV()!=_lastLV)
		_currentQuadtree->load();
	_lastLV = Simon::getCurrentSimon()->getCurrentLV();
	return _currentQuadtree;
}
 GObject* Quadtree::getObject(int type, int x, int y, int width, int height,bool left)
 {
	 GObject* tamp=0;
	 switch (type){

	 case TypeGame::Boss_Medusa:tamp = new Medusa(x, y); 
		 break;
	 case TypeGame::Boss_Mummies:tamp = new Mummies(x, y, width, height); break;

	 case TypeGame::Enemy_Bat: tamp = new Bat(x, y, width, height); break;
	 case TypeGame::Ground_Brick: tamp = new Bricks(x, y, width, height); break;
	 case TypeGame::Enemy_Spearguard: tamp = new Spearguard(x, y, width, height); break;
	 case TypeGame::Enemy_Ghost: tamp = new Ghost(x, y, width, height, left); break;
	 case TypeGame::Enemy_Medusahead: tamp = new MedusaHead(x, y, width, height, left); break;
	 case TypeGame::Enemy_Bonepilla:tamp = new BonePillar(x, y); break;
	 case TypeGame::Enemy_Fleaman:tamp = new Fleaman(x, y, width, height); break;
	 case TypeGame::Enemy_Raven:tamp = new Raven(x, y); break;
	 case TypeGame::Enemy_Skeleton:tamp = new Skeleton(x, y); break;


	 case TypeGame::Ground_Stair_Down: tamp = new Stairs2(x, y, width, height); break;
	 case TypeGame::Ground_Stair_Up: tamp = new Stairs(x, y, width, height); break;
	 case TypeGame::Ground_Hidden: tamp = new Brickhidden(x, y); break;
	 case TypeGame::Ground_Moving_Brick: tamp = new Brickmoving(x, y, width, height); break;
	 case TypeGame::Ground_Fireandle: tamp = new Fireandle(x, y); break;
	 case TypeGame::Ground_Firetower: tamp = new Firetower(x, y); break;
	 case TypeGame::Ground_Opendoor:tamp = new Door(x, y); break;
	 case TypeGame::Ground_Trap:tamp = new Trap(x, y); break;

	 case TypeGame::Item_axe: tamp = new Axe(x, y, width, height); break;
	 case TypeGame::Item_big_heart: tamp = new BigHeart(x, y, width, height); break;
	 case TypeGame::Item_cross: tamp = new Cross(x, y, width, height); break;
	 case TypeGame::Item_double_shot: tamp = new DoubleShot(x, y, width, height); break;
	 case TypeGame::Item_holy_water: tamp = new HolyWater(x, y, width, height); break;
	 case TypeGame::Item_knife: tamp = new Knife(x, y, width, height); break;
	 case TypeGame::Item_money_bag: tamp = new MoneyBag(x, y, width, height); break;
	 case TypeGame::Item_morning_star: tamp = new MorningStar(x, y, width, height); break;
	 case TypeGame::Item_roast: tamp = new Roast(x, y, width, height); break;
	 case TypeGame::Item_rosary: tamp = new Rosary(x, y, width, height); break;
	 case TypeGame::Item_small_heart: tamp = new SmallHeart(x, y, width, height); break;
	 case TypeGame::Item_spirit_ball: tamp = new SpiritBall(x, y, width, height); break;
	 case TypeGame::Item_stop_watch: tamp = new StopWatch(x, y, width, height); break;

	 case TypeGame::Death_Place:tamp = new DeathPlace(x, y, width, height); break;
	 default: tamp = new GObject(1,x, y, width, height); break;
	 }
	 return tamp;
 }


 
#include"Quadnode.h"
QuadNode::QuadNode(){
	bound = new Rect();
}
QuadNode::~QuadNode(){}
bool QuadNode::IsContain(){

	return !(GCamera::getCurrentCamera()->x + 515 < bound->x ||
		GCamera::getCurrentCamera()->y + 440 < bound->y ||
		GCamera::getCurrentCamera()->x > bound->x + bound->witdh ||
		GCamera::getCurrentCamera()->y > bound->y + bound->height);
}
void QuadNode::Retrieve(vector<GObject*>& listGObject){
	if (this->id == 12411)
		int a = 0;
	if (_nodeTL){
		if (_nodeTL->IsContain())
			_nodeTL->Retrieve(listGObject);
		if (_nodeTR->IsContain())
			_nodeTR->Retrieve(listGObject);
		if (_nodeBL->IsContain())
			_nodeBL->Retrieve(listGObject);
		if (_nodeBR->IsContain())
			_nodeBR->Retrieve(listGObject);
	}
	if (this->IsContain()){
		for each(GObject* tamp in listObject){
			int count = 0;
			for each(GObject* object in listGObject){
				if (object->_id == tamp->_id) count++;
			}
			if (count==0)
			listGObject.push_back(tamp);
		}
	}
}
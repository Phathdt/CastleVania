#include"Rect.h"
#include"GObject.h"
#include"Simon.h"
#include "GCamera.h"
#include <vector>
using namespace std;
class QuadNode{
private:
	
public:
	QuadNode* _nodeTL;
	QuadNode* _nodeTR;
	QuadNode* _nodeBL;
	QuadNode* _nodeBR;

	vector<GObject*> listObject;
	int id;
	Rect* bound;
	bool IsContain();
	void Retrieve(vector<GObject*>& listGObject);
	QuadNode();
	~QuadNode();
};
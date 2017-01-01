#ifndef _STATE_H_
#define _STATE_H_

#include "Graphics.h"
#include "GTexture.h"
#include "Simon.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
#define SIZE 16
#define IMAGE_REF_2 L"Maps/TileMap.png"
#define MATRIX_REF_2 "Maps/MaTrix.txt"
#define IMAGE_REF_3 L"Maps/TileMap2.png"
#define MATRIX_REF_3 "Maps/MaTrix2.txt"

class State{
	int** _matrix;
	int _col;
	int _row;
	int _listTileCount;
	int _lastLV;
	GTexture* _bgTexture;
	static State* _state;
public:
	State();
	~State();
	static State* getCurrentState();
	void load();
	void draw();
};
#endif
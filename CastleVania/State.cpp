#include "State.h"

State* State::_state = 0;
State::State(){
	this->_lastLV = 2;
}
State::~State(){}
void State::load(){
	LPCWSTR currentTexture=L"";
	string currentMatrix="";
	switch (Simon::getCurrentSimon()->getCurrentLV())
	{
	case 2:
		currentTexture = IMAGE_REF_2;
		currentMatrix = MATRIX_REF_2;
		break;
	case 3:
		currentTexture = IMAGE_REF_3;
		currentMatrix = MATRIX_REF_3;
		break;
	default:
		break;
	}
	string line;
	ifstream myfile(currentMatrix);
	myfile >> _listTileCount;
	myfile >> _col;
	myfile >> _col;
	myfile >> _col;
	myfile >> _row;
	_matrix = new int * [_row];
	for (int i = 0; i < _row; i++){
		_matrix[i] = new int[_col];
	}
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++){
			myfile >> _matrix[i][j];
		}
	}
	_bgTexture = new GTexture(currentTexture, _listTileCount, 1, _listTileCount, false);
}
void State::draw(){
	if (Simon::getCurrentSimon()->getCurrentLV() != _lastLV)
		load();
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++) {

			int index = _matrix[i][j];

			RECT srect;
			srect.left = index*SIZE;
			srect.top = 0;
			srect.right = srect.left + SIZE ;
			srect.bottom = srect.top + SIZE;

			D3DXVECTOR3 position(float(j * SIZE), float(i * SIZE)+90, 0.0f);
			
			Graphics::getCurGraphics()->_sprite->Draw(
				_bgTexture->Texture,
				&srect,
				NULL,
				&position,
				0xFFFFFFFF
				);
		}
	}
	_lastLV = Simon::getCurrentSimon()->getCurrentLV();
}
State* State::getCurrentState(){
	if (!_state){
		_state = new State();
		_state->load();
	}
	return _state;

}
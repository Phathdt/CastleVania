#include "Board.h"
Board* Board::current = 0;
Board::Board(){
	_board = new GTexture(SPRITE_BOARD, 1, 1, 1,true);
	_all = new GTexture(SPRITE_ALL, 8, 2, 16,true);
	_boom = new GTexture(SPRITE_BUMERANG, 1, 1, 1);
	_knife = new GTexture(SPRITE_KNIFE, 1, 1, 1);
	 _score=0;
	 _playerHp=16;
	 _enemyHP=16;
	 _time=0;
	 _heart=5;
	 _life=3;
	 _state=2;

	 _scorePosition = D3DXVECTOR3(105.0,10.0f,0.0f);
	 _playerHpPosition = D3DXVECTOR3(105.0, 38.0f, 0.0f);
	 _enemyHPPosition = D3DXVECTOR3(105.0, 55.0f, 0.0f);
	 _timePosition = D3DXVECTOR3(275.0, 10.0f, 0.0f);
	 _heartPosition = D3DXVECTOR3(350.0, 35.0f, 0.0f);
	 _lifePosition = D3DXVECTOR3(350.0, 55.0f, 0.0f);
	 _statePosition = D3DXVECTOR3(450.0, 10.0f, 0.0f);
	 _wheaponPosition = D3DXVECTOR3(261.0, 40.0f, 0.0f);

	 rect0.left=2;
	 rect0.top = 4;
	 rect0.right = 18;
	 rect0.bottom = 20;

	 rect1.left = 2;
	 rect1.top = 24;
	 rect1.right = 18;
	 rect1.bottom = 40;

	 rect2.left = 18;
	 rect2.top = 4;
	 rect2.right = 34;
	 rect2.bottom = 20;

	 rect3.left = 18;
	 rect3.top = 24;
	 rect3.right = 34;
	 rect3.bottom = 40;

	 rect4.left = 34;
	 rect4.top = 4;
	 rect4.right = 50;
	 rect4.bottom = 20;

	 rect5.left = 34;
	 rect5.top = 24;
	 rect5.right = 50;
	 rect5.bottom = 40;

	 rect6.left = 50;
	 rect6.top = 4;
	 rect6.right = 66;
	 rect6.bottom = 20;

	 rect7.left = 50;
	 rect7.top = 24;
	 rect7.right = 66;
	 rect7.bottom = 40;

	 rect8.left = 66;
	 rect8.top = 4;
	 rect8.right = 82;
	 rect8.bottom = 20;

	 rect9.left = 66;
	 rect9.top = 24;
	 rect9.right = 82;
	 rect9.bottom = 40;

}
Board* Board::GetCurrentBoard(){
	if (!current)
		current = new Board();
	return current;
}
void Board::drawHeart(){
	drawNumber(_heartPosition, _heart / 10);
	D3DXVECTOR3 tamp = _heartPosition;
	tamp.x += 16;

	drawNumber(tamp, _heart % 10 );
}
void Board::drawWheapon(){
	GTexture* currentTexture = NULL;
	if (_wheapon == 1){
		currentTexture = _boom;
	}
	else{
		currentTexture = _knife;
	}
	RECT tamp;
	tamp.left = 0;
	tamp.top = 0;
	tamp.right = 32;
	tamp.bottom = 28;
	float camerax, cameray;
	D3DXVECTOR3 position = _wheaponPosition;
	camerax = GCamera::getCurrentCamera()->x;
	cameray = GCamera::getCurrentCamera()->y;
	position.x += camerax;
	position.y += cameray;
	Graphics::getCurGraphics()->_sprite->Draw(
		currentTexture->Texture,
		&tamp,
		NULL,
		&position,
		0xFFFFFFFF
		);
}
void Board::drawLife(){
	drawNumber(_lifePosition, _life / 10);
	D3DXVECTOR3 tamp = _lifePosition;
	tamp.x += 16;

	drawNumber(tamp, _life % 10);
}
void Board::drawState(){
	drawNumber(_statePosition, _state / 10);
	D3DXVECTOR3 tamp = _statePosition;
	tamp.x += 16;

	drawNumber(tamp, _state % 10);
}
void Board::drawTime(){
	drawNumber(_timePosition, _time / 1000);
	D3DXVECTOR3 tamp = _timePosition;
	tamp.x += 16;

	drawNumber(tamp, (_time % 1000) / 100);
	tamp.x += 16;

	drawNumber(tamp, (_time % 100) / 10);
	tamp.x += 16;

	drawNumber(tamp, (_time % 10) / 1);
}
void Board::drawScore(){
	drawNumber(_scorePosition, _score / 100000);
	D3DXVECTOR3 tamp = _scorePosition;
	tamp.x += 16;

	drawNumber(tamp, (_score % 100000) / 10000);
	tamp.x += 16;

	drawNumber(tamp, (_score % 10000) / 1000);
	tamp.x += 16;

	drawNumber(tamp, (_score % 1000) / 100);
	tamp.x += 16;

	drawNumber(tamp, (_score % 100) / 10);
	tamp.x += 16;

	drawNumber(tamp, (_score % 10) / 1);
}
void Board::drawNumber(D3DXVECTOR3 position,int numb){
	RECT tamp;
	float camerax, cameray;
	camerax = GCamera::getCurrentCamera()->x;
	cameray = GCamera::getCurrentCamera()->y;
	position.x += camerax;
	position.y += cameray;
	switch (numb)
	{
	case 0: tamp = rect0;
		break;
	case 1: tamp = rect1;
		break;
	case 2: tamp = rect2;
		break;
	case 3: tamp = rect3;
		break;
	case 4: tamp = rect4;
		break;
	case 5: tamp = rect5;
		break;
	case 6: tamp = rect6;
		break;
	case 7: tamp = rect7;
		break;
	case 8: tamp = rect8;
		break;
	case 9: tamp = rect9;
		break;

	default:
		break;
	}
	Graphics::getCurGraphics()->_sprite->Draw(
		_all->Texture,
		&tamp,
		NULL,
		&position,
		0xFFFFFFFF
		);
}
void Board::drawPlaerHP(){
	float x = _playerHpPosition.x;
	float y=_playerHpPosition.y;
	float camerax, cameray;
	camerax = GCamera::getCurrentCamera()->x;
	cameray = GCamera::getCurrentCamera()->y;

	RECT srectFull;
	srectFull.left = 84;
	srectFull.top = 6;
	srectFull.right = 100;
	srectFull.bottom = 20;
	RECT srectNone;
	srectNone.left = 84;
	srectNone.top = 26;
	srectNone.right = 100;
	srectNone.bottom = 40;
	RECT srectHafl;
	srectHafl.left = 120;
	srectHafl.top = 6;
	srectHafl.right = 136;
	srectHafl.bottom = 20;
	for (int i = 0; i < _playerHp / 2; i++){
		x = _playerHpPosition.x + i * 16 + camerax;
		y = _playerHpPosition.y + cameray;
		D3DXVECTOR3 tamp = D3DXVECTOR3(x, y, 0.0f);
		Graphics::getCurGraphics()->_sprite->Draw(
			_all->Texture,
			&srectFull,
			NULL,
			&tamp,
			0xFFFFFFFF
			);
	}
	for (int i = 0; i < (16-_playerHp)%2; i++){
		x +=  16;
		//y = _playerHpPosition.y;
		D3DXVECTOR3 tamp = D3DXVECTOR3(x, y, 0.0f);
		Graphics::getCurGraphics()->_sprite->Draw(
			_all->Texture,
			&srectHafl,
			NULL,
			&tamp,
			0xFFFFFFFF
			);
	}
	for (int i = 0; i < (16 - _playerHp) / 2; i++){
		x += 16;
		//y = _playerHpPosition.y;
		D3DXVECTOR3 tamp = D3DXVECTOR3(x, y, 0.0f);
		Graphics::getCurGraphics()->_sprite->Draw(
			_all->Texture,
			&srectNone,
			NULL,
			&tamp,
			0xFFFFFFFF
			);
	}
}
void Board::drawEnemyHP(){
	float x = _enemyHPPosition.x;
	float y = _enemyHPPosition.y;
	float camerax, cameray;
	camerax = GCamera::getCurrentCamera()->x;
	cameray = GCamera::getCurrentCamera()->y;

	RECT srectFull;
	srectFull.left = 120;
	srectFull.top = 26;
	srectFull.right = 136;
	srectFull.bottom = 40;
	RECT srectNone;
	srectNone.left = 84;
	srectNone.top = 26;
	srectNone.right = 100;
	srectNone.bottom = 40;
	RECT srectHafl;
	srectHafl.left = 120;
	srectHafl.top = 6;
	srectHafl.right = 136;
	srectHafl.bottom = 20;
	for (int i = 0; i < _enemyHP / 2; i++){
		x = _enemyHPPosition.x + i * 16 + camerax;
		y = _enemyHPPosition.y + cameray;
		D3DXVECTOR3 tamp = D3DXVECTOR3(x, y, 0.0f);
		Graphics::getCurGraphics()->_sprite->Draw(
			_all->Texture,
			&srectFull,
			NULL,
			&tamp,
			0xFFFFFFFF
			);
	}
	for (int i = 0; i < (16 - _enemyHP) % 2; i++){
		x += 16;
		//y = _playerHpPosition.y;
		D3DXVECTOR3 tamp = D3DXVECTOR3(x, y, 0.0f);
		Graphics::getCurGraphics()->_sprite->Draw(
			_all->Texture,
			&srectHafl,
			NULL,
			&tamp,
			0xFFFFFFFF
			);
	}
	for (int i = 0; i < (16 - _enemyHP) / 2; i++){
		x += 16;
		//y = _playerHpPosition.y;
		D3DXVECTOR3 tamp = D3DXVECTOR3(x, y, 0.0f);
		Graphics::getCurGraphics()->_sprite->Draw(
			_all->Texture,
			&srectNone,
			NULL,
			&tamp,
			0xFFFFFFFF
			);
	}
}
void Board::Draw(){
	
	float x = GCamera::getCurrentCamera()->x;
	float y = GCamera::getCurrentCamera()->y;
	RECT srect;
	srect.left = 0;
	srect.top = 0;
	srect.right = 515;
	srect.bottom = 90;
	D3DXVECTOR3 position(x, y, 0.0f);
	Graphics::getCurGraphics()->_sprite->Draw(
		_board->Texture,
		&srect,
		NULL,
		&position,
		0xFFFFFFFF
		);
	drawPlaerHP();
	drawEnemyHP();
	drawHeart();
	drawState();
	drawLife();
	drawTime();
	drawScore();
	drawWheapon();
}
void Board::Update(){
	_heart = Simon::getCurrentSimon()->getHeart();
	_playerHp = Simon::getCurrentSimon()->getHP();
	_enemyHP = Simon::getCurrentSimon()->getBossHP();
	_life = Simon::getCurrentSimon()->getLife();
}
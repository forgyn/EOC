#pragma once


#include "Utility.h"
#include "Player.h"
#include "EnemyList.h"
#include "ClassList.h"
#include "Party.h"
#include "TextureHandle.h"


class Map;
class Object;

//TextureHandler* Object::_texture_handler = nullptr;




class GameSystem{
public:
	GameSystem();
	~GameSystem();
	bool run();
	void initTextures();
	void select_resolution();
private:
	RenderWindow *_mainWindow = nullptr;
	VideoMode *_videoMode = nullptr;
	Mouse* _mouse = nullptr;
	Event* _event = nullptr;
	Font* _font = nullptr;
	GameHandle _gameHandle;
	GAME_STATE _gameState = GAME_STATE::OK;
	Player* _player = nullptr;
	PlayerParty* _player_party = nullptr;

	//TextureHandler* _texture_handler = nullptr;

};


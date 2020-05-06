#pragma once


#include "Utility.h"
#include "ButtonMenu.h"
#include "Player.h"
#include "EnemyList.h"
#include "ClassList.h"
#include "Party.h"
#include "TextureHandle.h"
#include "GameHandle.h"
#include "FontHandle.h"

class Map;
class Object;



class GameSystem{
public:
	GameSystem();
	~GameSystem();
	bool run();
	void initTextures();
	void initFonts();
	void select_resolution();
private:
	RenderWindow *_mainWindow = nullptr;
	VideoMode *_videoMode = nullptr;
	GAME_STATE _gameState = GAME_STATE::OK;
	Player* _player = nullptr;
	PlayerParty* _player_party = nullptr;

	//TextureHandler* _texture_handler = nullptr;

};


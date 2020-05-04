#pragma once

//INCLUDES
#include <random>
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include "InputsOutputs/Button.h"
#include "InputsOutputs/ButtonMenu.h"



//NAMESPACES
using namespace std;
using namespace sf;

//DEFS
#define DEBUG
#define BITS_PRER_PIXEL 32U
#define MAX_FPS 60
#define LOOP(n) for(int i = 0; i<n ; i++)
#define TILE_SIZE 50
#define DEBUG_COLOR Color::Yellow
#define MAX_FPS 60
#define PLAYER_SIZE_X 50
#define PLAYER_SIZE_Y 75
#define RANDOM_MAP_SIZE 20
#define ZOOMING_STRENGH 0.5f
#define AUTO_COMBAT_SPEED 0.7f
#define MAX_COMBAT_SIDE_SIZE 5
#define MENU_SIZE_PORTION 5.f

//ENUMS
enum class Object_Type { Error, Static_Entity, Dynamic_Entity };
enum class Entity_Type { Error, NPC, Player, Enemy, Party };
enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };
enum class GAME_STATE { OK, END, ERROR };
enum class Map_Type {
	ERROR,
	FOREST,
	DESERT,
	CAVE,
	MOUNTAIN,
	CITY
};
enum class Entity_Stand {
	ERROR,
	HOSTILE,
	FRIENDLY,
	PLAYER,
	NEUTRAL
};


enum class Enemy_Type {
	ERROR,
	SKELETON,
	ZOMBIE,
	SLIME,
};

enum class Enemy_Class {
	MONSTER,
	WARRIOR,
	ARCHER,
	MAGE,
	ROGUE
};

enum class Animation_Type {
	ERROR,
	IDLE,
	BATTLE,
	MOVING
};


//OTHER
static default_random_engine _RANDOM_GENERATOR;


class GameHandle {
public:
	RenderWindow* window = nullptr;
	Mouse* mouse = nullptr;
	Event* evnt = nullptr;
	Font* font = nullptr;
};

class Bar {
public:
	Bar(const size_t& size_x, const size_t& size_y, const double& pos_x, const double& pos_y, GameHandle* gameHandle) {
		_background = new RectangleShape(Vector2f(size_x, size_y));
		_background->setPosition(pos_x, pos_y);
		_indicator = new RectangleShape(Vector2f(size_x, size_y));
		_indicator->setPosition(pos_x, pos_y);
		_gameHandle = gameHandle;
	}
	~Bar() {
		delete _background;
		delete _indicator;
		delete _overlaps;


	}

	void setValue(const double& value) {
		_value = value;
		_indicator->setSize(Vector2f(_background->getSize().x*_value,_background->getSize().y));
	}
	void setColor(Color background_color, Color indicator_color) {
		_background->setFillColor(background_color);
		_indicator->setFillColor(indicator_color);
	}
	void draw() {
		_gameHandle->window->draw(*_background);
		_gameHandle->window->draw(*_indicator);
	}
private:
	double _value = 1;
	GameHandle* _gameHandle = nullptr;
	RectangleShape* _background = nullptr;
	RectangleShape* _indicator = nullptr;
	RectangleShape* _overlaps = nullptr;
};


/*static TextureHandle* _th_skel_idle;*/ /*= new TextureHandle(L"idle_animation", "Texture/Animation/skeleton_idle_animation.png");*/

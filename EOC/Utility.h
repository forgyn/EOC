#pragma once

//INCLUDES
#include <iostream>
#include <random>
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <time.h>



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
#define BAR_WINDOW_PORTION 10.f
#define NAME_LVL_TEXT_PORTION 40.f
#define CURSOR_PORTION 20.f

//ENUMS
enum class Object_Type { Error, Static_Entity, Dynamic_Entity };
enum class Entity_Type { Error, NPC, Player, Enemy, Party };
enum class Direction { LEFT, RIGHT, UP, DOWN, NONE };
enum class GAME_STATE { OK, END, ERROR };
enum class Combat_Action {
	ATTACK,
	ITEM,
	MAGIC,
	FLEE,
	WAITING
};
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







/*static TextureHandle* _th_skel_idle;*/ /*= new TextureHandle(L"idle_animation", "Texture/Animation/skeleton_idle_animation.png");*/

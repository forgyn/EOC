#pragma once

#include "Object.h"
#include "DynamicEntity.h"
#include "Player.h"
#include "Tree.h"
#include "Utility.h"
#include "MapHandle.h"
#include "Combat.h"



class GameHandle;
class MapTile;


class Map{
public:
	//Made from handle
	Map(MapHandle* map_handle, PlayerParty* player_party);
	//Randomly generated
	Map(Map_Type map_type,const int &lvl, PlayerParty* player_party);
	~Map();

	void updateNoControl();
	void updateControl();
	void resizeUpdate();
	void draw();

	void setObjectPosition(Object* obj, const size_t &x,const size_t &y);
	void setViewPositionOnObject(Object* obj);
	void setViewPositionOnTile(const size_t& x, const size_t& y);

	bool moveObject(DynamicEntity* obj,Direction direction);
	bool checkCombat(Object* attacker, Object* defender);
	bool haveFocus() { return _focus; }
	bool playerInCombat() { return _player_in_combat; }

	void removeObject(Object* obj);
	void removeObject(const size_t& id);
	void removeCombat(Combat* combat);
	void removeCombat(const size_t& id);
	
	void generateObjects(Map_Type type, const unsigned& lvl);
	bool gameOver() { return _game_over; }

	View* getView() { return _view; }

private:
#ifdef DEBUG
	CircleShape _mouse_cursor;
#endif // DEBUG
	
	void sortObjects();
	bool objectOnGrid(Object* obj);
	void combatUpdate();
	void combatControlUpdate();
	void resizeView();
	void setDrag(bool dragging) { _dragging = dragging; }
	bool mouseInMap();
	bool viewInBorder();
	void updateMouseThread(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2);
	void updateTilesThread(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2);
	void generateTrees(const size_t& number, TreeType tree_type);
	void generateObjects(const size_t& number, Object* object);
	void updateMouse();
	void updateTiles();
	void updateView();
	void updateRelativeMouse();
	void updateObjects();
	void updatePlayerControl();

	wstring _name;
	const Vector2u _size;
	double _tileSize = 50;
	View* _view = nullptr;
	uint16_t _map_offset = 0;
	Vector2f _mouse_map_pos;
	RectangleShape* _background = nullptr;
	Vector2u _original_resolution;
	Vector2f _original_background_size;
	Map_Type _map_type = Map_Type::ERROR;
	
	bool _player_in_combat = false;
	bool _focus = true;
	bool _object_moved = false;

	vector<Object*> _objects;
	PlayerParty* _player_party = nullptr;

	Clock _dragg_clock;
	Clock _dragg_cooldown;
	bool _dragging = false;
	Vector2i _mouse_offset;
	bool _free_move = false;

	double _ratio = 1;
	double _resize_ratio = 1;
	double _current_zoom = 1;

	bool _zooming = true;
	double _zoom_maximum = 2;
	double _zoom_minimum = 0.2;

	vector<thread> _updateThreadsVec;
	bool _nextTurn = false;
	Clock _FPS_update_limiter;


	int lvl;
	MapTile*** _map = nullptr;
	vector<Combat*> _combat_list;
	Combat* _current_battle = nullptr;

	Keyboard::Key _last_pressed_key = Keyboard::P;
	EntityInfoPanel* _entity_info_panel = nullptr;

	Clock _map_mouse_update_limit_clock;
	const float _map_mouse_update_limit = 30;

	Clock _map_tile_update_limit_clock;
	const float _map_update_limit = 50;

	//random shit
	static uniform_int_distribution<unsigned> _randomMapSize;

	bool _game_over = false;

};


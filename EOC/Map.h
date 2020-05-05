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
	Map(Map_Type map_type,const int &lvl, Player* player);
	~Map();
	void updateMouse();
	void updateTiles();
	void updateView();
	void updateRelativeMouse();
	void updateObjects();
	void updatePlayerControl();
	void setObjectPosition(Object* obj, const size_t &x,const size_t &y);
	void setViewPositionOnObject(Object* obj);
	void setViewPositionOnTile(const size_t& x, const size_t& y);
	void sortObjects();
	bool moveObject(DynamicEntity* obj,Direction direction);
	bool checkCombat(Object* attacker, Object* defender);
	void removeObject(Object* obj);
	void removeObject(const size_t& id);

	void removeCombat(Combat* combat);
	void removeCombat(const size_t& id);


	bool objectOnGrid(Object* obj);
	void combatUpdate();
	void combatControlUpdate();
	void draw();

	void resizeView();
	void setDrag(bool dragging) { _dragging = dragging; }
	bool mouseInMap();
	bool viewInBorder();
	void updateMouseThread(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2);
	void updateTilesThread(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2);
	void resizeUpdate();
	View* getView() { return _view; }
	void generateTrees(const size_t& number, TreeType tree_type);
	bool playerInCombat() { return _player_in_combat; }
	
private:
#ifdef DEBUG
	CircleShape _mouse_cursor;
#endif // DEBUG

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

	bool _object_moved_on_y = false;

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

};


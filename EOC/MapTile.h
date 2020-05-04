#pragma once

#include "Utility.h"
#include "Object.h"

class GameHandle;

class MapTile{
public:
	MapTile(const float& size_x, const float& size_y, const float &pos_x, const float& pos_y,GameHandle* gamehandle);
	MapTile(Vector2f size, Vector2f pos , GameHandle* gamehandle);
	~MapTile();
	
	void updateMouse(const Vector2f &pos_m);
	void update();
	void draw();


	void setColor(const Color &color);
	void setSize(const Vector2f& size);
	void setPos(const Vector2f &pos);
	bool isOccupied() {return _binded_object != nullptr; }
	//void setOccupied(const bool &occupied) { _occupied = occupied; }
	Object* getBindedObject() { return _binded_object; }


	void bindObject(Object* object);
	void unbindObject();

	//DEBUG
	void showInfo();


private:
	RectangleShape* _background = nullptr;
	GameHandle* _gameHandle = nullptr;
	Object* _binded_object = nullptr;
	Color _current_color;
	Color _base_color;
	Vector2f _size;
	Vector2f _pos;
	bool _pressed = false;
	bool _occupied = false;
};


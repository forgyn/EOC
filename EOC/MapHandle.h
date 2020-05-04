#pragma once
#include "Utility.h"
#include "Object.h"
class ObjectDictionary {
public:
	ObjectDictionary(const char &c,Object* obj):character(c),object(obj){}
	const char character;
	Object* object;
};

class TileHandle {
public:
	TileHandle(Object* obj, Vector2u pos);
	~TileHandle() { delete _object; };
	Object* getObject() const { return _object; }
private:
	Object* _object;
};

class MapHandle {
public:
	MapHandle(wstring _name, Vector2u _init_player_pos, Vector2u _map_size, unsigned _lvl = 1);
	~MapHandle() {}
	void addObject(Object* obj, Vector2u pos) { _objects.push_back(new TileHandle(obj, pos)); }
	size_t getSize() const { return _objects.size(); }
	TileHandle* operator[](const size_t& n) {return _objects[n];}
	char** getCharMap() {return _char_map;}
	void addDictionryEntry(const char& character, Object* object) { _dictionary.push_back(ObjectDictionary(character, object)); }
	void setCharMapFromString(const string& str);
	void setObjectsFromCharMap();

	const wstring name = L"Error";
	const Vector2u init_player_pos;
	const Vector2u map_size;

#ifdef DEBUG
	void showCharMap() {
		for (int x = 0; x < map_size.x; x++) {
			for (int y = 0; y < map_size.y; y++) {
				cout << _char_map[x][y];
			}
			cout << endl;
		}
	}
#endif // DEBUG


private:
	vector<TileHandle*> _objects;
	vector<ObjectDictionary> _dictionary;
	char** _char_map;
};


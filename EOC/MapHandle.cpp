#include "MapHandle.h"


TileHandle::TileHandle(Object* obj, Vector2u pos)
{
	_object = obj;
	_object->setGridPosition(pos.x, pos.y);
}

MapHandle::MapHandle(wstring _name, Vector2u _init_player_pos, Vector2u _map_size, unsigned _lvl)
	: name(_name), init_player_pos(_init_player_pos), map_size(_map_size) {
	_char_map = new char* [map_size.x];
	LOOP(map_size.x) {
		_char_map[i] = new char[map_size.y];
	}

	for (int x = 0; x < map_size.x; x++) {
		for (int y = 0; y < map_size.y; y++) {
			_char_map[x][y] = ' ';
		}
	}

}

void MapHandle::setCharMapFromString(const string& str)
{
	if (str.size() == map_size.x * map_size.y + (map_size.y)) {
		int y = 0;
		int x = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '/') {
				x = 0;
				y++;
			}
			else {
				_char_map[x][y] = str[i];
				x++;
			}
		}
	}
	else {
		//cout << "Error: Wrong dimension of string to char map!" << endl;
		throw("Error: Wrong dimension of string to char map!");
	}

}

void MapHandle::setObjectsFromCharMap()
{
	if (_dictionary.size() > 0) {
		for (int x = 0; x < map_size.x; x++) {
			for (int y = 0; y < map_size.y; y++) {
				for (int i = 0; i < _dictionary.size(); i++) {
					if (_char_map[x][y] == _dictionary[i].character) {
						_objects.push_back(new TileHandle(_dictionary[i].object->cloneObj(), Vector2u(x, y)));
					}
				}
			}
		}
	}
	else {
		throw("Dictionary is empty!");
	}

}

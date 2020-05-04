#include "Map.h"
#include "GameSystem.h"
#include "MapTile.h"


Map::Map(MapHandle* map_handle, PlayerParty* player_party, GameHandle* gamehandle)
	: _name(map_handle->name),_size(map_handle->map_size),lvl(lvl),_gameHandle(gamehandle)
{
	_original_resolution = _gameHandle->window->getSize();
	_ratio = static_cast<float>(_gameHandle->window->getSize().x) / static_cast<float>(_gameHandle->window->getSize().y);
	
	_view = new View(Vector2f(_gameHandle->window->getSize().y, _gameHandle->window->getSize().y),Vector2f((_gameHandle->window->getSize().y / 2)/**(1/_ratio)*/, _gameHandle->window->getSize().y / 2));
	_view->setViewport(FloatRect(((static_cast<float>(_gameHandle->window->getSize().x) - static_cast<float>(_gameHandle->window->getSize().y))/2)/ static_cast<float>(_gameHandle->window->getSize().x), 0, 1/_ratio, 1));
	_gameHandle->window->setView(*_view);
	_map_offset = (static_cast<float>(_gameHandle->window->getSize().x) - static_cast<float>(_gameHandle->window->getSize().y)) / 2;
	_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;
	_map = new MapTile**[_size.x];

	if (_size.x <= _size.y) {
		_zoom_maximum = static_cast < double>(2*_size.x*TILE_SIZE) / static_cast<double>(_gameHandle->window->getSize().y);
		_zoom_minimum = static_cast<double>(TILE_SIZE) / static_cast<double>(_gameHandle->window->getSize().y);
	}
	else {
		_zoom_maximum = static_cast<double>(2 * _size.y * TILE_SIZE) / static_cast<double>(_gameHandle->window->getSize().y);
		_zoom_minimum = static_cast<double>(TILE_SIZE) / static_cast<double>(_gameHandle->window->getSize().y);
	}
#ifdef DEBUG
	cout << "Max zoom: " << _zoom_maximum << endl;
	cout << "Minimum zoom: " << _zoom_minimum<< endl;
#endif // DEBUG



	for(int x = 0;x<_size.x;x++){
		_map[x] = new MapTile *[_size.y];
	}

	for (int x = 0; x < _size.x; x++) {
		for (int y = 0; y < _size.y; y++) {
			_map[x][y] = new MapTile(TILE_SIZE,TILE_SIZE,x*TILE_SIZE,y*TILE_SIZE,_gameHandle);
		}
	}

	_background = new RectangleShape(Vector2f(_gameHandle->window->getSize().y, _gameHandle->window->getSize().y));
	_background->setPosition(_map_offset, 0);
	_background->setFillColor(Color::Blue);
	_original_background_size = _background->getSize();

	//_player_party = new PlayerParty(player, _gameHandle);
	_player_party = player_party;
	//----DEPENDS ON TYPE OF MAP----

	setObjectPosition(_player_party, map_handle->init_player_pos.x, map_handle->init_player_pos.y);
	_objects.push_back(_player_party);
	setViewPositionOnObject(_player_party);
	LOOP(map_handle->getSize()) {
		_objects.push_back((*map_handle)[i]->getObject());
		_objects.back()->setId(i+1);
		_map[(*map_handle)[i]->getObject()->getGridPosition().x][(*map_handle)[i]->getObject()->getGridPosition().y]->bindObject((*map_handle)[i]->getObject());
	}
	

	sortObjects();

	//------------------------------

#ifdef DEBUG
	_mouse_cursor.setFillColor(Color::Red);
	_mouse_cursor.setRadius(10);
	_mouse_cursor.setOrigin(_mouse_cursor.getRadius(), _mouse_cursor.getRadius());
	_mouse_cursor.setPosition(_mouse_map_pos);
#endif


}

Map::Map(Map_Type map_type,  const int& lvl, Player* player, GameHandle* gamehandle)
: _size(Vector2f(RANDOM_MAP_SIZE, RANDOM_MAP_SIZE)), lvl(lvl), _gameHandle(gamehandle)
{
	_original_resolution = _gameHandle->window->getSize();
	_ratio = static_cast<float>(_gameHandle->window->getSize().x) / static_cast<float>(_gameHandle->window->getSize().y);

	_view = new View(Vector2f(_gameHandle->window->getSize().y, _gameHandle->window->getSize().y), Vector2f((_gameHandle->window->getSize().y / 2)/**(1/_ratio)*/, _gameHandle->window->getSize().y / 2));
	_view->setViewport(FloatRect(((static_cast<float>(_gameHandle->window->getSize().x) - static_cast<float>(_gameHandle->window->getSize().y)) / 2) / static_cast<float>(_gameHandle->window->getSize().x), 0, 1 / _ratio, 1));
	_gameHandle->window->setView(*_view);
	_map_offset = (static_cast<float>(_gameHandle->window->getSize().x) - static_cast<float>(_gameHandle->window->getSize().y)) / 2;
	_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;
	_map = new MapTile * *[_size.x];

	if (_size.x <= _size.y) {
		_zoom_maximum = _size.x * TILE_SIZE / _gameHandle->window->getSize().y;
		_zoom_minimum = TILE_SIZE / _gameHandle->window->getSize().y;
	}
	else {
		_zoom_maximum = _size.y * TILE_SIZE / _gameHandle->window->getSize().y;
		_zoom_minimum = TILE_SIZE / _gameHandle->window->getSize().y;
	}



	for (int x = 0; x < _size.x; x++) {
		_map[x] = new MapTile * [_size.y];
	}

	for (int x = 0; x < _size.x; x++) {
		for (int y = 0; y < _size.y; y++) {
			_map[x][y] = new MapTile(TILE_SIZE, TILE_SIZE, x * TILE_SIZE, y * TILE_SIZE, _gameHandle);
		}
	}

	_background = new RectangleShape(Vector2f(_gameHandle->window->getSize().y, _gameHandle->window->getSize().y));
	_background->setPosition(_map_offset, 0);
	_background->setFillColor(Color::Blue);
	_original_background_size = _background->getSize();

	//init player party
	_player_party = new PlayerParty(player, _gameHandle);

	//init objects
	//----DEPENDS ON TYPE OF MAP----
	uniform_int_distribution<unsigned> randomPlayerPosition(0,RANDOM_MAP_SIZE-1);
	setObjectPosition(_player_party, randomPlayerPosition(_RANDOM_GENERATOR), randomPlayerPosition(_RANDOM_GENERATOR));

	_objects.push_back(_player_party);
	setViewPositionOnObject(_player_party);

	_map_type = map_type;
	switch (_map_type) {
	case Map_Type::FOREST:
		generateTrees(50,TreeType::Apple);
		break;
	}
	
	
	sortObjects();

	//------------------------------
	//updateRelativeMouse();
#ifdef DEBUG
	_mouse_cursor.setFillColor(Color::Red);
	_mouse_cursor.setRadius(10);
	_mouse_cursor.setOrigin(_mouse_cursor.getRadius(), _mouse_cursor.getRadius());
	_mouse_cursor.setPosition(_mouse_map_pos);
#endif

}

Map::~Map(){
	for (int x = 0; x < _size.x; x++) {
		for (int y = 0; y < _size.y; y++) {
			delete _map[x][y];
			_map[x][y] = nullptr;
		}
		delete[] _map[x];
		_map[x] = nullptr;
	}

	for (int i = 1; i < _objects.size(); i++)delete _objects[i];


	delete[] _map;
	delete _view;
	delete _background;
}

void Map::updateMouse() {
#ifdef DEBUG
	_mouse_cursor.setPosition(_mouse_map_pos);
#endif // DEBUG

	
	//cout << "x: " << _gameHandle->mouse->getPosition(*_gameHandle->window).x << " y: " << _gameHandle->mouse->getPosition(*_gameHandle->window).y << endl;
	const static uint16_t numberOfThreads = 2;
	LOOP(numberOfThreads) {
		_updateThreadsVec.push_back(thread(&Map::updateMouseThread,this, i * (_size.x / numberOfThreads), i * (_size.x / numberOfThreads) + _size.x / numberOfThreads, 0, _size.y));
	}

	LOOP(_updateThreadsVec.size())_updateThreadsVec[i].join();
	_updateThreadsVec.clear();


	//_gameHandle->window->setView(*_view);
#ifdef  DEBUG
	//cout << "GB_x: " << _gameHandle->mouse->getPosition(*_gameHandle->window).x << " GB_y: " << _gameHandle->mouse->getPosition(*_gameHandle->window).y << endl;
#endif //  DEBUG
}

void Map::updateTiles()
{
	const static uint16_t numberOfThreads = 2;
	LOOP(numberOfThreads) {
		_updateThreadsVec.push_back(thread(&Map::updateTilesThread, this, i * (_size.x / numberOfThreads), i * (_size.x / numberOfThreads) + _size.x / numberOfThreads, 0, _size.y));
	}

	LOOP(_updateThreadsVec.size())_updateThreadsVec[i].join();
	_updateThreadsVec.clear();
}

void Map::updateView(){
	if(_zooming)if (_gameHandle->evnt->type == Event::MouseWheelMoved)resizeView();
	if (_free_move) {
		if (mouseInMap()) {
			if (_gameHandle->evnt->type == Event::MouseButtonPressed) {
				if (_dragging != true) {
					_dragg_clock.restart();
					_dragging = true;
					_mouse_offset.x = _view->getCenter().x - _gameHandle->mouse->getPosition(*_gameHandle->window).x;
					_mouse_offset.y = _view->getCenter().y - _gameHandle->mouse->getPosition(*_gameHandle->window).y;
				}
			}
		}

		if (_gameHandle->evnt->type == Event::MouseButtonReleased) {
			_dragging = false;
			_dragg_clock.restart();
		}

		if (_dragging) {
			if (_dragg_clock.getElapsedTime().asMilliseconds() >= 150) {
				if (_dragg_cooldown.getElapsedTime().asMilliseconds() >= 25) {
					//if in map
					if (viewInBorder()) {
						_view->setCenter(_gameHandle->mouse->getPosition(*_gameHandle->window).x + _mouse_offset.x, (_gameHandle->mouse->getPosition(*_gameHandle->window).y + _mouse_offset.y));
						_gameHandle->window->setView(*_view);
					}
					_dragg_cooldown.restart();
				}
			}
		}
	}
}

void Map::updateRelativeMouse(){
	_mouse_map_pos = Vector2f(
		(((_gameHandle->mouse->getPosition(*_gameHandle->window).x) - static_cast<int>(_gameHandle->window->getSize().x / 2)) * _current_zoom  + _view->getCenter().x)
		, (((_gameHandle->mouse->getPosition(*_gameHandle->window).y) - static_cast<int>(_gameHandle->window->getSize().y / 2)) * _current_zoom + _view->getCenter().y));
}

void Map::updateObjects(){
	
	if(!_free_move)setViewPositionOnObject(_player_party);

	if (_object_moved_on_y) { 
		sortObjects(); 
		_object_moved_on_y = false;
	}

	LOOP(_objects.size())_objects[i]->update();

}

void Map::updatePlayerControl(){
	switch (_gameHandle->evnt->type) {
	case Event::KeyPressed:
		_last_pressed_key = _gameHandle->evnt->key.code;
		switch (_gameHandle->evnt->key.code) {
		case Keyboard::W:	moveObject(_player_party, Direction::UP);		break;
		case Keyboard::A:	moveObject(_player_party, Direction::LEFT);		break;
		case Keyboard::S:	moveObject(_player_party, Direction::DOWN);		break;
		case Keyboard::D:	moveObject(_player_party, Direction::RIGHT);	break;
		}
		break;
	case Event::KeyReleased:
		switch (_last_pressed_key) {
		case Keyboard::W:	
		case Keyboard::A:
		case Keyboard::S:
		case Keyboard::D:
			_player_party->stopMoving();
			break;
		}
		break;
	}
}

void Map::setObjectPosition(Object* obj,const size_t& x, const size_t& y){
	if (!_map[x][y]->isOccupied()) { 
		obj->setGridPosition(x, y); 
		//_map[x][y]->setOccupied(true);
		_map[x][y]->bindObject(obj);
	}
}

void Map::setViewPositionOnObject(Object *obj){
	obj->placeView(_view);
}

void Map::setViewPositionOnTile(const size_t& x, const size_t& y)
{
	_view->setCenter(x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE + TILE_SIZE);
}

void Map::sortObjects(){
	//sort(_objects.begin(), _objects.end());
	Object* temp_obj = nullptr;
	size_t sorted = 0;
	while (true) {	
		sorted = 0;
		for (int i = 0; i < _objects.size()-1 ;i++) {
			if (_objects[i]->getGridPosition().y > _objects[i + 1]->getGridPosition().y) {
				temp_obj = _objects[i + 1];
				_objects[i + 1] = _objects[i];
				_objects[i] = temp_obj;
				sorted = 0;
			}
			else {
				sorted++;
			}
		}
		if (sorted >= _objects.size()-1)break;
	}
}

bool Map::moveObject(DynamicEntity* obj, Direction direction){
	//switch (direction) {
	//case Direction::UP:
	//	if (obj->getGridPosition().y > 0) {
	//		if (!_map[obj->getGridPosition().x][obj->getGridPosition().y - 1]->isOccupied()) {
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->unbindObject();
	//			obj->addMove(Direction::UP);
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->bindObject(obj);
	//			_object_moved_on_y = true;
	//			return true;
	//		}
	//		else {
	//			if (checkCombat(obj, _map[obj->getGridPosition().x][obj->getGridPosition().y - 1]->getBindedObject())) {
	//				//COMBAT
	//				_combat_list.push_back(new Combat(obj->convertParty(), _map[obj->getGridPosition().x][obj->getGridPosition().y - 1]->getBindedObject()->convertParty(),_gameHandle));
	//				_combat_list.back()->setId(_combat_list.size());
	//				if (_combat_list.back()->playerInCombat()) { 
	//					_player_in_combat = true;
	//					_current_battle = _combat_list.back(); 
	//				}
	//				return true;
	//			}
	//			else {
	//				//_player_party->stopMoving();
	//				return false;
	//			}
	//		}

	//	}
	//	break;
	//case Direction::LEFT:
	//	if (obj->getGridPosition().x > 0) {
	//		if (!_map[obj->getGridPosition().x - 1][obj->getGridPosition().y]->isOccupied()) {
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->unbindObject();
	//			
	//			obj->addMove(Direction::LEFT);
	//			
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->bindObject(obj);
	//			return true;
	//		}
	//		else {
	//			if (checkCombat(obj, _map[obj->getGridPosition().x - 1][obj->getGridPosition().y]->getBindedObject())) {
	//				//COMBAT
	//				_combat_list.push_back(new Combat(obj->convertParty(), _map[obj->getGridPosition().x - 1][obj->getGridPosition().y]->getBindedObject()->convertParty(), _gameHandle));
	//				_combat_list.back()->setId(_combat_list.size());
	//				if (_combat_list.back()->playerInCombat()) {
	//					_player_in_combat = true;
	//					_current_battle = _combat_list.back();
	//				}
	//			}
	//			else {
	//				//_player_party->stopMoving();
	//				return false;
	//			}
	//		}

	//	}
	//	break;
	//case Direction::DOWN:
	//	if (obj->getGridPosition().y < _size.y - 1) {
	//		if (!_map[obj->getGridPosition().x][obj->getGridPosition().y + 1]->isOccupied()) {
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->unbindObject();
	//			
	//			obj->addMove(Direction::DOWN);
	//			
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->bindObject(obj);
	//			_object_moved_on_y = true;
	//			return true;
	//		}
	//		else {
	//			if (checkCombat(obj, _map[obj->getGridPosition().x][obj->getGridPosition().y + 1]->getBindedObject())) {
	//				//COMBAT
	//				_combat_list.push_back(new Combat(obj->convertParty(), _map[obj->getGridPosition().x ][obj->getGridPosition().y + 1]->getBindedObject()->convertParty(), _gameHandle));
	//				_combat_list.back()->setId(_combat_list.size());
	//				if (_combat_list.back()->playerInCombat()) {
	//					_player_in_combat = true;
	//					_current_battle = _combat_list.back();
	//				}
	//			}
	//			else {
	//				//_player_party->stopMoving();
	//				return false;
	//			}

	//		}
	//	}
	//	break;
	//case Direction::RIGHT:
	//	if (obj->getGridPosition().x < _size.x - 1) {
	//		if (!_map[obj->getGridPosition().x + 1][obj->getGridPosition().y]->isOccupied()) {
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->unbindObject();
	//			obj->addMove(Direction::RIGHT);
	//			_map[obj->getGridPosition().x][obj->getGridPosition().y]->bindObject(obj);
	//			return true;
	//		}
	//		else {
	//			if (checkCombat(obj, _map[obj->getGridPosition().x + 1][obj->getGridPosition().y]->getBindedObject())) {
	//				//COMBAT
	//				_combat_list.push_back(new Combat(obj->convertParty(), _map[obj->getGridPosition().x + 1][obj->getGridPosition().y]->getBindedObject()->convertParty(), _gameHandle));
	//				_combat_list.back()->setId(_combat_list.size());
	//				if (_combat_list.back()->playerInCombat()) {
	//					_player_in_combat = true;
	//					_current_battle = _combat_list.back();
	//				}
	//				return true;
	//			}
	//			else {
	//				//_player_party->stopMoving();
	//				return false;
	//			}
	//		}
	//	}
	//	break;	
	//}

	int x = 0, y = 0;
	switch (direction) {
	case Direction::RIGHT: x = 1; y = 0; break; 
	case Direction::LEFT:x = -1; y = 0; break;
	case Direction::UP:x = 0; y = -1; break;
	case Direction::DOWN:x = 0; y = 1; break;
	}
	//check x
	if (obj->getNextPos().x + x > _size.x - 1 || obj->getNextPos().x + x < 0)return false;
	//check y
	if (obj->getNextPos().y + y > _size.y - 1 || obj->getNextPos().y + y < 0)return false;
	
	
	if (!_map[obj->getNextPos().x + x][obj->getNextPos().y + y]->isOccupied()) {
		_map[obj->getNextPos().x][obj->getNextPos().y]->unbindObject();
		if (obj->addMove(direction)) {
			_map[obj->getNextPos().x + x][obj->getNextPos().y + y]->bindObject(obj);
		}
		else {
			
		}
		
		if(y != 0)_object_moved_on_y = true;
		return true;
	}

	return false;
}

bool Map::checkCombat(Object* attacker,Object* defender){
	if (attacker->getStand() == Entity_Stand::PLAYER) {
		if (defender->getStand() == Entity_Stand::HOSTILE) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (attacker->getStand() == Entity_Stand::HOSTILE) {
		if (defender->getStand() == Entity_Stand::PLAYER || defender->getStand() == Entity_Stand::FRIENDLY) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (attacker->getStand() == Entity_Stand::FRIENDLY) {
		if (defender->getStand() == Entity_Stand::HOSTILE) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}


	
}

void Map::removeObject(Object* obj){
	LOOP(_objects.size()) {
		if (_objects[i]->getId() == obj->getId()) {
			//remove object
			vector<Object*> temp;
			for (int x = 0; x < _objects.size(); x++) {
				if (x != i) {
					temp.push_back(_objects[x]);
				}
			}
			delete _objects[i];
			_objects[i] = nullptr;
			_objects.clear();
			for (int x = 0; x < temp.size(); x++) {
				_objects.push_back(temp[x]);
			}
			temp.clear();
			return;
		}
	}


}

void Map::removeObject(const size_t& id)
{
	//remove object
	vector<Object*> temp;
	for (int x = 0; x < _objects.size(); x++) {
		if (x != id) {
			temp.push_back(_objects[x]);
		}
	}
	delete _objects[id];
	_objects[id] = nullptr;
	_objects.clear();
	for (int x = 0; x < temp.size(); x++) {
		_objects.push_back(temp[x]);
	}
	temp.clear();
}

void Map::removeCombat(Combat* combat){
	LOOP(_combat_list.size()) {
		if (_combat_list[i]->getId() == combat->getId()) {
			//remove combat from list (battle is over)
			vector<Combat*> temp;
			for (int x = 0; x < _combat_list.size(); x++) {
				if (x != i) {
					temp.push_back(_combat_list[x]);
				}
			}
			delete _combat_list[i];
			_combat_list[i] = nullptr;
			_combat_list.clear();
			for (int x = 0; x < temp.size(); x++) {
				_combat_list.push_back(temp[x]);
			}
			temp.clear();
			combat = nullptr;
			return;
		}
	}
}

void Map::removeCombat(const size_t& id)
{
	//remove combat from list (battle is over)
	vector<Combat*> temp;
	for (int x = 0; x < _combat_list.size(); x++) {
		if (x != id) {
			temp.push_back(_combat_list[x]);
		}
	}
	delete _combat_list[id];
	_combat_list[id] = nullptr;
	_combat_list.clear();
	for (int x = 0; x < temp.size(); x++) {
		_combat_list.push_back(temp[x]);
	}
	temp.clear();

}


bool Map::objectOnGrid(Object* obj)
{
	//if(obj->getPosition().x )
	//return false;
	return false;
}

void Map::combatUpdate(){
	LOOP(_combat_list.size())_combat_list[i]->update();

	if (_current_battle!=nullptr) {
		if (!_current_battle->isOn()) {
			removeCombat(_current_battle);
			_current_battle = nullptr;
			delete _current_battle;
			_player_in_combat = false;
		}
	}
	else {

	}
}

void Map::combatControlUpdate()
{
	LOOP(_combat_list.size()) {
		_combat_list[i]->updateControl();
	}

}

void Map::draw(){
	if (!_player_in_combat) {
		_gameHandle->window->setView(_gameHandle->window->getDefaultView());
		_gameHandle->window->draw(*_background);
		_gameHandle->window->setView(*_view);

		for (int x = 0; x < _size.x; x++) {
			for (int y = 0; y < _size.y; y++) {
				_map[x][y]->draw();
			}
		}
		LOOP(_objects.size())_objects[i]->draw();

		//_player_party->draw();
#ifdef DEBUG
		_gameHandle->window->draw(_mouse_cursor);
#endif // DEBUG
	}
	else {
		_gameHandle->window->setView(_gameHandle->window->getDefaultView());
		_current_battle->draw();
		_gameHandle->window->setView(*_view);
	}
	
	
}

void Map::resizeView(){
	if (_gameHandle->evnt->mouseWheel.delta > 0) {	
		if (/*(_view->getSize().y + TILE_SIZE) / _gameHandle->window->getSize().y*/_current_zoom <= _zoom_maximum) {
			_view->setSize(Vector2f(_view->getSize().x + TILE_SIZE * ZOOMING_STRENGH, _view->getSize().y + TILE_SIZE * ZOOMING_STRENGH));
			#ifdef DEBUG
						cout << "Zooming in" << endl;
						cout << "Before: " <<_current_zoom << endl;
			#endif // DEBUG
						_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;
			#ifdef DEBUG
						cout << "After: " << _current_zoom << endl;
			#endif // DEBUG
			_gameHandle->window->setView(*_view);
			if (!viewInBorder()) {
				_view->setSize(Vector2f(_view->getSize().x - TILE_SIZE * _ratio, _view->getSize().y - TILE_SIZE));
				_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;
				_gameHandle->window->setView(*_view);
			}
		}
	}
	if (_gameHandle->evnt->mouseWheel.delta < 0) {
		if (/*(_view->getSize().y - TILE_SIZE) / _gameHandle->window->getSize().y*/_current_zoom >= _zoom_minimum/*(TILE_SIZE*2)/_gameHandle->window->getSize().y*/) {
			_view->setSize(Vector2f(_view->getSize().x - TILE_SIZE*ZOOMING_STRENGH , _view->getSize().y - TILE_SIZE * ZOOMING_STRENGH));
			#ifdef DEBUG
					cout << "Zooming out" << endl;
					cout << "Before: " << _current_zoom << endl;
			#endif // DEBUG
						_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;
			#ifdef DEBUG
					cout << "After: " << _current_zoom << endl;
			#endif // DEBUG
			_gameHandle->window->setView(*_view);
			if (!viewInBorder()) {
				_view->setSize(Vector2f(_view->getSize().x + TILE_SIZE * _ratio, _view->getSize().y + TILE_SIZE));
				_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;
				_gameHandle->window->setView(*_view);
			}
		}
		
	}

}

bool Map::mouseInMap()
{
	if (_gameHandle->mouse->getPosition(*_gameHandle->window).x >= (_gameHandle->window->getSize().x - _gameHandle->window->getSize().y)/2
		&& _gameHandle->mouse->getPosition(*_gameHandle->window).x <= _gameHandle->window->getSize().x - (_gameHandle->window->getSize().x - _gameHandle->window->getSize().y)/2
		&& _gameHandle->mouse->getPosition(*_gameHandle->window).y >= 0 && _gameHandle->mouse->getPosition(*_gameHandle->window).y <= _gameHandle->window->getSize().y
	)return true;
	else return false;
}

bool Map::viewInBorder(){
#ifdef DEBUG
	return true;
#endif // DEBUG

	if (_gameHandle->mouse->getPosition(*_gameHandle->window).x + _mouse_offset.x - _view->getSize().x / 2 >= 0) {
		if (_gameHandle->mouse->getPosition(*_gameHandle->window).y + _mouse_offset.y - _view->getSize().y / 2 >= 0)
			if (static_cast<float>(_gameHandle->mouse->getPosition(*_gameHandle->window).x + _mouse_offset.x) + _view->getSize().x / 2 <= _size.x * TILE_SIZE)
				if (static_cast<float>(_gameHandle->mouse->getPosition(*_gameHandle->window).y + _mouse_offset.y) + _view->getSize().y / 2 <= _size.y * TILE_SIZE)
					return true;
				else {
					_view->setCenter(Vector2f(_view->getCenter().x, (TILE_SIZE * _size.y) - _view->getSize().y / 2));
					_gameHandle->window->setView(*_view);
					return false;
				}
			else {
				_view->setCenter(Vector2f((_size.x * TILE_SIZE) - _view->getSize().x / 2, _view->getCenter().y));
				_gameHandle->window->setView(*_view);
				return false;
			}
		else {
			_view->setCenter(Vector2f(_view->getCenter().x, _view->getSize().y / 2));
			_gameHandle->window->setView(*_view);
			return false;
		}
	}
	else {
		_view->setCenter(Vector2f(_view->getSize().x / 2, _view->getCenter().y));
		_gameHandle->window->setView(*_view);
		return false;
	}


}

void Map::updateMouseThread(const uint16_t &x1,const uint16_t &x2,const uint16_t &y1,const uint16_t &y2)
{
	if (mouseInMap()) {
		for (int x = x1; x < x2; x++) {
			for (int y = y1; y < y2; y++) {
				_map[x][y]->updateMouse(_mouse_map_pos);
			}
		}
	}
}

void Map::updateTilesThread(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2){
	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			_map[x][y]->update();
		}
	}
}

void Map::resizeUpdate()
{
	_ratio = static_cast<double>(_gameHandle->window->getSize().x) / static_cast<double>(_gameHandle->window->getSize().y);
	_resize_ratio = static_cast<double>(_gameHandle->window->getSize().x) / static_cast<double>(_original_resolution.x);
	
	cout << _ratio << endl;
	cout << _resize_ratio << endl;
	cout << _gameHandle->window->getSize().x << endl;
	cout << _gameHandle->window->getSize().y << endl;
	_map_offset = (static_cast<float>(_gameHandle->window->getSize().x) - static_cast<float>(_gameHandle->window->getSize().y)) / 2;
	_current_zoom = _view->getSize().y / _gameHandle->window->getSize().y;

	_view->setViewport(FloatRect(((static_cast<float>(_gameHandle->window->getSize().x) - static_cast<float>(_gameHandle->window->getSize().y)) / 2) / static_cast<float>(_gameHandle->window->getSize().x), 0, 1 / _ratio, 1));

	_background->setPosition(_map_offset/_resize_ratio, 0);
	_background->setSize(Vector2f(_gameHandle->window->getSize().y/ _resize_ratio, _gameHandle->window->getSize().y));
	updateRelativeMouse();
}

void Map::generateTrees(const size_t& number,TreeType tree_type){

	uniform_int_distribution<unsigned> random_pos_x(0, _size.x-1);
	uniform_int_distribution<unsigned> random_pos_y(0, _size.y-1);
	unsigned number_of_set_objects = _objects.size();
	unsigned new_number_of_objects = _objects.size() + number;
	LOOP(number) {
		_objects.push_back(new Tree(L"Tree"+to_wstring(i), tree_type, 100, 150, _gameHandle));
	}



	while (true) {
		Vector2u random_position(random_pos_x(_RANDOM_GENERATOR), random_pos_y(_RANDOM_GENERATOR));
		if (!_map[random_position.x][random_position.y]->isOccupied()) {
			setObjectPosition(_objects[number_of_set_objects++], random_position.x, random_position.y);
			if (number_of_set_objects >= new_number_of_objects)break;
		}
	}
}




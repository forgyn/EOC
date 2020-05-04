#include "DynamicEntity.h"
#include "Party.h"

//DynamicEntity::DynamicEntity(const wstring& name, const size_t& size_x, const size_t& size_y, GameHandle* gameHandle)
//	:Object(name,size_x,size_y,gameHandle)
//{
//	
//}

DynamicEntity::~DynamicEntity()
{
	delete _hp_bar;
	delete _mp_bar;
}

Object* DynamicEntity::cloneObj()
{
	return nullptr;
}

void DynamicEntity::placeView(View* view)
{
	if (_moving) {
		if (_moving_clock.getElapsedTime().asSeconds() >= _time_to_move / 20) {
			Object::placeView(view);
		}
	}
	else Object::placeView(view);
}

void DynamicEntity::update(){
	//Main class update
	Object::update();

	//check next move
	if (_moving_que.size() > 0) {
		_moving = true;
		if (_moving_finished) {
			_moving_direction = _moving_que.front();
			removeLastMove();
			updateMovePos();
			playMoveAnim();
			_moving_finished = false;
		}
	}
	//update if entity stops moving (set idle animation)
	else if (_moving && _moving_finished) {
		if (_currently_playing->getInteruptedAnimation() != nullptr) {
			_currently_playing->stop();
			_currently_playing = _currently_playing->removeInteruptedAnimation();
			_currently_playing->play();
		}
		_moving_direction = Direction::NONE;
		_moving_finished = true;
		_moving = false;
	}
	

	//update moving
	if (_moving_clock.getElapsedTime().asSeconds() >= _time_to_move / 20 ) {
		if (_moving) {
			//y axis
			if (_move_end_point.x == _move_start_point.x) {
				_background->move(0, (_move_end_point.y - _move_start_point.y)/20);
				if (_moving_direction == Direction::UP) {
					if (_background->getPosition().y <= _move_end_point.y) {
							_background->setPosition(_move_end_point);
							_moving_finished = true;
					}
				}
				if (_moving_direction == Direction::DOWN) {
					if (_background->getPosition().y >= _move_end_point.y) {
						_background->setPosition(_move_end_point);
						_moving_finished = true;
					}
				}
			}

			//x axis
			if (_move_end_point.y == _move_start_point.y) {
				_background->move((_move_end_point.x - _move_start_point.x) / 20, 0);
				if (_moving_direction == Direction::LEFT) {
					if (_background->getPosition().x <= _move_end_point.x) {
						_background->setPosition(_move_end_point);
						_moving_finished = true;
					}
				}
				if (_moving_direction == Direction::RIGHT) {
					if (_background->getPosition().x >= _move_end_point.x) {
						_background->setPosition(_move_end_point);
						_moving_finished = true;
					}
				}
			}
		}

		_moving_clock.restart();
	}

	
	
}

void DynamicEntity::updateBars()
{
	if (_show_hp_bar)_hp_bar->setValue(_hp / _max_hp);
	if (_show_mp_bar)_mp_bar->setValue(_mp / _max_mp);
}

void DynamicEntity::draw()
{
	Object::draw();
	if(_show_hp_bar)_hp_bar->draw();
	if (_show_mp_bar)_mp_bar->draw();
}

//void DynamicEntity::move(const float& x, const float& y) {
//	if (!_moving && _moving_finished) {
//		_moving_finished = false;
//		_moving = true;
//		_move_start_point = _background->getPosition();
//		_move_end_point = Vector2f(_background->getPosition().x + (x * TILE_SIZE), _background->getPosition().y + (y * TILE_SIZE));
//		_grid_position.x += x;
//		_grid_position.y += y;	
//		if (x < 0) { 
//			_moving_direction = Direction::LEFT; 	
//			startAnimation(L"moving_left", 0, 0);
//		}
//		if (x > 0) { 
//			_moving_direction = Direction::RIGHT; 
//			startAnimation(L"moving_right", 0, 0);
//		}
//		if (y < 0)_moving_direction = Direction::UP;
//		if (y > 0)_moving_direction = Direction::DOWN;
//		_moving_clock.restart();
//	}
//}
//
//void DynamicEntity::move(const Direction& dir){
//	float x, y;
//	
//	switch (dir) {
//		case Direction::RIGHT	:	x = 1	;		y = 0	;	break;
//		case Direction::LEFT	:	x = -1	;		y = 0	;	break;
//		case Direction::DOWN	:	x = 0	;		y = 1	;	break;
//		case Direction::UP		:	x = 0	;		y = -1	;	break;
//		default: x = 0; y = 0; break;
//	}
//
//	if (!_moving && _moving_finished) {
//		_moving_finished = false;
//		_moving = true;
//		_move_start_point = _background->getPosition();
//		_move_end_point = Vector2f(_background->getPosition().x + (x * TILE_SIZE), _background->getPosition().y + (y * TILE_SIZE));
//		_grid_position.x += x;
//		_grid_position.y += y;
//		if (x < 0) {
//			startAnimation(L"moving_left", 0, 0);
//		}
//		if (x > 0) {
//			startAnimation(L"moving_right", 0, 0);
//		}
//		if (y < 0)_moving_direction = Direction::UP;
//		if (y > 0)_moving_direction = Direction::DOWN;
//		_moving_clock.restart();
//	}
//}

bool DynamicEntity::addMove(const Direction& dir){
	if (_moving_que.size() < 1) {
		_moving_que.push_back(dir);
		return true;
	}
	else {
		return false;
	}
}

void DynamicEntity::addMove(const float& x, const float& y){
	if (x < 0) _moving_que.push_back(Direction::LEFT);
	if (x > 0) _moving_que.push_back(Direction::RIGHT);
	if (y < 0) _moving_que.push_back(Direction::UP);
	if (y > 0) _moving_que.push_back(Direction::DOWN);	
}

void DynamicEntity::removeLastMove(){
	vector<Direction> temp;
	for (int i = 1; i < _moving_que.size();i++)temp.push_back(_moving_que[i]);
	_moving_que.clear();
	LOOP(temp.size())_moving_que.push_back(temp[i]);
}

void DynamicEntity::updateMovePos()
{
	float x, y;
	switch (_moving_direction) {
	case Direction::RIGHT:	x = 1;		y = 0;	break;
	case Direction::LEFT:	x = -1;		y = 0;	break;
	case Direction::DOWN:	x = 0;		y = 1;	break;
	case Direction::UP:		x = 0;		y = -1;	break;
	default: x = 0; y = 0; break;
	}
	_move_start_point = _background->getPosition();
	_move_end_point = Vector2f(_background->getPosition().x + (x * TILE_SIZE), _background->getPosition().y + (y * TILE_SIZE));
	_grid_position.x += x;
	_grid_position.y += y;

}

void DynamicEntity::playMoveAnim()
{
	switch (_moving_direction) {
	case Direction::RIGHT:	startAnimation(L"moving_right",  0,  0);	break;
	case Direction::LEFT:	startAnimation(L"moving_left" ,  0,  0);	break;
	case Direction::DOWN:	startAnimation(L"moving_down" ,  0,  0);	break;
	case Direction::UP:		;	break;
	}
}

Vector2u DynamicEntity::getNextPos(){
	Vector2u nextPos = _grid_position;
	float x = 0, y = 0;
	if(_moving_que.size() > 0 && _moving_que.size() < 1)
		switch (_moving_que[0]) {
		case Direction::RIGHT:	x = 1;		y = 0;	break;
		case Direction::LEFT:	x = -1;		y = 0;	break;
		case Direction::DOWN:	x = 0;		y = 1;	break;
		case Direction::UP:		x = 0;		y = -1;	break;
		default: x = 0; y = 0; break;
	}

	nextPos.x += x;
	nextPos.y += y;
	return nextPos;
}

Party* DynamicEntity::convertParty(){
	Party* newParty = nullptr;
	newParty = new FriendlyParty(this, _gameHandle);
	return newParty;
}

void DynamicEntity::showBars(const bool& hp_bar, const bool& mp_bar)
{
	_show_hp_bar = hp_bar;
	_show_mp_bar = mp_bar;
	if (_show_hp_bar && _show_mp_bar) {
		_hp_bar = new Bar(_background->getSize().x*2, _gameHandle->window->getSize().y / 40, _background->getPosition().x - _background->getSize().x, _background->getPosition().y , _gameHandle);
		_hp_bar->setColor(Color::White, Color::Red);
		_hp_bar->setValue(_hp / _max_hp);
		_mp_bar = new Bar(_background->getSize().x*2, _gameHandle->window->getSize().y / 40, _background->getPosition().x - _background->getSize().x, _background->getPosition().y + static_cast<double>(_gameHandle->window->getSize().y) / 40, _gameHandle);
		_mp_bar->setColor(Color::White, Color(49,76,247));
		_mp_bar->setValue(_mp / _max_mp);
	}

	if (_show_hp_bar && !_show_mp_bar) {
		_hp_bar = new Bar(_background->getSize().x*2, _gameHandle->window->getSize().y / 40, _background->getPosition().x - _background->getSize().x, _background->getPosition().y , _gameHandle);
		_hp_bar->setColor(Color::White, Color::Red);
		_hp_bar->setValue(_hp / _max_hp);
	}

	if (_show_mp_bar && !_show_hp_bar) {
		_mp_bar = new Bar(_background->getSize().x*2, _gameHandle->window->getSize().y / 40, _background->getPosition().x - _background->getSize().x, _background->getPosition().y, _gameHandle);
		_mp_bar->setColor(Color::White, Color(49, 76, 247));
		_mp_bar->setValue(_mp / _max_mp);
	}


}

void DynamicEntity::hideBars()
{
	_show_hp_bar = false;
	_show_mp_bar = false;

	delete _hp_bar; _hp_bar = nullptr;
	delete _mp_bar; _mp_bar = nullptr;
}

void DynamicEntity::stopMoving(){
	_stop_moving = true;
}

void DynamicEntity::initStats(){
	_hp = _max_hp;
	_mp = _max_mp;
	_str = _max_str;
	_end = _max_end;
	_int = _max_int;
	_wis = _max_wis;
	_agi = _max_agi;
	_luc = _max_luc;
}


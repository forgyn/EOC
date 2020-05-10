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
	delete _name_lvl_text;

	//delete _default_attack; _default_attack = nullptr;
	LOOP(_spells.size()) { 
		if (_spells[i] != nullptr) {
			delete _spells[i];
			_spells[i] = nullptr;
		}
		
	}

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
	if (_show_hp_bar)_hp_bar->setValue(_hp.percent());
	if (_show_mp_bar)_mp_bar->setValue(_mp.percent());
}

void DynamicEntity::draw()
{
	Object::draw();
	if(_show_hp_bar)_hp_bar->draw();
	if (_show_mp_bar)_mp_bar->draw();
	if (_show_name_and_lvl)GameHandle::draw(*_name_lvl_text);
	if (_show_cursor)GameHandle::draw(*_cursor);

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

void DynamicEntity::useNormalAttack(Party* caster_party, Party* target_party, DynamicEntity* target)
{
	_default_attack->use(caster_party, this, target_party, target);
}

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
	case Direction::UP:		startAnimation(L"moving_up",	 0,	 0);	break;
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

void DynamicEntity::setInfoString(wstringstream& ss){
	Object::setInfoString(ss);
	ss << ":----------STATS----------::----------DEFENCE----------:" << endl;
	//ss << " HP  : " << setw(4) << _hp.getNow() << setw(2) << "/" << setw(4) << _hp.getMax() << endl;
	//ss << " MP  : " << setw(4) << _mp.getNow() << setw(2) << "/" << setw(4) << _mp.getMax() << endl;
	//ss << " STR : " << setw(4) << _str.getNow() << setw(2) << "/" << setw(4) <<_str.getMax() << endl;
	//ss << " END : " << setw(4) << _end.getNow() << setw(2) << "/" << setw(4) << _end.getMax() << endl;
	//ss << " INT : " << setw(4) << _int.getNow() << setw(2) << "/" << setw(4) << _int.getMax() << endl;
	//ss << " WIS : " << setw(4) << _wis.getNow() << setw(2) << "/" << setw(4) << _wis.getMax() << endl;
	//ss << " AGI : " << setw(4) << _agi.getNow() << setw(2) << "/" << setw(4) << _agi.getMax() << endl;
	//ss << " LUC : " << setw(4) << _luc.getNow() << setw(2) << "/" << setw(4) << _luc.getMax() << endl;
	ss << " HP  : " << setw(5) << _hp.getNow() << setw(2) << "/" << setw(4) << _hp.getMax();
	ss << setw(5) << "            "  << " PHYS DEF : " << setw(8) << _phys_abs_def.getNow() << setw(3) << "|"  << _phys_per_def.getNow() * 100 << "%" << endl;
	ss << " MP  : " << setw(5) << _mp.getNow() << setw(2) << "/" << setw(4) << _mp.getMax();
	ss << setw(5) << "            "  << " FIRE DEF : " << setw(8) << _fire_abs_def.getNow() << setw(3) << "|" << _fire_per_def.getNow() * 100<< "%" << endl;
	ss << " STR : " << setw(5) << _str.getNow() ;
	ss << setw(18)<< "            "  << " FROST DEF: " << setw(8) << _frost_abs_def.getNow() << setw(3) << "|"  << _frost_per_def.getNow() * 100 << "%" << endl;
	ss << " END : " << setw(5) << _end.getNow();
	ss << setw(18) << "            " << " WATER DEF: " << setw(8) << _water_abs_def.getNow() << setw(3) << "|"<< _water_per_def.getNow() * 100 << "%" << endl;
	ss << " INT : " << setw(5) << _int.getNow();
	ss << setw(18) << "            " << " ELEC DEF : " << setw(8) << _electricity_abs_def.getNow() << setw(3) << "|"  << _electricity_per_def.getNow() * 100 << "%" << endl;
	ss << " WIS : " << setw(5) << _wis.getNow();
	ss << setw(18) << "            " << " LIGHT DEF: " << setw(8) << _light_abs_def.getNow() << setw(3) << "|"  << _light_per_def.getNow() * 100 << "%" << endl;
	ss << " AGI : " << setw(5) << _agi.getNow();
	ss << setw(18) << "            " << " DARK DEF : " << setw(8) << _dark_abs_def.getNow() << setw(3) << "|" << _dark_per_def.getNow() * 100 << "%" << endl;
	ss << " LUC : " << setw(5) << _luc.getNow();
	ss << setw(18) << "            " << " DEATH DEF: " << setw(8) << _death_abs_def.getNow() << setw(3) << "|"  << _death_per_def.getNow() * 100 << "%" << endl;
	ss << ":-------------------------::---------------------------:" << endl;
}

void DynamicEntity::setSpellInfoString(wstringstream& ss, unsigned spell_id){
	_spells[spell_id]->setInfoToString(ss, this);
}

Party* DynamicEntity::convertParty(){
	Party* newParty = nullptr;
	newParty = new FriendlyParty(this);
	return newParty;
}

void DynamicEntity::showBars(const bool& hp_bar, const bool& mp_bar){
	_show_hp_bar = hp_bar;
	_show_mp_bar = mp_bar;

	if (_mp.getMax() == 0)_show_mp_bar = false;

	if (_show_hp_bar && _show_mp_bar) {
		_hp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _background->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION*2), _background->getPosition().y + static_cast<double>(GameHandle::getWinSize().y)/100);
		_hp_bar->setColor(Color::Black, Color::Red);
		_hp_bar->setValue(_hp.percent());
		_mp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _background->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _background->getPosition().y + static_cast<double>(GameHandle::getWinSize().y) / 40 + static_cast<double>(GameHandle::getWinSize().y) / 100);
		_mp_bar->setColor(Color::Black, Color(49,76,247));
		_mp_bar->setValue(_mp.percent());
	}

	if (_show_hp_bar && !_show_mp_bar) {
		_hp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _background->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _background->getPosition().y + static_cast<double>(GameHandle::getWinSize().y) / 100);
		_hp_bar->setColor(Color::Black, Color::Red);
		_hp_bar->setValue(_hp.percent());
	}

	if (_show_mp_bar && !_show_hp_bar) {
		_mp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _background->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _background->getPosition().y);
		_mp_bar->setColor(Color::Black, Color(49, 76, 247));
		_mp_bar->setValue(_mp.percent());
	}


}

void DynamicEntity::hideBars()
{
	if (_show_hp_bar) {
		_show_hp_bar = false;
		delete _hp_bar; _hp_bar = nullptr;
	}
	if (_show_mp_bar) {
		_show_mp_bar = false;
		delete _mp_bar; _mp_bar = nullptr;
	}
}

void DynamicEntity::showNameAndLvl(){
	_show_name_and_lvl = true;
	_name_lvl_text = new Text(_name + "\nLVL: " + to_string(_lvl),*FontHandler::getFont(L"arial"),GameHandle::getWinSize().y/NAME_LVL_TEXT_PORTION);
	_name_lvl_text->setPosition(_background->getPosition().x - _background->getGlobalBounds().width / 2, _background->getPosition().y - _background->getGlobalBounds().height - GameHandle::getWinSize().y / (NAME_LVL_TEXT_PORTION / 2.5));
	_name_lvl_text->setFillColor(Color::Black);
	_name_lvl_text->setOutlineThickness(0.3);
}

void DynamicEntity::hideNameAndLvl(){
	_show_name_and_lvl = false;
	delete _name_lvl_text;
	_name_lvl_text = nullptr;
}

void DynamicEntity::showCursor()
{
	_show_cursor = true;
	_cursor = new RectangleShape(Vector2f(GameHandle::getWinSize().x / CURSOR_PORTION, GameHandle::getWinSize().x / CURSOR_PORTION));
	_cursor->setOrigin(_cursor->getSize().x / 2, _cursor->getSize().y);
	_cursor->setPosition(_background->getPosition().x, _background->getPosition().y - _background->getGlobalBounds().height - GameHandle::getWinSize().y/(CURSOR_PORTION/1.2));
	_cursor->setTexture(TextureHandler::getHudTexture(L"entity_cursor"));
}

void DynamicEntity::hideCursor(){
	_show_cursor = false;
	delete _cursor; _cursor = nullptr;
}

float DynamicEntity::dealDmg(const float& dmg, const Element_Type& type){
	double after_reduction_dmg = dmg;
	switch (type) {
	case Element_Type::PHYSICAL:
		after_reduction_dmg -= _phys_abs_def.getNow();
		after_reduction_dmg *= (1 - _phys_per_def.getNow());
		break;
	case Element_Type::FIRE:
		after_reduction_dmg -= _fire_abs_def.getNow();
		after_reduction_dmg *= (1 - _fire_per_def.getNow());
		break;
	case Element_Type::FROST:
		after_reduction_dmg -= _frost_abs_def.getNow();
		after_reduction_dmg *= (1 - _frost_per_def.getNow());
		break;
	case Element_Type::WATER:
		after_reduction_dmg -= _water_abs_def.getNow();
		after_reduction_dmg *= (1 - _water_per_def.getNow());
		break;
	case Element_Type::ELECTRICITY:
		after_reduction_dmg -= _electricity_abs_def.getNow();
		after_reduction_dmg *= (1 - _electricity_per_def.getNow());
		break;
	case Element_Type::LIFE:
		after_reduction_dmg -= _life_abs_def.getNow();
		after_reduction_dmg *= (1 - _life_per_def.getNow());
		break;
	case Element_Type::DEATH:
		after_reduction_dmg -= _death_abs_def.getNow();
		after_reduction_dmg *= (1 - _death_per_def.getNow());
		break;
	case Element_Type::LIGHT:
		after_reduction_dmg -= _light_abs_def.getNow();
		after_reduction_dmg *= (1 - _light_per_def.getNow());
		break;
	case Element_Type::DARK:
		after_reduction_dmg -= _dark_abs_def.getNow();
		after_reduction_dmg *= (1 - _dark_per_def.getNow());
		break;
	}

	after_reduction_dmg -= _pure_abs_def.getNow();
	after_reduction_dmg *= (1 - _pure_per_def.getNow());

	/*if (after_reduction_dmg < 1)after_reduction_dmg = 1;*/
	
	if (!_hp.reduce(after_reduction_dmg)) {
		_base_color = Color(_base_color.r,_base_color.g,_base_color.g,122);
		_background->setFillColor(_base_color);
		_is_dead = true;
	}
	return after_reduction_dmg;
}

void DynamicEntity::removeMp(const float& mp){

}

float DynamicEntity::getPhysDmg(){
	//TO DO
	float dmg = 0;
	dmg = _str.getNow() * 5;
	return dmg;
}

void DynamicEntity::addSpellToPanel(ButtonMenu* menu){
	LOOP(_spells.size()) {
		menu->addButton(_spells[i]->getName(), FontHandler::getFont(L"unispace"));
		//check abs cost of spell
		if(checkSpellAvaible(i))menu->back()->setColor(Color::Green);
		else menu->back()->setColor(Color::Red);
		//if (_spells[i]->getAbsCost().x >= _hp.getNow() || _spells[i]->getAbsCost().y >= _mp.getNow()
		//	|| _spells[i]->getPercentCost().x * _hp.getMax() >= _hp.getNow()|| _spells[i]->getPercentCost().y * _mp.getMax() >= _mp.getNow()) {
		//	
		//}else 
	}
}

bool DynamicEntity::checkSpellAvaible(unsigned spell_id){
	if (_spells[spell_id]->getAbsCost().x + _spells[spell_id]->getPercentCost().x * _hp.getMax() <= _hp.getNow() 
		&& _spells[spell_id]->getAbsCost().y + _spells[spell_id]->getPercentCost().y * _mp.getMax() <= _mp.getNow()) {
		return true;
	}
	else return false;
}

void DynamicEntity::useSpell(unsigned spellId, Party* caster_party, Party* target_party, DynamicEntity* target)
{
	_spells[spellId]->use(caster_party, this, target_party, target);
}

void DynamicEntity::spellCostApply(double abs_hp_cost, double percent_hp_cost, double abs_mp_cost, double percent_mp_cost)
{
	_hp.reduce(abs_hp_cost);
	_hp.reducePercent(percent_hp_cost);
	_mp.reduce(abs_mp_cost);
	_mp.reducePercent(percent_mp_cost);
}

void DynamicEntity::stopMoving(){
	_stop_moving = true;
}

void DynamicEntity::initStats(){
	_hp.refill();
	_mp.refill();
	_str.refill();
	_end.refill();
	_int.refill();
	_wis.refill();
	_agi.refill();
	_luc.refill();
}

void DynamicEntity::resetPtrOnClone(){
	Object::resetPtrOnClone();

	Spell* temp = _default_attack;
	_default_attack = nullptr;
	_default_attack = temp->clone();

	vector<Spell*> temp2;

	LOOP(_spells.size()) {
		temp2.push_back(_spells[i]);
	}
	_spells.clear();

	LOOP(temp2.size()) {
		_spells.push_back(temp2[i]->clone());
	}
	temp2.clear();

}



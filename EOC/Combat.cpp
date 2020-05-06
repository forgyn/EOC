#include "Combat.h"

Combat::Combat(Party* attacker, Party* defender) {
	_party_1 = attacker;
	_party_2 = defender;

	//PLAYER IN COMBAT!!
	if (_party_1->getStand() == Entity_Stand::PLAYER || _party_2->getStand() == Entity_Stand::PLAYER) {
		_player_in_combat = true;

		LOOP(_party_1->getSize()) {
			if ((*_party_1)[i]->getStand() == Entity_Stand::PLAYER) {
				_player = (*_party_1)[i];
				_party_on_turn = _party_1;
				_info_scope = (*_party_1)[i];
				break;
			}
		}
		LOOP(_party_2->getSize()) {
			if ((*_party_2)[i]->getStand() == Entity_Stand::PLAYER) {
				_player = (*_party_2)[i];
				_party_on_turn = _party_2;
				_info_scope = (*_party_2)[i];
				break;
			}
		}

		//_player->startAnimation(L"breathing_animation", 0, 2);

		_menu_background = new RectangleShape(Vector2f(GameHandle::getWinSize().x, GameHandle::getWinSize().y / MENU_SIZE_PORTION));
		_menu_background->setFillColor(Color::Green);

		init();

		_attack_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, 0, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION, L"ATTACK", FontHandler::getFont(L"arial"));
		_magic_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, 0, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, L"MAGIC",  FontHandler::getFont(L"arial"));
		_item_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, GameHandle::getWinSize().x - GameHandle::getWinSize().x / 4, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION , L"ITEM",  FontHandler::getFont(L"arial"));
		_flee_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, GameHandle::getWinSize().x - GameHandle::getWinSize().x / 4, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, L"FLEE",  FontHandler::getFont(L"arial"));
		
		
		_hp_info_bar = new Bar((GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.9, 25, GameHandle::getWinSize().x / 4 + (GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.1/2, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + 50);
		_hp_info_bar->setValue(_info_scope->getHp().x / _info_scope->getHp().y);
		_hp_info_bar->setColor(Color::Yellow, Color::Red);

		_mp_info_bar = new Bar((GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.9, 25, GameHandle::getWinSize().x / 4 + (GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.1/2, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + 75);
		_mp_info_bar->setValue(_info_scope->getMp().x / _info_scope->getMp().y);
		_mp_info_bar->setColor(Color::Yellow, Color::Blue);
		_button_press_checker = new Clock;

		_ai_turn_timer = new Clock();
		_entity_on_turn = (*_party_on_turn)[0];
		for (int i = 0; i < _party_1->getSize() && _entity_on_turn->isDead(); i++) {
			_entity_on_turn = (*_party_on_turn)[i];
		}
	
		_entity_on_turn->showCursor();
	}
	else {
		_auto_combat_clock = new Clock;
		_party_on_turn = _party_1;
		_entity_on_turn = (*_party_on_turn)[_turn];
	}


}

Combat::~Combat()
{
	delete _auto_combat_clock;
	delete _button_press_checker;
	delete _attack_button;
	delete _magic_button;
	delete _item_button;
	delete _flee_button;
	delete _hp_info_bar;
	delete _mp_info_bar;
}

void Combat::updateControl(){
	if (_party_on_turn->isPlayer()) {
		
		_attack_button->update();
		_magic_button->update();
		_item_button->update();
		_flee_button->update();
		

		switch (GameHandle::getEventType()) {
		case Event::KeyPressed:
			updateKeyInput();
			break;
		case Event::MouseMoved:
			updateMouseMove();
			break;
		case Event::MouseButtonPressed:
			updateMousePress();
			break;
		}
	}
}

void Combat::updateKeyInput(){
	switch (GameHandle::getKeyPressed()) {
	case Keyboard::Space:
#ifdef DEBUG
		exitBattle();
#endif // DEBUG
		break;
	case Keyboard::N:
#ifdef DEBUG
		_next_turn = true;
#endif // DEBUG
		break;
	case Keyboard::D:
#ifdef DEBUG
		if (_selected_entity != nullptr) {
			_selected_entity->dealPhysDmg(50);
			_selected_entity->updateBars();
		}
#endif // DEBUG

		break;
	}
}

void Combat::updateMouseMove(){

	//update color if mouse is over entity
	//party1
	LOOP(_party_1->getSize()) {
		if ((*_party_1)[i]->getGlobalBounds().contains(GameHandle::getRelativeMousePos())) {
			(*_party_1)[i]->darken();
		}
		else {
			(*_party_1)[i]->undarken();
		}
	}
	//party2
	LOOP(_party_2->getSize()) {
		if ((*_party_2)[i]->getGlobalBounds().contains(GameHandle::getRelativeMousePos())) {

			(*_party_2)[i]->darken();
		}
		else {
			(*_party_2)[i]->undarken();
		}
	}

}

void Combat::updateMousePress(){
	//left mouse button
	if (GameHandle::getMouseButton() == Mouse::Button::Left) {
		//party1
		LOOP(_party_1->getSize()) {
			if ((*_party_1)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {
				if ((*_party_1)[i] != _selected_entity && _selected_entity != nullptr) {
					_selected_entity->setColor(Color::White);
				}
				_selected_entity = (*_party_1)[i];
			}
		}
		//party2
		LOOP(_party_2->getSize()) {
			if ((*_party_2)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {
				if ((*_party_2)[i] != _selected_entity && _selected_entity != nullptr) {
					_selected_entity->setColor(Color::White);
				}
				_selected_entity = (*_party_2)[i];
			}
		}
	}
	if (GameHandle::getMouseButton() == Mouse::Button::Right) {
		//party1
		LOOP(_party_1->getSize()) {
			if ((*_party_1)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {
#ifdef DEBUG
				(*_party_1)[i]->showInfo();
#endif // DEBUG
			}
		}
		//party2
		LOOP(_party_2->getSize()) {
			if ((*_party_2)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {
#ifdef DEBUG
				(*_party_2)[i]->showInfo();
#endif // DEBUG
			}
		}
	}

}

Party* Combat::getLoser(){
	if (_party_1->isDead()) return _party_1;
	if (_party_2->isDead()) return _party_2;
	//no side is dead
	return nullptr;
}

Party* Combat::getWinner(){
	//flee or something (no side have lost)
	if (!_party_1->isDead() && !_party_2->isDead()) return nullptr;
	if (!_party_1->isDead()) return _party_1;
	if (!_party_2->isDead()) return _party_2;
}

void Combat::updateAction(){
	switch(_action) {
	case Combat_Action::ATTACK:
		if (_selected_entity != nullptr ) {
			if (!checkEntityInParty(_party_on_turn, _selected_entity) && !_selected_entity->isDead()) {
				float deal_dmg = _entity_on_turn->getPhysDmg();
				float received_dmg = _selected_entity->dealPhysDmg(deal_dmg);
#ifdef DEBUG
				wcout << _entity_on_turn->getName() << " attacked " << _selected_entity->getName() << " for " << to_wstring(received_dmg) << " dmg!" << endl;
#endif // DEBUG

				_selected_entity->updateBars();
				_next_turn = true;
			}
		}

		break;
	}
}

void Combat::aiTurn(){
	//random entity selection
	uniform_int_distribution<unsigned> randomEntity(0,opositeParty()->getSize()-1);

	//check if entity is not dead
	//unsigned random_entity = randomEntity(_RANDOM_GENERATOR);
	_selected_entity = (*opositeParty())[randomEntity(_RANDOM_GENERATOR)];
	while (_selected_entity->isDead()) {
		_selected_entity = (*opositeParty())[randomEntity(_RANDOM_GENERATOR)];
	}

	//Attack target
	_action = Combat_Action::ATTACK;



}

bool Combat::checkEntityInParty(Party* party, DynamicEntity* entity){

	LOOP(party->getSize()) if ((*party)[i] == entity)return true;
	return false;
}

Party* Combat::opositeParty(){
	if (checkEntityInParty(_party_1, _entity_on_turn))return _party_2;
	else return _party_1;
}

void Combat::update(){
	if (_player_in_combat) {
		_party_1->combatUpdate();
		_party_2->combatUpdate();
	}
	else {
		if (_auto_combat_clock->getElapsedTime().asSeconds() >= AUTO_COMBAT_SPEED) {
			_auto_combat_clock->restart();
		}
	}
	
	//check hud
	if (_button_press_checker->getElapsedTime().asMilliseconds() >= 50 && _party_on_turn->isPlayer()) {
		if (_attack_button->isPressed(true)) {
			_action = Combat_Action::ATTACK;

			_attack_button->darken();
			_magic_button->undarken();
			_item_button->undarken();
			_flee_button->undarken();

			_selected_entity = nullptr;
		}
		if (_magic_button->isPressed(true)) {
			_action = Combat_Action::MAGIC;

			_attack_button->undarken();
			_magic_button->darken();
			_item_button->undarken();
			_flee_button->undarken();

			_selected_entity = nullptr;
		}
		if (_item_button->isPressed(true)) {
			_action = Combat_Action::ITEM;

			_attack_button->undarken();
			_magic_button->undarken();
			_item_button->darken();
			_flee_button->undarken();

			_selected_entity = nullptr;
		}
		if (_flee_button->isPressed(true)) {
			_action = Combat_Action::FLEE;

			_attack_button->undarken();
			_magic_button->undarken();
			_item_button->undarken();
			_flee_button->darken();

			_selected_entity = nullptr;

			exitBattle();
		}

		
		_button_press_checker->restart();
	}


	//ai turn
	if(_player_in_combat)
	if (!_party_on_turn->isPlayer() && _ai_turn_timer->getElapsedTime().asSeconds() > 1.75) { 
		aiTurn(); 
		_ai_turn_timer->restart();
	}

	//check action
	updateAction();


	//Selected entity is dead (killed)
	if (_selected_entity != nullptr)
	if (_selected_entity->isDead()) {
		//_party_1->removeDead();
		//_party_2->removeDead();
		_selected_entity = nullptr;

		if (_party_1->isDead() || _party_2->isDead()) { 
			exitBattle(); 
			_next_turn = false;
		}
	}

	//check if entity on turn is dead
	if (_entity_on_turn->isDead()) {
		_next_turn = true;
	}


	if (_next_turn) {
		_turn++;

		_attack_button->undarken();
		_magic_button->undarken();
		_item_button->undarken();
		_flee_button->undarken();


		if (_turn > _party_on_turn->getSize() - 1) {
			_turn = 0;
			if (_party_1 != _party_on_turn)_party_on_turn = _party_1;
			else if (_party_2 != _party_on_turn)_party_on_turn = _party_2;
			_ai_turn_timer->restart();
		}
		_entity_on_turn->hideCursor();
		_entity_on_turn = (*_party_on_turn)[_turn];
		//check if entity on turn is not dead
		while (_entity_on_turn->isDead()) {
			_turn++;
			if (_turn > _party_on_turn->getSize() - 1) {
				_turn = 0;
				if (_party_1 != _party_on_turn)_party_on_turn = _party_1;
				else if (_party_2 != _party_on_turn)_party_on_turn = _party_2;
				_ai_turn_timer->restart();
			}

			_entity_on_turn = (*_party_on_turn)[_turn];
		}
		_entity_on_turn->showCursor();

		_next_turn = false;
		_selected_entity = nullptr;
		_action = Combat_Action::WAITING;
	}


}

void Combat::draw()
{
	//_gameHandle->window->setView(*_view);
	//_gameHandle->window->setView(_gameHandle->window->getDefaultView());
	_party_1->drawInCombat();
	_party_2->drawInCombat();


	
	//_gameHandle->window->setView(_gameHandle->window->getDefaultView());
	//_gameHandle->window->setView(_gameHandle->window->getDefaultView());
	GameHandle::draw(*_menu_background);
	_attack_button->draw();
	_magic_button->draw();
	_item_button->draw();
	_flee_button->draw();

	_hp_info_bar->draw();
	_mp_info_bar->draw();

	//_gameHandle->window->setView(*_view);
	
}

void Combat::init()
{
	//LOOP(_party_1->getSize()) {
	//	(*_party_1)[i]->scale(4);
	//}
	
	//_party_1->init(GameHandle::getWinSize().y* -_menu_background->getSize().y - GameHandle::getWinSize().y*0.2);
	_party_1->init(GameHandle::getWinSize().y/1.4);
	//LOOP(_party_2->getSize()) {
	//	(*_party_2)[i]->scale(4);
	//}
	
	//_party_2->init(GameHandle::getWinSize().y * -_menu_background->getSize().y - GameHandle::getWinSize().y * 0.8);
	_party_2->init(GameHandle::getWinSize().y /3);

	_menu_background->setPosition(0, GameHandle::getWinSize().y - _menu_background->getSize().y);

	
	//set hp & mp bars and name/lvl text
	//party1
	LOOP(_party_1->getSize()) {
		(*_party_1)[i]->showNameAndLvl();
		if ((*_party_1)[i]->getMp().y > 0) {
			(*_party_1)[i]->showBars(true, true);
		}
		else (*_party_1)[i]->showBars(true, false);
	}
	//party2
	LOOP(_party_2->getSize()) {
		(*_party_2)[i]->showNameAndLvl();
		if ((*_party_2)[i]->getMp().y > 0) {
			(*_party_2)[i]->showBars(true, true);
		}
		else (*_party_2)[i]->showBars(true, false);
	}
}

void Combat::exitBattle(){
	_battleOn = false;
	//party1
	LOOP(_party_1->getSize()) {
		(*_party_1)[i]->setColor(Color::White);
		(*_party_1)[i]->hideCursor();
	}
	//party2
	LOOP(_party_2->getSize()) {
		(*_party_2)[i]->setColor(Color::White);
		(*_party_2)[i]->hideCursor();
	}
}

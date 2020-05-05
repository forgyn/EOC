#include "Combat.h"

Combat::Combat(Party* party1, Party* party2) {
	_party_1 = party1;
	_party_2 = party2;

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

		_attack_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, 0, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION, L"ATTACK", GameHandle::getWindow(), FontHandler::getFont(L"arial"));
		_magic_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, 0, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, L"MAGIC", GameHandle::getWindow(), FontHandler::getFont(L"arial"));
		_item_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, GameHandle::getWinSize().x - GameHandle::getWinSize().x / 4, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION , L"ITEM", GameHandle::getWindow(), FontHandler::getFont(L"arial"));
		_flee_button = new TextButton(GameHandle::getWinSize().x / 4, (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, GameHandle::getWinSize().x - GameHandle::getWinSize().x / 4, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + (GameHandle::getWinSize().y / MENU_SIZE_PORTION) / 2, L"FLEE", GameHandle::getWindow(), FontHandler::getFont(L"arial"));
		
		
		_hp_info_bar = new Bar((GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.9, 25, GameHandle::getWinSize().x / 4 + (GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.1/2, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + 50);
		_hp_info_bar->setValue(_info_scope->getHp().x / _info_scope->getHp().y);
		_hp_info_bar->setColor(Color::Yellow, Color::Red);

		_mp_info_bar = new Bar((GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.9, 25, GameHandle::getWinSize().x / 4 + (GameHandle::getWinSize().x - GameHandle::getWinSize().x / 2) * 0.1/2, GameHandle::getWinSize().y - GameHandle::getWinSize().y / MENU_SIZE_PORTION + 75);
		_mp_info_bar->setValue(_info_scope->getMp().x / _info_scope->getMp().y);
		_mp_info_bar->setColor(Color::Yellow, Color::Blue);
		_button_press_checker = new Clock;

		

	}
	else {
		_auto_combat_clock = new Clock;
	}

	_entity_on_turn = (*_party_on_turn)[_turn];
	_entity_on_turn->showCursor();
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
	if (_player_in_combat) {
		_attack_button->update(GameHandle::getEvent(), GameHandle::getMouse());
		_magic_button->update(GameHandle::getEvent(), GameHandle::getMouse());
		_item_button->update(GameHandle::getEvent(), GameHandle::getMouse());
		_flee_button->update(GameHandle::getEvent(), GameHandle::getMouse());
		
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

	}
}

void Combat::updateMouseMove()
{
	//update color if mouse is over entity
	//party1
	LOOP(_party_1->getSize()) {
		if ((*_party_1)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {
			(*_party_1)[i]->darken();
		}
		else {
			(*_party_1)[i]->undarken();
		}
	}
	//party2
	LOOP(_party_2->getSize()) {
		if ((*_party_2)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {

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
				/*_selected_entity->undarken();
				_selected_entity->setColor(Color::Cyan);
				_selected_entity->darken();*/
				#ifdef DEBUG
						(*_party_1)[i]->showInfo();
				#endif // DEBUG

			}
		}
		//party2
		LOOP(_party_2->getSize()) {
			if ((*_party_2)[i]->getGlobalBounds().contains(GameHandle::getMousePos())) {
				if ((*_party_2)[i] != _selected_entity && _selected_entity != nullptr) {
					_selected_entity->setColor(Color::White);
				}
				_selected_entity = (*_party_2)[i];
				//_selected_entity->undarken();
				//_selected_entity->setColor(Color::Red);
				//_selected_entity->darken();
				#ifdef DEBUG
					(*_party_2)[i]->showInfo();
				#endif // DEBUG
			}
		}
	}
}

Party* Combat::getLoser(){
	if (_party_1->getSize() == 0) return _party_1;
	if (_party_2->getSize() == 0) return _party_2;
	//no side is dead
	return nullptr;
}

Party* Combat::getWinner(){
	//flee or something (no side have lost)
	if (_party_1->getSize() > 0 && _party_2->getSize() > 0) return nullptr;
	if (_party_1->getSize() > 0) return _party_1; 
	if (_party_2->getSize() > 0) return _party_2;
}

void Combat::updateAction(){
	switch(_action) {
	case Combat_Action::ATTACK:
		if (_selected_entity != nullptr) {
			if (!checkEntityInParty(_party_on_turn, _selected_entity)) {
				_selected_entity->dealPhysDmg(_entity_on_turn->getPhysDmg());
				_selected_entity->updateBars();
				_next_turn = true;
			}
		}

		break;
	}
}

bool Combat::checkEntityInParty(Party* party, DynamicEntity* entity){

	LOOP(party->getSize()) if ((*party)[i] == entity)return true;
	return false;
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

	
	if (_button_press_checker->getElapsedTime().asMilliseconds() >= 50) {
		if (_attack_button->isPressed(true)) {
			cout << "Attack button pressed" << endl;
			_action = Combat_Action::ATTACK;
			_selected_entity = nullptr;
		}
		if (_magic_button->isPressed(true)) {
			cout << "Magic button pressed" << endl;
		}
		if (_item_button->isPressed(true)) {
			cout << "Item button pressed" << endl;
		}
		if (_flee_button->isPressed(true)) {
			cout << "Flee button pressed" << endl;
			exitBattle();
		}
		_button_press_checker->restart();
	}

	//check action
	updateAction();


	//Selected entity is dead
	if (_selected_entity != nullptr)
	if (_selected_entity->isDead()) {
		_party_1->removeDead();
		_party_2->removeDead();
		_selected_entity = nullptr;

		if (_party_1->isDead() || _party_2->isDead()) { 
			exitBattle(); 
			_next_turn = false;
		}


	}


	if (_next_turn) {
		_turn++;
		if (_turn > _party_on_turn->getSize() - 1) {
			_turn = 0;
			if (_party_1 != _party_on_turn)_party_on_turn = _party_1;
			else if (_party_2 != _party_on_turn)_party_on_turn = _party_2;
		}
		_entity_on_turn->hideCursor();
		_entity_on_turn = (*_party_on_turn)[_turn];
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

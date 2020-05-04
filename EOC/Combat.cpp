#include "Combat.h"

Combat::Combat(Party* party1, Party* party2, GameHandle* gameHandle) {
	_gameHandle = gameHandle; 
	_party_1 = party1;
	_party_2 = party2;

	//PLAYER IN COMBAT!!
	if (_party_1->getStand() == Entity_Stand::PLAYER || _party_2->getStand() == Entity_Stand::PLAYER) {
		_player_in_combat = true;

		LOOP(_party_1->getSize()) {
			if ((*_party_1)[i]->getStand() == Entity_Stand::PLAYER) {
				_player = (*_party_1)[i];
				_info_scope = (*_party_1)[i];
				break;
			}
		}
		LOOP(_party_2->getSize()) {
			if ((*_party_2)[i]->getStand() == Entity_Stand::PLAYER) {
				_info_scope = (*_party_2)[i];
				break;
			}
		}

		_player->startAnimation(L"breathing_animation", 0, 2);

		_menu_background = new RectangleShape(Vector2f(_gameHandle->window->getSize().x, _gameHandle->window->getSize().y / MENU_SIZE_PORTION));
		_menu_background->setFillColor(Color::Green);
		init();

		_attack_button = new TextButton(_gameHandle->window->getSize().x / 4, (_gameHandle->window->getSize().y / MENU_SIZE_PORTION) / 2, 0, _gameHandle->window->getSize().y - _gameHandle->window->getSize().y / MENU_SIZE_PORTION, L"ATTACK", _gameHandle->window, _gameHandle->font);
		_magic_button = new TextButton(_gameHandle->window->getSize().x / 4, (_gameHandle->window->getSize().y / MENU_SIZE_PORTION) / 2, 0, _gameHandle->window->getSize().y - _gameHandle->window->getSize().y / MENU_SIZE_PORTION + (_gameHandle->window->getSize().y / MENU_SIZE_PORTION) / 2, L"MAGIC", _gameHandle->window, _gameHandle->font);
		_item_button = new TextButton(_gameHandle->window->getSize().x / 4, (_gameHandle->window->getSize().y / MENU_SIZE_PORTION) / 2, _gameHandle->window->getSize().x - _gameHandle->window->getSize().x / 4, _gameHandle->window->getSize().y - _gameHandle->window->getSize().y / MENU_SIZE_PORTION , L"ITEM", _gameHandle->window, _gameHandle->font);
		_flee_button = new TextButton(_gameHandle->window->getSize().x / 4, (_gameHandle->window->getSize().y / MENU_SIZE_PORTION) / 2, _gameHandle->window->getSize().x - _gameHandle->window->getSize().x / 4, _gameHandle->window->getSize().y - _gameHandle->window->getSize().y / MENU_SIZE_PORTION + (_gameHandle->window->getSize().y / MENU_SIZE_PORTION) / 2, L"FLEE", _gameHandle->window, _gameHandle->font);
		
		
		_hp_info_bar = new Bar((_gameHandle->window->getSize().x - _gameHandle->window->getSize().x / 2) * 0.9, 25, _gameHandle->window->getSize().x / 4 + (_gameHandle->window->getSize().x - _gameHandle->window->getSize().x / 2) * 0.1/2, _gameHandle->window->getSize().y - _gameHandle->window->getSize().y / MENU_SIZE_PORTION + 50 , _gameHandle);
		_hp_info_bar->setValue(_info_scope->getHp().x / _info_scope->getHp().y);
		_hp_info_bar->setColor(Color::Yellow, Color::Red);

		_mp_info_bar = new Bar((_gameHandle->window->getSize().x - _gameHandle->window->getSize().x / 2) * 0.9, 25, _gameHandle->window->getSize().x / 4 + (_gameHandle->window->getSize().x - _gameHandle->window->getSize().x / 2) * 0.1/2, _gameHandle->window->getSize().y - _gameHandle->window->getSize().y / MENU_SIZE_PORTION + 75, _gameHandle);
		_mp_info_bar->setValue(_info_scope->getMp().x / _info_scope->getMp().y);
		_mp_info_bar->setColor(Color::Yellow, Color::Blue);

	}
	
}




//void Bar::setColor(Color background_color, Color indicator_color);

void Combat::updateControl()
{
	if (_player_in_combat) {

		switch (_gameHandle->evnt->type) {
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
	else {

	}
}

void Combat::updateKeyInput()
{
	switch (_gameHandle->evnt->key.code) {

	case Keyboard::Space:
#ifdef DEBUG
		_battleOn = false;
		exitBattle();
#endif // DEBUG
		break;

	}
}

void Combat::updateMouseMove()
{
	//update color if mouse is over entity
	//party1
	LOOP(_party_1->getSize()) {
		if ((*_party_1)[i]->getGlobalBounds().contains(Vector2f(_gameHandle->mouse->getPosition(*_gameHandle->window).x, _gameHandle->mouse->getPosition(*_gameHandle->window).y))) {
			(*_party_1)[i]->darken();
		}
		else {
			(*_party_1)[i]->undarken();
		}
	}
	//party2
	LOOP(_party_2->getSize()) {
		if ((*_party_2)[i]->getGlobalBounds().contains(Vector2f(_gameHandle->mouse->getPosition(*_gameHandle->window).x, _gameHandle->mouse->getPosition(*_gameHandle->window).y))) {

			(*_party_2)[i]->darken();
		}
		else {
			(*_party_2)[i]->undarken();
		}
	}

}

void Combat::updateMousePress(){
	//left mouse button
	if (_gameHandle->evnt->mouseButton.button == Mouse::Button::Left) {
		//party1
		LOOP(_party_1->getSize()) {
			if ((*_party_1)[i]->getGlobalBounds().contains(Vector2f(_gameHandle->mouse->getPosition(*_gameHandle->window).x, _gameHandle->mouse->getPosition(*_gameHandle->window).y))) {
				if ((*_party_1)[i] != _selected_entity && _selected_entity != nullptr) {
					_selected_entity->setColor(Color::White);
				}
				_selected_entity = (*_party_1)[i];
				_selected_entity->undarken();
				_selected_entity->setColor(Color::Cyan);
				_selected_entity->darken();
				#ifdef DEBUG
						(*_party_1)[i]->showInfo();
				#endif // DEBUG

			}
		}
		//party2
		LOOP(_party_2->getSize()) {
			if ((*_party_2)[i]->getGlobalBounds().contains(Vector2f(_gameHandle->mouse->getPosition(*_gameHandle->window).x, _gameHandle->mouse->getPosition(*_gameHandle->window).y))) {
				if ((*_party_2)[i] != _selected_entity && _selected_entity != nullptr) {
					_selected_entity->setColor(Color::White);
				}
				_selected_entity = (*_party_2)[i];
				_selected_entity->undarken();
				_selected_entity->setColor(Color::Red);
				_selected_entity->darken();
				#ifdef DEBUG
					(*_party_2)[i]->showInfo();
				#endif // DEBUG
			}
		}
	}
}

void Combat::update()
{
	if (_player_in_combat) {
		_party_1->combatUpdate();
		_party_2->combatUpdate();

	}
	else {
		if (_auto_combat_clock.getElapsedTime().asSeconds() >= AUTO_COMBAT_SPEED) {
			_auto_combat_clock.restart();
		}
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
	_gameHandle->window->draw(*_menu_background);

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
	_party_1->init(425);
	_party_2->init(200);
	_menu_background->setPosition(0, _gameHandle->window->getSize().y - _menu_background->getSize().y);

	

	//set hp & mp bars
	//party1
	LOOP(_party_1->getSize()) {
		if ((*_party_1)[i]->getMp().y > 0) {
			(*_party_1)[i]->showBars(true, true);
		}
		else (*_party_1)[i]->showBars(true, false);
	}
	//party2
	LOOP(_party_2->getSize()) {
		if ((*_party_2)[i]->getMp().y > 0) {
			(*_party_2)[i]->showBars(true, true);
		}
		else (*_party_2)[i]->showBars(true, false);
	}
}

void Combat::exitBattle(){
	//party1
	LOOP(_party_1->getSize()) {
		(*_party_1)[i]->setColor(Color::White);
	}
	//party2
	LOOP(_party_2->getSize()) {
		(*_party_2)[i]->setColor(Color::White);
	}
}

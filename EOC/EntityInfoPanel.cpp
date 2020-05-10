#include "EntityInfoPanel.h"

EntityInfoPanel::EntityInfoPanel(){
	_background = new RectangleShape(Vector2f(GameHandle::getWinSize().x * 0.8, GameHandle::getWinSize().y * 0.8));
	_background->setPosition(GameHandle::getWinSize().x * 0.1, GameHandle::getWinSize().y * 0.1);
	_background->setFillColor(Color(0, 0, 200));
	_background->setOutlineColor(Color::Black);
	_background->setOutlineThickness(-2.5);
	_titlebar = new RectangleShape(Vector2f(GameHandle::getWinSize().x * 0.8, GameHandle::getWinSize().y * 0.05));
	_titlebar->setPosition(GameHandle::getWinSize().x * 0.1, GameHandle::getWinSize().y * 0.1);
	_titlebar->setFillColor(Color(0, 0, 230));
	_titlebar->setOutlineColor(Color::Black);
	_titlebar->setOutlineThickness(-2.5);

	_close_button = new Button(GameHandle::getWinSize().y * 0.05, GameHandle::getWinSize().y * 0.05, GameHandle::getWinSize().x * 0.9 - GameHandle::getWinSize().y * 0.05, GameHandle::getWinSize().y * 0.1);
	_close_button->setColor(Color::Red);

	float button_size = 0.07;
	_next_party_member = new Button(GameHandle::getWinSize().x * button_size, GameHandle::getWinSize().y * button_size, GameHandle::getWinSize().x*0.5 - 2*GameHandle::getWinSize().x*button_size, GameHandle::getWinSize().y * 0.1 + GameHandle::getWinSize().y * 0.8 - 2*GameHandle::getWinSize().y * button_size);
	_next_party_member->setColor(Color::Green);
	_previous_party_member = new Button(GameHandle::getWinSize().x * button_size, GameHandle::getWinSize().y * button_size, GameHandle::getWinSize().x*0.5 + GameHandle::getWinSize().x*button_size, GameHandle::getWinSize().y * 0.1 + GameHandle::getWinSize().y * 0.8 - 2 * GameHandle::getWinSize().y * button_size);
	_previous_party_member->setColor(Color::Green);


	double space_size = GameHandle::getWinSize().y * 0.035;

	_text.setFont(*FontHandler::getFont(L"basis33"));
	_text.setPosition(GameHandle::getWinSize().x * 0.12, GameHandle::getWinSize().y * 0.12 + GameHandle::getWinSize().y * 0.05);
	_text.setCharacterSize(space_size);
	_text.setFillColor(Color::White);
	_text.setOutlineColor(Color::Black);
	_text.setOutlineThickness(0.2);

	//_text.setString("Name: ");

	/*_stats.setFont(*FontHandler::getFont(L"basis33"));
	_stats.setPosition(GameHandle::getWinSize().x * 0.12, GameHandle::getWinSize().y * 0.12 + GameHandle::getWinSize().y * 0.05 + _name.getGlobalBounds().height + space_size/2);
	_stats.setCharacterSize(space_size);
	_stats.setFillColor(Color::White);
	_stats.setOutlineColor(Color::Black);
	_stats.setOutlineThickness(0.2);

	_stats.setString("Stats: ");*/
}

EntityInfoPanel::~EntityInfoPanel(){
	delete _background;
	delete _titlebar;
	delete _close_button;
	delete _next_party_member;
}

void EntityInfoPanel::update(){
	if (_show) {
		_close_button->update();
		if (_party) {
			_next_party_member->update();
			_previous_party_member->update();

			if (_next_party_member->isPressed(true)) { 
				_entity->nextMemberInfo();
				setText(); 
			}
			if (_previous_party_member->isPressed(true)) {
				_entity->previousMemberInfo();
				setText();
			}
		}
	}
}

void EntityInfoPanel::draw(){
	if (_show) {
		GameHandle::draw(_background);
		GameHandle::draw(_titlebar);
		_close_button->draw();

		//draw entity info
		GameHandle::draw(_text);
		if (_party) {
			_next_party_member->draw();
			_previous_party_member->draw();
		}
	}
}

void EntityInfoPanel::setText(Object* entity){
	_entity = entity;
	if (_entity->getSize() > 1) {
		_party = true;
	}
	else {
		_party = false;
	}


	wstringstream ss;
	ss.setf(ios::dec);
	entity->setInfoString(ss);
	_text.setString(ss.str());


}

void EntityInfoPanel::setText()
{
	if (_entity->getSize() > 1){
		_party = true;
	}
	wstringstream ss;
	_entity->setInfoString(ss);
	ss.setf(ios::dec);
	_text.setString(ss.str());
}

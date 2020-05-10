#include "SpellPanel.h"

SpellPanel::SpellPanel(DynamicEntity* entity)
{
	_entity = entity;
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
	_close_button->setOutlineThiccnes(-2.5);
	_close_button->setOutlineColor(Color::Black);

	_menu = new ButtonMenu(_background->getPosition().x + _titlebar->getSize().y/** 0.1 + GameHandle::getWinSize().y * 0.1*/, GameHandle::getWinSize().y * 0.2, _background->getSize().x * 0.4, (_background->getSize().y-3*_titlebar->getSize().y), GameHandle::getWinSize().y * 0.07);
	_entity->addSpellToPanel(_menu);
	
	double space_size = GameHandle::getWinSize().y * 0.035;
	_text.setFont(*FontHandler::getFont(L"basis33"));
	_text.setPosition(_background->getPosition().x + 2*_titlebar->getSize().y + _background->getSize().x * 0.4, GameHandle::getWinSize().y * 0.15);
	_text.setCharacterSize(space_size);
	_text.setFillColor(Color::White);
	_text.setOutlineColor(Color::Black);
	_text.setOutlineThickness(0.2);



}

SpellPanel::~SpellPanel()
{
	delete _background; _background = nullptr;
	delete  _titlebar; _titlebar = nullptr;
	delete  _close_button; _close_button = nullptr;
	delete  _menu; _menu = nullptr;
}

void SpellPanel::update()
{
	_close_button->update();
	_menu->update();

	if(!_spell_selected)
	LOOP(_menu->getSize()) {
		if ((*_menu)[i]->isPointed()) {
			wstringstream ss;
			ss.setf(ios::dec);
			_entity->setSpellInfoString(ss,i);
			_text.setString(ss.str());
		}
		if ((*_menu)[i]->isPressed(true)) {
			if (_entity->checkSpellAvaible(i)) {
				_spell_selected = true;
				_selected_spell = i;
				break;
			}
		}
	}


}

void SpellPanel::draw()
{
	GameHandle::draw(_background);
	GameHandle::draw(_titlebar);
	_close_button->draw();
	_menu->draw();
	GameHandle::draw(_text);
}

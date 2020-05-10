#pragma once
#include "Utility.h"
#include "Party.h"
#include "ButtonMenu.h"
class SpellPanel{
public:
	SpellPanel(DynamicEntity* entity);
	~SpellPanel();

	void update();
	void draw();
	bool closeButtonPressed() { return _close_button->isPressed(true); }
	bool spellSelected() { return _spell_selected; }
	unsigned selectedSpell() { return _selected_spell; }
private:
	DynamicEntity* _entity = nullptr;

	RectangleShape* _background = nullptr;
	RectangleShape* _titlebar = nullptr;
	Button* _close_button = nullptr;
	ButtonMenu* _menu = nullptr;

	Text _text;
	
	bool _spell_selected = false;
	unsigned _selected_spell = 0;


};


#pragma once
#include "Utility.h"
#include "TextureHandle.h"
#include "Party.h"
#include "StaticEntity.h"
#include "Button.h"





class EntityInfoPanel{
public:
	EntityInfoPanel();
	~EntityInfoPanel();

	void update();
	void draw();
	bool closeButtonPressed() { return _close_button->isPressed(true); }
	void show() { _show = true; }
	void hide() { _show = false; _close_button->reset(); }
	void setText(Object* entity);
	

private:
	void setText();
	Object* _entity = nullptr;
	bool _show = false;
	RectangleShape* _background = nullptr;
	RectangleShape* _titlebar = nullptr;
	Button* _close_button = nullptr;
	bool _party = false;
	Button* _next_party_member = nullptr;
	Button* _previous_party_member = nullptr;
	Text _text;
};


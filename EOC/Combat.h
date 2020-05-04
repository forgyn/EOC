#pragma once
#include "Utility.h"
#include "Party.h"





class Combat{
public:
	Combat(Party* party1,Party* party2,GameHandle* gameHandle);
	~Combat(){}
	bool isOn() { return _battleOn; }
	bool playerInCombat() { return _player_in_combat; }
	//void addEntityToSide1(Object* entity);
	//void addEntityToSide2(Object* entity);
	void updateControl();
	void updateKeyInput();
	void updateMouseMove();
	void updateMousePress();
	void update();
	void draw();
	void init();
	void exitBattle();
	size_t getId() { return _id; }
	void setId(const size_t& id) { _id = id; }
private:
	size_t _id = 0;
	bool _battleOn = true;
	unsigned _turn = 1;
	bool _player_in_combat = false;
	Party* _party_1;
	Party* _party_2;
	DynamicEntity* _selected_entity = nullptr;
	DynamicEntity* _player = nullptr;

	GameHandle* _gameHandle = nullptr;

	Clock _auto_combat_clock;
	RectangleShape* _menu_background = nullptr;
	View* _view = nullptr;

	bool _layer_1_active = true;
	TextButton* _attack_button = nullptr;
	TextButton* _item_button = nullptr;
	TextButton* _magic_button = nullptr;
	//TextButton* _info_button = nullptr;
	TextButton* _flee_button = nullptr;

	DynamicEntity* _info_scope = nullptr;

	Bar* _hp_info_bar = nullptr;
	Bar* _mp_info_bar = nullptr;
};


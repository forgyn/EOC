#pragma once
#include "Utility.h"
#include "Party.h"

class Combat{
public:
	Combat(Party* party1,Party* party2);
	~Combat();
	bool isOn() { return _battleOn; }
	bool playerInCombat() { return _player_in_combat; }
	void updateControl();
	void updateKeyInput();
	void updateMouseMove();
	void updateMousePress();
	Party* getLoser();
	Party* getWinner();
	void updateAction();
	void aiTurn();
	bool checkEntityInParty(Party* party, DynamicEntity* entity);
	Party* opositeParty();
	void update();
	void draw();
	void init();
	void exitBattle();
	size_t getId() { return _id; }
	void setId(const size_t& id) { _id = id; }
private:
	size_t _id = 0;
	bool _battleOn = true;
	unsigned _turn = 0;
	bool _player_in_combat = false;
	Party* _party_1;
	Party* _party_2;

	Party* _party_on_turn = nullptr;
	DynamicEntity* _entity_on_turn = nullptr;
	bool _next_turn = false;


	DynamicEntity* _selected_entity = nullptr;
	DynamicEntity* _player = nullptr;
	DynamicEntity* _info_scope = nullptr;


	Combat_Action _action = Combat_Action::WAITING;


	//CLOCKS
	Clock* _auto_combat_clock = nullptr;
	Clock* _button_press_checker = nullptr;
	Clock* _ai_turn_timer = nullptr;

	View* _view = nullptr;

	///HUD
	RectangleShape* _menu_background = nullptr;
	//BUTTONS
	TextButton* _attack_button = nullptr;
	TextButton* _item_button = nullptr;
	TextButton* _magic_button = nullptr;
	TextButton* _flee_button = nullptr;
	//OTHER
	Bar* _hp_info_bar = nullptr;
	Bar* _mp_info_bar = nullptr;
	
};


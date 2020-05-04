#include "Player.h"
#include "GameSystem.h"


Player::Player(const wstring& name, eoc::Class* player_class, GameHandle* gameHandle)
{
	_name = name;
	_class = player_class;
	_stand = Entity_Stand::PLAYER;
	

	//BASE STATS
	_max_hp  = 100	* _class->hp_m;
	_max_mp  = 100	* _class->mp_m;
	_max_str = 10	* _class->str_m;
	_max_end = 10	* _class->end_m;
	_max_int = 10	* _class->int_m;
	_max_wis = 10	* _class->wis_m;
	_max_agi = 10	* _class->agi_m;
	_max_luc = 10	* _class->luc_m;


	initStats();

	_gameHandle = gameHandle;

	_entity_type = Entity_Type::Player;
	_object_type = Object_Type::Dynamic_Entity;

	setDefaultTexture(TextureHandler::getTexture(L"player_default_texture"));

	_animations.push_back(new Animation(L"blinking_animation",Animation_Type::IDLE, TextureHandler::getTextureHandle(L"player_blinking_animation"), _background, 4, 125, true, true));
	_animations.push_back(new Animation(L"idle_animation", Animation_Type::IDLE, TextureHandler::getTextureHandle(L"player_breathing_animation"), _background, 4, 125, true, true));
	_animations.push_back(new Animation(L"moving_right", Animation_Type::MOVING, TextureHandler::getTextureHandle(L"player_moving_right_animation"), _background, 4, 200, true, false));
	_animations.push_back(new Animation(L"moving_left", Animation_Type::MOVING, TextureHandler::getTextureHandle(L"player_moving_left_animation"), _background, 4, 200, true, false));
	_animations.push_back(new Animation(L"moving_down", Animation_Type::MOVING, TextureHandler::getTextureHandle(L"player_moving_down_animation"), _background, 4, 200, true, false));
	_animations.push_back(new Animation(L"moving_up", Animation_Type::MOVING, TextureHandler::getTextureHandle(L"player_moving_up_animation"), _background, 4, 200, true, false));
	startAnimation(L"idle_animation", 0, 1.25);


	_blink_timer = new Clock();
	_blink_timer->restart();

}

Player::~Player(){
	delete _blink_timer;
}

void Player::update(){
	

	if (_currently_playing == _currently_playing->getInteruptedAnimation()) {
		cout << "wtf" << endl;
	}

	if (_blink_timer->getElapsedTime().asSeconds() >= 3 && !_moving) {
		startAnimation(L"blinking_animation", 1);
		_blink_timer->restart();
	}


	DynamicEntity::update();

	
}

Object* Player::cloneObj()
{
	auto* temp = new  auto(*this);
	temp->resetPtrOnClone();
	return  temp;
}

DynamicEntity* Player::cloneDE()
{
	DynamicEntity* temp = new Player(*this);
	temp->resetPtrOnClone();
	return  temp;
}

void Player::resetPtrOnClone()
{
	Object::resetPtrOnClone();

	_blink_timer = nullptr;
	_blink_timer = new Clock();
	_blink_timer->restart();

}

Party* Player::convertParty(){
	Party* newParty = nullptr;
	newParty = new PlayerParty(this,_gameHandle);
	return newParty;
}



void Player::draw()	{
	DynamicEntity::draw();
}

#include "Player.h"
#include "GameSystem.h"


Player::Player(const wstring& name, Class* player_class)
{
	_name = name;
	_class = player_class;
	_stand = Entity_Stand::PLAYER;
	

	//BASE STATS
	_hp = Stat(100 * _class->hp_m);
	_mp = Stat(100 * _class->mp_m);
	_str = Stat(10 * _class->str_m);
	_end = Stat(10 * _class->end_m);
	_int = Stat(10 * _class->int_m);
	_wis = Stat(10 * _class->wis_m);
	_agi = Stat(10 * _class->agi_m);
	_luc = Stat(10 * _class->luc_m);

	initStats();

	_entity_type = Entity_Type::Player;
	_object_type = Object_Type::Dynamic_Entity;

	setDefaultTexture(TextureHandler::getTexture(L"player_default_texture"));

	_animations.push_back(new Animation(L"blinking_animation",Animation_Type::IDLE, TextureHandler::getAnimationTexture(L"player_blinking_animation"), _background, 4, 125, true, true));
	_animations.push_back(new Animation(L"idle_animation", Animation_Type::IDLE, TextureHandler::getAnimationTexture(L"player_breathing_animation"), _background, 4, 125, true, true));
	_animations.push_back(new Animation(L"moving_right", Animation_Type::MOVING, TextureHandler::getAnimationTexture(L"player_moving_right_animation"), _background, 4, 200, true, false));
	_animations.push_back(new Animation(L"moving_left", Animation_Type::MOVING, TextureHandler::getAnimationTexture(L"player_moving_left_animation"), _background, 4, 200, true, false));
	_animations.push_back(new Animation(L"moving_down", Animation_Type::MOVING, TextureHandler::getAnimationTexture(L"player_moving_down_animation"), _background, 4, 200, true, false));
	_animations.push_back(new Animation(L"moving_up", Animation_Type::MOVING, TextureHandler::getAnimationTexture(L"player_moving_up_animation"), _background, 4, 200, true, false));
	startAnimation(L"idle_animation", 0, 1.25);


	_blink_timer = new Clock();
	_blink_timer->restart();
	_default_attack = new NormalAttack();
	_spells.push_back(_default_attack);
	//_spells.push_back(new SpellInstantDmg(L"Hand of Doom", Element_Type::PURE, 10000, 1, 0, 0, 100, 0, 100, 100, 100, 100, 100, 100, 0, 0, 100, 0));
	_spells.push_back(new SpellInstantDmg(L"Corona cough", Element_Type::DEATH, 10000000,1,0,0,0,0.95));
	_spells.push_back(new SpellInstantDmg(L"Fire Ball", Element_Type::FIRE, 50, 0.95, 5, 0, 0, 0,0,0,5,5));
	//_spells.push_back(new SpellInstantDmg(L"Omae wa mou", Element_Type::PHYSICAL, 0,1,0,0,0,0,1000,1000));
	_spells.push_back(new SpellInstantDmg(L"Small Heal", Element_Type::LIFE,-50,1,5,0,10,0,0,0,-10,-10));
	_spells.push_back(new SpellInstantDmg(L"Holy strike", Element_Type::LIGHT, 50, 1, 5, 0, 0, 0, 0, 0, 10, 10));
	_spells.push_back(new SpellInstantDmg(L"MP surge", Element_Type::PURE, 0, 1, -10, 0, 10));

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
	DynamicEntity::resetPtrOnClone();

	_blink_timer = nullptr;
	_blink_timer = new Clock();
	_blink_timer->restart();

}

Party* Player::convertParty(){
	Party* newParty = nullptr;
	newParty = new PlayerParty(this);
	return newParty;
}



void Player::draw()	{
	DynamicEntity::draw();
}

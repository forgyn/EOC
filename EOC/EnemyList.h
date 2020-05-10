#pragma once

#include "Enemy.h"
#include "ClassList.h"


class Slime : public Enemy {
public:
	Slime(const unsigned& lvl)
	: Enemy(L"Slime", new Monster(), lvl, 100,0,2,2,0,0,3,1)
	{
		setDefaultTexture(TextureHandler::getTexture(L"slime_default_texture"));
		
		//_animations.push_back(new Animation(L"idle_animation",_background, "Texture/Animation/slime_idle_animation.png", 4, 100, true, true));
		_animations.push_back(new Animation(L"idle_animation", Animation_Type::IDLE, TextureHandler::getAnimationTexture(L"slime_idle_animation"),_background, 4, 100, true, true));
		this->startAnimation(L"idle_animation", 0, 0.5);

		//_rectangle_size = _background->getSize();
		//_background->setOrigin(_rectangle_size.x / 2, _rectangle_size.y);
		_default_attack = new NormalAttack();
		_phys_per_def = Stat(0.75);
		_fire_abs_def = Stat(-50);
		_fire_per_def = Stat(-0.8);
	}
	~Slime() {};
	Object* cloneObj() {
		auto* temp = new  auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
	DynamicEntity* cloneDE() {
		auto* temp = new  auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
private:
};

class Skeleton : public Enemy {
public:
	Skeleton(const unsigned &lvl, Class* enemy_class)
	: Enemy(L"Skeleton", enemy_class,lvl, 150, 30, 3, 3, 3, 4, 3, 2) {
		//_rectangle_size.x = 17*2;
		//_rectangle_size.y = 40*2;
		/*this->initBackground();*/

		setDefaultTexture(TextureHandler::getTexture(L"skeleton_default_texture"));

		_animations.push_back(new Animation(L"idle_animation",Animation_Type::IDLE,TextureHandler::getAnimationTexture(L"skeleton_idle_animation") ,_background, 4, 200, true, false));
		_default_attack = new SpellInstantDmg(L"Bonestrousle", Element_Type::PHYSICAL, 25, 0.75, 0, 0, 0, 0, 5, 5,0,0,0,0,0,0,5);
		this->startAnimation(L"idle_animation", 0, 3.5);

		_light_abs_def = Stat(-100);
		_light_per_def = Stat(-2);

		_phys_abs_def = Stat(10);
		_phys_per_def = Stat(0.3);


	}
	~Skeleton() {};
	Object* cloneObj() {
		auto* temp = new  auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
	DynamicEntity* cloneDE() {
		auto* temp = new  auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
private:
};

class Zombie : public Enemy {
public:
	Zombie(const unsigned& lvl, Class* enemy_class)
		: Enemy(L"Zombie", enemy_class,lvl, 300, 0, 10, 4, 0, 0, 4, 3) {
	}
	~Zombie() {};
	Object* cloneObj() {
		auto* temp = new auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
	DynamicEntity* cloneDE() {
		auto* temp = new  auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
private:
};
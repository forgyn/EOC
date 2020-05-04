#pragma once

#include "Enemy.h"
#include "ClassList.h"


class Slime : public Enemy {
public:
	Slime(const unsigned& lvl, GameHandle* gameHandle)
	: Enemy(L"Slime", new Monster(), lvl, 100,0,1,2,0,0,3,1, gameHandle)
	{
		setDefaultTexture(TextureHandler::getTexture(L"slime_default_texture"));
		
		//_animations.push_back(new Animation(L"idle_animation",_background, "Texture/Animation/slime_idle_animation.png", 4, 100, true, true));
		_animations.push_back(new Animation(L"idle_animation", Animation_Type::IDLE, TextureHandler::getTextureHandle(L"slime_idle_animation"),_background, 4, 100, true, true));
		this->startAnimation(L"idle_animation", 0, 0.5);

		//_rectangle_size = _background->getSize();
		//_background->setOrigin(_rectangle_size.x / 2, _rectangle_size.y);
		

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
	Skeleton(const unsigned &lvl, eoc::Class* enemy_class, GameHandle* gameHandle)
	: Enemy(L"Skeleton", enemy_class,lvl, 300, 50, 5, 3, 3, 4, 3, 2, gameHandle) {
		//_rectangle_size.x = 17*2;
		//_rectangle_size.y = 40*2;
		/*this->initBackground();*/

		setDefaultTexture(TextureHandler::getTexture(L"skeleton_default_texture"));

		_animations.push_back(new Animation(L"idle_animation",Animation_Type::IDLE,TextureHandler::getTextureHandle(L"skeleton_idle_animation") ,_background, 4, 200, true, false));

		this->startAnimation(L"idle_animation", 0, 3.5);
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
	Zombie(const unsigned& lvl, eoc::Class* enemy_class, GameHandle* gameHandle)
		: Enemy(L"Zombie", enemy_class,lvl, 450, 0, 10, 4, 0, 0, 4, 3, gameHandle) {
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
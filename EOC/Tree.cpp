#include "Tree.h"

Tree::Tree(TreeType type) {
	_tree_type = type;
	_object_type = Object_Type::Static_Entity;

	setDefaultTexture(TextureHandler::getTexture(L"default_tree_texture"));

	scale(1.5);

	init();
	_stand = Entity_Stand::NEUTRAL;
}


Tree::~Tree()
{
}

Object* Tree::cloneObj()
{
	auto* temp = new  auto(*this);
	temp->resetPtrOnClone();
	return  temp;
}

void Tree::init()
{
	switch (_tree_type) {
	case TreeType::Apple:
		_name = L"Apple Tree";
		_animations.push_back(new Animation(L"idle_animation",Animation_Type::IDLE, TextureHandler::getAnimationTexture(L"default_tree_idle_animation"),_background, 2, 500, true, true));
		this->startAnimation(L"idle_animation", 0, 2);
		break;
	case TreeType::Orange:
		_name = L"Orange Tree";
		break;
	case TreeType::Banana:
		_name = L"Banana Tree";
		break;
	}
}

#include "Tree.h"

Tree::Tree(const wstring& name, TreeType type, const size_t& size_x, const size_t& size_y)
	/*:StaticEntity(name, size_x, size_y, gameHandle)*/ {
	_tree_type = type;
	_object_type = Object_Type::Static_Entity;
	_background = new RectangleShape(Vector2f(size_x, size_y));
	_background->setFillColor(Color::Green);
	_name = name;
	_background->setOrigin(size_x / 2, size_y);
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
		
		_animations.push_back(new Animation(L"idle_animation",Animation_Type::IDLE, TextureHandler::getTextureHandle(L"appletree_idle_animation"),_background, 4, 100, true, true));
		this->startAnimation(L"idle_animation", 0, 2);
		break;
	case TreeType::Orange:

		break;
	case TreeType::Banana:

		break;
	}
}

#include "Object.h"
#include "Party.h"



Object::~Object()
{
	delete _background; _background = nullptr;
	if (!_shared_texture) { delete _default_texture; _default_texture = nullptr; }
	LOOP(_animations.size())delete _animations[i];
}

void Object::update()
{
	if (_currently_playing != nullptr) { 
		_currently_playing->update();
		if (_currently_playing->isOver()) { 	
			if (_currently_playing->getInteruptedAnimation() != nullptr) {
				_currently_playing = _currently_playing->removeInteruptedAnimation();
				_currently_playing->play();
			}
			else {
				equipDefaultTexture();
			}
		}

	}

}

void Object::setGridPosition(const float& x, const float& y)
{
		_grid_position.x = x;
		_grid_position.y = y;
		_background->setPosition(_grid_position.x * TILE_SIZE + TILE_SIZE / 2, _grid_position.y * TILE_SIZE + TILE_SIZE);

}

void Object::setAbsPosition(const float& x, const float& y)
{
	_background->setPosition(x,y);
}

void Object::setDefaultTexture(Texture* texture)
{
	_shared_texture = true;
	_default_texture = texture;
	_rectangle_size = Vector2f(_default_texture->getSize().x, _default_texture->getSize().y);
	_background = new RectangleShape(_rectangle_size);
	_background->setOrigin(_rectangle_size.x / 2, _rectangle_size.y);
	_background->setFillColor(Color::White);
	_background->setTexture(_default_texture);
}

void Object::equipDefaultTexture()
{
	_background->setTexture(_default_texture);
	_background->setTextureRect(IntRect(0,0,_rectangle_size.x,_rectangle_size.y));
}

void Object::draw()
{
	GameHandle::draw(*_background);
}

void Object::scale(const Vector2f& mult)
{
	_background->setScale(mult);
}

void Object::scale(const float& mult)
{
	_background->setScale(mult,mult);
}

void Object::startAnimation(const wstring& animation_name,const size_t &num_of_play, const double& pause_time_s){
	LOOP(_animations.size()) {
		if (_animations[i]->checkName(animation_name)) {
			if (_currently_playing != _animations[i]) {
				if (_currently_playing != nullptr) {
					_animations[i]->addInteruptedAnimation(_currently_playing);
					_currently_playing->pause();
				}
				_currently_playing = _animations[i];
				_currently_playing->startAnimation(num_of_play, pause_time_s);
				return;
			}
		}
	}
}


void Object::copyAnimations(Object* copy, Object* paste)
{
	LOOP(copy->getAnimations()->size()) {
		paste->getAnimations()->push_back((*copy->getAnimations())[i]);
	}
}

void Object::placeView(View* view){
	view->setCenter(Vector2f(_background->getPosition().x, _background->getPosition().y - TILE_SIZE/2));
}

void Object::resetPtrOnClone(){	
	auto* temp_ptr = this->_background;
	this->_background = nullptr;
	this->_background = new RectangleShape(*temp_ptr);
	this->_background->setTexture(temp_ptr->getTexture());

	vector<Animation*> temp;
	size_t id_play_anim = 0;

	LOOP(_animations.size()) {
		temp.push_back(_animations[i]);
		if (_currently_playing != nullptr) {
			if (_currently_playing == _animations[i])id_play_anim = i;
		}
	}

	_animations.clear();
	LOOP(temp.size()) {
		this->_animations.push_back(new Animation(*temp[i]));
		this->_animations.back()->setBackground(this->_background);
		if (_currently_playing != nullptr) {
			if (i == id_play_anim)_currently_playing = _animations.back();
		}
		
	}

	_currently_playing->play();
}

void Object::resetBackground()
{
	_rectangle_size = _background->getSize();
	_background->setOrigin(_rectangle_size.x / 2, _rectangle_size.y);
}

void Object::darken(){
	if (!_darkened) {
		_current_color = Color(_base_color.r / 2, _base_color.g / 2, _base_color.b / 2);
		_background->setFillColor(_current_color);
		_darkened = true;
	}
}

void Object::undarken()
{
	if (_darkened) {
		_current_color = _base_color;
		_background->setFillColor(_current_color);
		_darkened = false;
	}
}


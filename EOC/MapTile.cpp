#include "MapTile.h"
#include "GameSystem.h"

MapTile::MapTile(const float& size_x, const float& size_y, const float& pos_x, const float& pos_y)

{
	_size.x = size_x;
	_size.y = size_y;
	_pos.x = pos_x;
	_pos.y = pos_y;
	_background = new RectangleShape(_size);
	_background->setPosition(_pos);
	//_background->rotate(45);


#ifdef DEBUG
	_base_color = DEBUG_COLOR;
	_current_color = _base_color;
	_background->setFillColor(_current_color);
	_background->setOutlineColor(Color::Black);
	_background->setOutlineThickness(-2);
#else
	_base_color = Color::White;
	_current_color = _base_color;
	_background->setFillColor(_base_color);
#endif // DEBUG
}
MapTile::MapTile(Vector2f size, Vector2f pos){
	_size = size;
	_pos = pos;
	_background = new RectangleShape(_size);
	_background->setPosition(_pos);
	//_background->rotate(45);
#ifdef DEBUG
	_base_color = DEBUG_COLOR;
	_current_color = _base_color;
	_background->setFillColor(_current_color);
	_background->setOutlineColor(Color::Black);
	_background->setOutlineThickness(-2);
#else
	_base_color = Color::White;
	_current_color = _base_color;
	_background->setFillColor(_base_color);
#endif // DEBUG
}

MapTile::~MapTile()
{
	delete _background;
}

bool MapTile::updateMouse(const Vector2f &m_pos){
	//if (GameHandle::getEventType() == Event::MouseButtonReleased && _pressed) {
	//	_pressed = false;
	//	_current_color = _base_color;
	//	return false;
	//}
	
	if (_background->getGlobalBounds().contains(m_pos)) {
		_current_color = Color(_base_color.r / 2, _base_color.g / 2, _base_color.b / 2);
		if(_binded_object!=nullptr)_binded_object->showBars();
		if (GameHandle::getEventType() == Event::MouseButtonPressed) {
			if (GameHandle::getMouseButton() == Mouse::Button::Right) {
				if (_binded_object != nullptr) {
					return true;
				}
			}
		}
	}
	else {
		_current_color = _base_color;
		if (_binded_object != nullptr)_binded_object->hideBars();
	}

	return false;
}

void MapTile::update(){
	_background->setFillColor(_current_color);
}

void MapTile::draw(){
	GameHandle::draw(*_background);
}

void MapTile::setColor(const Color& color)
{
	_base_color = color;
	_current_color = _base_color;
	_background->setFillColor(_current_color);
}

void MapTile::setSize(const Vector2f& size)
{
	_size = size;
	_background->setSize(_size);
}

void MapTile::setPos(const Vector2f& pos)
{
	_pos = pos;
	_background->setPosition(_pos);
}

void MapTile::bindObject(Object* object)
{
	_binded_object = object; 
#ifdef DEBUG
	_base_color = Color::Red;
	_current_color = _base_color;
#endif // DEBUG

}

void MapTile::unbindObject(){
	_binded_object = nullptr; 
#ifdef DEBUG
	_base_color = DEBUG_COLOR;
	_current_color = _base_color;
#endif // DEBUG
}

void MapTile::showInfo()
{
	cout << "HEIGHT " << _background->getGlobalBounds().height << endl;
	cout << "WIDTH  " << _background->getGlobalBounds().width << endl;
	cout << "LEFT   " << _background->getGlobalBounds().left << endl;
	cout << "TOP    " << _background->getGlobalBounds().top << endl;
}

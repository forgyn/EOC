#include "GameHandle.h"

void GameHandle::init(RenderWindow* window){
	_window = window;
	_original_window_size = _window->getSize();
}

Vector2f GameHandle::getRelativeMousePos()
{
	return Vector2f(_mouse->getPosition(*_window).x * (static_cast<float>(_original_window_size.x) / _window->getSize().x), _mouse->getPosition(*_window).y * (static_cast<float>(_original_window_size.y) /_window->getSize().y));
}

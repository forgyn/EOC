#include "GameHandle.h"

void GameHandle::init(RenderWindow* window){
	_window = window;
	_original_window_size = _window->getSize();
}

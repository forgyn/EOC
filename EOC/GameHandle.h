#pragma once
#include "Utility.h"

class GameHandle {
public:
	static void init(RenderWindow* window);
	static Vector2f getMousePos() { return Vector2f(_mouse->getPosition(*_window).x, _mouse->getPosition(*_window).y); }
	static Event::EventType getEventType() { return _event->type; }
	static Keyboard::Key getKeyPressed() { return _event->key.code; }
	static Mouse::Button getMouseButton() { return _event->mouseButton.button; }
	static void setDefaultView() { _window->setView(_window->getDefaultView()); }
	static bool pollEvent() { return _window->pollEvent(*_event); }
	static RenderWindow* getWindow() { return _window; }
	static void setView(View* view) { _window->setView(*view); }
	static Event::MouseWheelEvent getMouseWheel() { return _event->mouseWheel; }
	static Vector2u getWinSize() { return _window->getSize(); }
	static void draw(const Drawable& drawable) { _window->draw(drawable); }
	static Event* getEvent() { return _event; }
	static Mouse* getMouse() { return _mouse; }
private:
	static Mouse* _mouse;
	static Vector2f _resize_ratio;
	static Vector2u _original_window_size;
	static Event* _event;
	static RenderWindow* _window;
};


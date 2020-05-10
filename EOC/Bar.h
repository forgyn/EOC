#pragma once
#include "Utility.h"
#include "GameHandle.h"


class Bar {
public:
	Bar(const size_t& size_x, const size_t& size_y, const double& pos_x, const double& pos_y) {
		_background = new RectangleShape(Vector2f(size_x, size_y));
		_background->setPosition(pos_x, pos_y);
		_indicator = new RectangleShape(Vector2f(size_x, size_y));
		_indicator->setPosition(pos_x, pos_y);
		_indicator->setOutlineThickness(-3);
		_indicator->setOutlineColor(Color::Black);
	}
	~Bar() {
		delete _background;
		delete _indicator;
		delete _overlaps;


	}

	void setValue(const double& value) {
		_value = value;
		_indicator->setSize(Vector2f(_background->getSize().x * _value, _background->getSize().y));
	}
	void setColor(Color background_color, Color indicator_color) {
		_background->setFillColor(background_color);
		_indicator->setFillColor(indicator_color);
	}
	void draw() {
		GameHandle::draw(*_background);
		GameHandle::draw(*_indicator);
	}
private:
	double _value = 1;
	RectangleShape* _background = nullptr;
	RectangleShape* _indicator = nullptr;
	RectangleShape* _overlaps = nullptr;
};


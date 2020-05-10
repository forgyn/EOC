#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slider.h"
#include <string.h>
#include <iostream>
using namespace sf;
using namespace std;
class ButtonMenu{
public:
	ButtonMenu(float pos_x, float pos_y,float size_x,float size_y,float button_height);

	~ButtonMenu();

	void addButton(string text, Font* font);
	void addButton(wstring text, Font* font);
	void update();
	void changeMod(uint8_t mod);

	void setBackgroundColor(const Color& col) { _background.setFillColor(col); }

	void setBackgroundTexture(Texture* texture);
	void addBackgroundTexture(string path);

	void setBackgroundTextureRect(Texture* texture,IntRect rect);
	void addBackgroundTextureRect(string path,IntRect rect);
	
	void setButtonTexture(Texture* texture);
	void addButtonTexture(string path);

	void setButtonTextureRect(Texture* texture, IntRect rect);
	void addButtonTextureRect(string path, IntRect rect);

	void setSliderBackgroundTexture(Texture* texture);
	void addSliderBackgroundTexture(string path);
	
	void setSliderBackgroundTextureRect(Texture* texture, IntRect rect);
	void addSliderBackgroundTextureRect(string path, IntRect rect);

	void setSliderTexture(Texture* texture);
	void addSliderTexture(string path);

	void setSliderTextureRect(Texture* texture, IntRect rect);
	void addSliderTextureRect(string path, IntRect rect);

	void draw();
	TextButton* operator[](size_t n);
	TextButton* back() { return _menu.back(); }
	void reset();
	uint16_t getSize() { return static_cast<uint16_t>(_menu.size()); }
private:
	Vector2f _pos;
	Vector2f _size;
	bool _button_mod = true;
	const float _button_size;
	vector<TextButton*> _menu;
	RectangleShape _background;
	Slider* _slider = nullptr;
	View* _view = nullptr;
	uint8_t _mod = 0;
	int16_t BUTTON_SELECTED = -1;
	Clock* _button_clock;
	float _actual_size = 0;


	Texture* _background_texture = nullptr;
	bool _added_background_texture = false;
	bool _loaded_background_texture = false;

	Texture* _button_texture = nullptr;
	bool _added_button_texture = false;
	bool _loaded_button_texture = false;
	bool _rect_button_texture = false;
	IntRect _button_rect;


	Texture* _slider_background_texture = nullptr;
	bool _added_slider_background_texture = false;
	bool _loaded_slider_background_texture = false;

	Texture* _slider_texture = nullptr;
	bool _added_slider_texture = false;
	bool _loaded_slider_texture = false;
};

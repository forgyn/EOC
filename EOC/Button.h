#pragma once

#include "Input.h"

#define TEXT_RATIO 0.5f
#define BASIC_COLOR Color::Yellow

class Button : public InputElement {
public:
	Button(float size_x, float size_y, float pos_x, float pos_y);
	Button(Vector2f size, Vector2f pos);
	~Button();
	void draw();
	virtual void update();
	bool isPointed();
	void setColor(const Color &color, const Color& color2 = Color::Transparent);
	void setBackgroundTexture(string path);
	void setBackgroundTexture(Texture* texture);
	void setBackgroundRectTexture(string path, IntRect rect);
	void setBackgroundRectTexture(Texture* texture, IntRect rect);
	void setSpecialTexture(Texture* texture) {}
	void setSpecialTexture(string path) {}
	void setSpecialRectTexture(Texture* texture, IntRect rect) {}
	void setSpecialRectTexture(string path, IntRect rect) {}
	void setOutlineThiccnes(const float& thicc) { _backgroud->setOutlineThickness(thicc); }
	void setOutlineColor(Color col) { _backgroud->setOutlineColor(col); }
	bool isPressed(bool unpress = false);
	void removeTexture(Color color = Color::Yellow);
	Vector2f getPos() { return Vector2f(_position.x-_backgroud->getOrigin().x,_position.y - _backgroud->getOrigin().y); }
	void reset();
	
	void changePos(Vector2f pos);
	void changeSize(Vector2f size);
	void changeMod(uint8_t mod);

	void darken() { _darkened = true; _backgroud->setFillColor(Color(_basicColor.r * 0.5f, _basicColor.g * 0.5f, _basicColor.b * 0.5f)); }
	void undarken(){ _darkened = false; _backgroud->setFillColor(_basicColor); }
protected:
	Vector2f _size;
	Vector2f _position;
	Vector2u _defaultWindowSize;
	uint8_t _mod = 0;
	RectangleShape* _backgroud = nullptr;
	Color _basicColor;
	Texture* _texture = nullptr;
	bool loadedTexture = false;
	bool PRESSED = false;
	bool POINTED = false;
	bool HOLDING = false;
	bool _darkened = false;
};

class DraggableButton : public Button {
public:
	DraggableButton(float size_x, float size_y, float pos_x, float pos_y);
	DraggableButton(Vector2f size, Vector2f pos);
	void update();
	bool FOLLOWING = false;
	void changeMoveMod(unsigned move_mod) { _move_mod = move_mod; }
	void reset();
	Vector2f getLeftUpCorner() { return Vector2f(_position.x,_position.y); }
	Vector2f getRightDownCorner() { return Vector2f(_position.x + _size.x, _position.y + _size.y); }
	void setLimit(float min_x,float max_x, float min_y,float max_y);
	
private:
	unsigned _move_mod = 0;
	Vector2f _limit_max;
	Vector2f _limit_min;
};

class TextButton : public Button {
public:
	//TextButton(float size_x, float size_y, float pos_x, float pos_y, const string& text, RenderWindow* window);
	TextButton(float size_x, float size_y, float pos_x, float pos_y, const wstring& text, Font* font);
	TextButton(float size_x, float size_y, float pos_x, float pos_y, const string& text, Font* font);
	~TextButton();
	void draw();
	//void update(Event* _event, Mouse* _mouse);
	void changeStyle(Uint32 style);
	void setFont(Font* font);
	void setFont(string path);
	void setColor(Color bck_col,Color txt_col = Color::Black);
	void setString(wstring str);
	void setString(string str) { _text->setString(str); }
	void changePos(Vector2f pos);
	void setTextRatio(float ratio);
	void getDebugInfo();
private:
	Text *_text = nullptr;
	bool loadedFont = false;
	float _text_ratio = 1.f;
	Font* _font = nullptr;
	Color _basic_text_color;
};
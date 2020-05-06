#pragma once
#include "Utility.h"
#include "Button.h"
#include "TextureHandle.h"
#include "FontHandle.h"
#include "Animation.h"
#include "GameHandle.h"
class Party;


class Object{
public:
	virtual ~Object();
	virtual  Object* cloneObj() = 0;
	//virtual  Object* cloneObj() = 0;
	//virtual const  Object* cloneObj() = 0;
	virtual void update();
	virtual void setGridPosition(const float &x,const float &y);
	virtual void setAbsPosition(const float& x, const float& y);
	virtual void setDefaultTexture(Texture* texture);
	virtual void equipDefaultTexture();



	virtual void draw();
	virtual void scale(const Vector2f& mult);
	virtual void scale(const float& mult);
	virtual void setId(const unsigned& id) { _id = id; }
	virtual Party* convertParty() = 0;
	virtual unsigned getId() { return _id; }
	virtual Vector2f getRecSize() { return _background->getSize(); }
	virtual void setColor(const Color& color) { _base_color = color; _current_color = _base_color; _background->setFillColor(_current_color); }
	virtual void startAnimation(const wstring& animation_name, const size_t& num_of_play = 0,const double &pause_time_s = 0);
	virtual void copyAnimations(Object* copy, Object* paste);
	virtual void placeView(View* view);
	virtual Entity_Stand getStand() { return _stand; };
	virtual vector<Animation*>* getAnimations() { return &_animations; }
	virtual Vector2f getPosition() { return _background->getPosition(); }
	virtual Vector2u getGridPosition() { return _grid_position; }
	virtual FloatRect getGlobalBounds() { return _background->getGlobalBounds(); }
	virtual void resetPtrOnClone();
	virtual void resetBackground();
	virtual void darken();
	virtual void undarken();

	virtual wstring getName() { return _name; }

#ifdef DEBUG
	virtual void showInfo() {
		wcout << "Name: " << _name << endl;
		cout << "Id: " << _id << endl;
	};
#endif // DEBUG

	


protected:

	wstring _name;
	Object_Type _object_type = Object_Type::Error;
	RectangleShape* _background = nullptr;
	Texture* _default_texture = nullptr;
	Vector2u _grid_position;
	bool _shared_texture = false;

	Color _base_color = Color::White;
	Color _current_color = Color::White;
	bool _darkened = false;

	Entity_Stand _stand = Entity_Stand::ERROR;
	unsigned _id = 0;
	vector<Animation*> _animations;
	vector<Animation*> _animation_que;
	Animation* _currently_playing = nullptr;
	Animation* _idle_animation = nullptr;

	Vector2f _rectangle_size = Vector2f(50,50);
	
#ifdef DEBUG
	CircleShape* _origin_locator = nullptr;
#endif // DEBUG


private:
	
	
};


#pragma once
#include "Utility.h"
#include "TextureHandle.h"

class Animation {
public:
	//Animation(const wstring& animation_name, TextureHandle* tex_handle, RectangleShape* animated_background, const size_t& frames, const float& frame_duration_ms, bool repeating, bool circle_repeating);
	Animation(const wstring& animation_name, Animation_Type anim_type, Texture* anim_frames, RectangleShape* animated_background, const size_t& frames, const float& frame_duration_ms, bool repeating, bool circle_repeating);
	
	Animation(const Animation& anim);
	~Animation();
	void update();
	void startAnimation(const size_t& num_of_play, const double& pause_time_s = 0);
	void play();
	void pause();
	void stop();
	bool checkName(const wstring& name) { return name == _name; }
	void addInteruptedAnimation(Animation* anim);
	Animation* removeInteruptedAnimation();
	Animation* getInteruptedAnimation() const;
	Animation_Type getType() { return _animation_type; }
	//Animation* getInteruptedAnimation() { return _interupted_animation; }
	bool isOver();
	bool endOfCycle() { return _end_of_cycle; }
	void setBackground(RectangleShape* background) {
		_animated_background = background;
		_animated_background->setFillColor(Color::White);
		_animated_background->setTexture(_animation_frames);
		_animated_background->setTextureRect(IntRect(0, 0, _frame_size.x, _frame_size.y));
	}
	void reset();
	wstring getName() { return _name; }

private:
	Animation_Type _animation_type = Animation_Type::ERROR;
	wstring _name = L"Error";
	RectangleShape* _animated_background = nullptr;
	bool _animation_playing = false;
	IntRect _current_rec;
	Animation* _interupted_animation = nullptr;
	vector<Animation*> _interupted_animations;
	bool _repeating = false;
	bool _circle_repeating = false;

	bool _reversing = false;
	bool _is_over = false;
	bool _end_of_cycle = false;
	double _pause_time_s = 0;
	bool _pausing = false;

	uint8_t _current_frame = 0;
	uint8_t _frames = 0;
	uint8_t _number_of_times_played = 0;
	uint8_t _play_for = 1;
	bool _play_forever = false;

	float _frame_duration_ms = 0;
	Vector2u _frame_size;


	Clock* _animation_clock = nullptr;
	Clock* _pause_clock = nullptr;


	Texture* _animation_frames = nullptr;

	bool _shared_texture = false;
};


#include "Animation.h"




//Animation::Animation(const wstring& animation_name, TextureHandle* tex_handle, RectangleShape* animated_background, const size_t& frames, const float& frame_duration_ms, bool repeating, bool circle_repeating)
//{
//	_name = animation_name;
//
//	_shared_texture = true;
//	_animation_frames = tex_handle->getTexture();
//
//	_frame_duration_ms = frame_duration_ms;
//	_frames = frames;
//	_frame_size.x = _animation_frames->getSize().x / _frames;
//	_frame_size.y = _animation_frames->getSize().y;
//	_animation_clock = new Clock;
//	_repeating = repeating;
//	_circle_repeating = circle_repeating;
//
//
//
//	_animated_background = animated_background;
//
//}

Animation::Animation(const wstring& animation_name, Animation_Type anim_type, TextureHandle* tex_handle, RectangleShape* animated_background, const size_t& frames, const float& frame_duration_ms, bool repeating, bool circle_repeating)
{
	_name = animation_name;
	_animation_type = anim_type;

	_shared_texture = true;
	_animation_frames = tex_handle->getTexture();

	_frame_duration_ms = frame_duration_ms;
	_frames = frames;
	_frame_size.x = _animation_frames->getSize().x / _frames;
	_frame_size.y = _animation_frames->getSize().y;
	_animation_clock = new Clock;
	_repeating = repeating;
	_circle_repeating = circle_repeating;



	_animated_background = animated_background;
}

Animation::Animation(const Animation& anim)
{
	*this = anim;
	if (!_shared_texture) {
		this->_animation_frames = nullptr;
		this->_animation_frames = new Texture(*anim._animation_frames);
	}
	else {
		this->_animation_frames = anim._animation_frames;
	}
	this->_animation_clock = nullptr;
	this->_animation_clock = new Clock();
	this->_pause_clock = nullptr;
	if (anim._pause_clock != nullptr) {
		this->_pause_clock = new Clock();
	}


}

Animation::~Animation() {
	if (!_shared_texture)delete _animation_frames;
	delete _animation_clock;
	if (_pausing)delete _pause_clock;
}

void Animation::update() {
	if (_animation_playing) {
		if (!_pausing && _pause_clock == nullptr) {
			if (_animation_clock->getElapsedTime().asMilliseconds() >= _frame_duration_ms) {
				_end_of_cycle = false;
				if (_play_forever) {
					_animated_background->setTextureRect(IntRect(_current_frame * _frame_size.x, 0, _frame_size.x, _frame_size.y));

					if (_reversing)_current_frame--;
					else _current_frame++;



					if (_current_frame >= _frames) {
						if (!_circle_repeating && !_play_forever)_number_of_times_played++;
						if (_repeating) {
							if (_circle_repeating)_reversing = true;
							else {
								_current_frame = 0;
								_number_of_times_played++;
							}
						}

						if (!_circle_repeating)_end_of_cycle = true;
					}
				}
				else {
					

					if (_reversing)_current_frame--;
					else _current_frame++;

					_animated_background->setTextureRect(IntRect(_current_frame * _frame_size.x, 0, _frame_size.x, _frame_size.y));

					if (_current_frame >= _frames-1) {
						if (!_circle_repeating && !_play_forever)_number_of_times_played++;
						if (_repeating) {
							if (_circle_repeating)_reversing = true;
							else {
								_current_frame = 0;
								_number_of_times_played++;
							}
						}

						if (!_circle_repeating)_end_of_cycle = true;
					}
				}

				if (_current_frame == 0 && _reversing) {
					_reversing = false;
					_end_of_cycle = true;
					if (!_play_forever) {
						_number_of_times_played++;
					}
				}

				if (_number_of_times_played >= _play_for && !_play_forever) {
					_animation_playing = false;
					_is_over = true;
					_number_of_times_played = 0;
				}

				_animation_clock->restart();
			}
		}
		else if (_pause_clock->getElapsedTime().asSeconds() >= _pause_time_s) {
			if (_animation_clock->getElapsedTime().asMilliseconds() >= _frame_duration_ms) {
				_end_of_cycle = false;
				if (_reversing)_current_frame--;
				else _current_frame++;

				if (_current_frame == _frames) {
					if (!_circle_repeating && !_play_forever)_number_of_times_played++;
					if (_repeating) {
						if (_circle_repeating) {
							_current_frame -= 2;
							_reversing = true;
						}
						else {
							_current_frame = 0;
							_pause_clock->restart();
						}
					}
					if (!_circle_repeating)_end_of_cycle = true;

				}

				if (_current_frame == 0 && _reversing) {
					_end_of_cycle = true;
					_reversing = false;
					_pause_clock->restart();
					if (!_play_forever)_number_of_times_played++;
				}

				if (_number_of_times_played >= _play_for && !_play_forever) {
					_animation_playing = false;
					_is_over = true;
					_number_of_times_played = 0;
				}

				_animated_background->setTextureRect(IntRect(_current_frame * _frame_size.x, 0, _frame_size.x, _frame_size.y));
				_animation_clock->restart();
			}
		}
	}
}

void Animation::startAnimation(const size_t& num_of_play, const double& pause_time_s)
{
	_is_over = false;
	_end_of_cycle = false;
	_animated_background->setTexture(_animation_frames);
	_animated_background->setTextureRect(IntRect(0, 0, _frame_size.x, _frame_size.y));
	_current_frame = 0;
	_animation_playing = true;

	if (num_of_play == 0) {
		_play_forever = true;
	}
	else {
		_play_for = num_of_play;

	}

	if (pause_time_s > 0)
	{
		_pause_clock = new Clock;
		_pause_time_s = pause_time_s;
		_pausing = true;
	}
}

void Animation::play() {
	_animation_playing = true;
	_animated_background->setTexture(_animation_frames);
	_animated_background->setTextureRect(IntRect(_current_frame * _frame_size.x, 0, _frame_size.x, _frame_size.y));
}

void Animation::pause() {
	_animation_playing = false;
}

void Animation::stop() {
	_animation_playing = false;
	_current_frame = 0;
}

void Animation::addInteruptedAnimation(Animation* anim){
	//if (anim != this) {
	//	//_interupted_animation = anim->getInteruptedAnimation();
	//	if (anim->getType() != Animation_Type::MOVING)_interupted_animation = anim;
	//	else _interupted_animation = anim->getInteruptedAnimation();
	//}
	//else {
	//	_interupted_animation = anim->getInteruptedAnimation();
	//}
	
	if (anim != this ) {
		//_interupted_animation = anim->getInteruptedAnimation();
		if (anim->getType() != Animation_Type::MOVING)_interupted_animations.push_back(anim);
		else _interupted_animations.push_back(anim->getInteruptedAnimation());
	}


		
	//if (anim->getType() == Animation_Type::MOVING) {
	//	_interupted_animation = anim->getInteruptedAnimation();
	//}
	//else {
	//	_interupted_animation = anim;
	//}
	
}

Animation* Animation::removeInteruptedAnimation(){
	vector<Animation*> temp;
	Animation* temp2 = _interupted_animations.back();

	LOOP(_interupted_animations.size() - 1)temp.push_back(_interupted_animations[i]);
	_interupted_animations.clear();
	LOOP(temp.size())_interupted_animations.push_back(temp[i]);
	temp.clear();

	return temp2;
}

Animation* Animation::getInteruptedAnimation() const {
	if (_interupted_animations.size() == 0)return nullptr;
	return _interupted_animations.back();
}


bool Animation::isOver(){
	if (_play_forever)return false;
	else return _is_over;
}

void Animation::reset()
{
	_interupted_animation = nullptr;
	_is_over = true;
}

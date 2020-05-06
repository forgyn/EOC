#pragma once
#include "Object.h"
#include "Bar.h"


class Party;

class DynamicEntity : public Object{
public:
	//DynamicEntity(const wstring& name, const size_t& size_x, const size_t& size_y, GameHandle* gameHandle);
	virtual ~DynamicEntity();

	virtual Object* cloneObj();
	virtual DynamicEntity* cloneDE() = 0;
	virtual void placeView(View* view);
	virtual void update();
	virtual void updateBars();
	virtual void draw();
	//virtual void move(const float& x, const float& y);
	//virtual void move(const Direction &dir);

	virtual bool  addMove(const Direction &dir);
	virtual void addMove(const float& x, const float& y);
	virtual void removeLastMove();
	virtual void updateMovePos();
	virtual void playMoveAnim();
	virtual Vector2u getNextPos();

	virtual bool isMoving() { return _moving; }
	virtual Party* convertParty();

	virtual void showBars(const bool& hp_bar, const bool& mp_bar);
	virtual void hideBars();

	virtual void showNameAndLvl();
	virtual void hideNameAndLvl();

	virtual void showCursor();
	virtual void hideCursor();

	virtual bool isDead() { return _is_dead; }

	virtual unsigned getLvl() { return _lvl; }
	virtual Vector2f getHp() { return Vector2f(_hp, _max_hp); }
	virtual float dealPhysDmg(const float& hp);
	virtual Vector2f getMp() { return Vector2f(_mp, _max_mp); }
	virtual void removeMp(const float& mp);
	virtual Vector2u getStr() { return Vector2u(_str,_max_str); }
	virtual Vector2u getEnd() { return Vector2u(_end, _max_end); }
	virtual float getPhysDmg();


	virtual Vector2u getInt() { return Vector2u(_int, _max_int); }
	virtual Vector2u getWis() { return Vector2u(_wis, _max_wis); }
	virtual Vector2u getAgi() { return Vector2u(_agi, _max_agi); }
	virtual Vector2u getLuc() { return Vector2u(_luc, _max_luc); }


	virtual bool movingFinished() { return _moving_finished; }
	virtual void stopMoving();
	void refillHp() { _hp = _max_hp; }
	void refillMp() { _mp = _max_mp; }
	void initStats();



	Bar* _hp_bar = nullptr;
	Bar* _mp_bar = nullptr;
	Text* _name_lvl_text = nullptr;

#ifdef DEBUG
	virtual void showInfo() {
		Object::showInfo();
		wcout << "Lvl    : " << _lvl << endl;
		wcout << "Hp : " << _hp << "/" <<_max_hp << endl;
		wcout << "Mp : " << _mp << "/" << _max_mp << endl;
		wcout << "Max Str: " << _max_str << endl;
		wcout << "Max End: " << _max_end << endl;
		wcout << "Max Int: " << _max_int << endl;
		wcout << "Max Wis: " << _max_wis << endl;
		wcout << "Max Agi: " << _max_agi << endl;
		wcout << "Max Luc: " << _max_luc << endl;
	}
#endif // DEBUG



protected:
	Entity_Type _entity_type = Entity_Type::Error;
	bool _moving = false;
	Clock _moving_clock;

	double _time_to_move = 0.350;
	Vector2f _move_start_point;
	Vector2f _move_end_point;
	Direction _moving_direction = Direction::NONE;
	vector<Direction> _moving_que;
	
	bool _show_cursor = false;
	RectangleShape* _cursor = nullptr;

	bool _in_combat = false;
	bool _is_dead = false;

	bool _moving_finished = true;
	bool _stop_moving = false;
	bool _moving_pause = false;
	bool _cons_moving = false;

	bool _show_hp_bar = false;
	bool _show_mp_bar = false;
	bool _show_name_and_lvl = false;


	//stats
	unsigned _lvl = 1;
	double _max_hp;
	double _hp;
	double _max_mp;
	double _mp;
	unsigned _max_str;
	unsigned _str;
	unsigned _max_end;
	unsigned _end;
	unsigned _max_int;
	unsigned _int;
	unsigned _max_wis;
	unsigned _wis;
	unsigned _max_agi;
	unsigned _agi;
	unsigned _max_luc;
	unsigned _luc;

private:



};


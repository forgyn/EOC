#pragma once
#include "Object.h"
#include "Bar.h"
#include "ClassList.h"

class Party;


class Stat {
public:
	Stat(const double& max = 0) {
		this->_max = max;
		_now = this->_max;
	}
	void setMax(const double& max) { _max = max; }
	void refill() { _now = _max; }

	double getMax() { return _max; }
	double getNow() { return _now; }
	bool reduce(const double& amount) {
		_now -= amount;
		if (_now <= 0) { 
			_now = 0;
			return false; 
		}
		else if (_now > _max) { 
			_now = _max; 
			return true;
		}
		else return true;
	}
	bool reducePercent(const double& percent) {
		_now -= _max*percent;
		if (_now <= 0)return false;
		else return true;
	}
	bool isMoreThan(const double& than) { return _now > than; }
	bool isLessThan(const double& than) { return _now < than; }
	double percent() { return _now / _max; }
	void zero() { _now = 0; }


private:
	double _now;
	double _max;
};

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
	virtual void useNormalAttack(Party* caster_party, Party* target_party, DynamicEntity* target);
	virtual bool  addMove(const Direction &dir);
	virtual void addMove(const float& x, const float& y);
	virtual void removeLastMove();
	virtual void updateMovePos();
	virtual void playMoveAnim();
	virtual Vector2u getNextPos();

	virtual void setInfoString(wstringstream& ss);
	void setSpellInfoString(wstringstream& ss,unsigned spell_id);
	
	virtual string getEntityType() { return "DynamicEntity"; }

	virtual bool isMoving() { return _moving; }
	virtual Party* convertParty();

	virtual void showBars(const bool& hp_bar = true, const bool& mp_bar = true);
	virtual void hideBars();

	virtual void showNameAndLvl();
	virtual void hideNameAndLvl();

	virtual void showCursor();
	virtual void hideCursor();

	virtual bool isDead() { return _is_dead; }

	virtual unsigned getLvl() { return _lvl; }
	virtual Stat getHp() { return _hp; }
	virtual float dealDmg(const float& hp,const Element_Type& type);
	virtual Stat getMp() { return _mp; }
	virtual void removeMp(const float& mp);
	virtual Stat getStr() { return _str; }
	virtual Stat getEnd() { return _end; }
	virtual float getPhysDmg();
	//spells
	void addSpellToPanel(ButtonMenu* menu);
	bool checkSpellAvaible(unsigned spell_id);
	void useSpell(unsigned spellId, Party* caster_party, Party* target_party, DynamicEntity* target);
	void spellCostApply(double abs_hp_cost,double percent_hp_cost, double abs_mp_cost,double percent_mp_cost);

	virtual Stat getInt() { return _int; }
	virtual Stat getWis() { return _wis; }
	virtual Stat getAgi() { return _agi; }
	virtual Stat getLuc() { return _luc; }
	virtual unsigned getMoney() { return _money; }

	virtual bool movingFinished() { return _moving_finished; }
	virtual void stopMoving();
	void refillHp() { _hp.refill(); }
	void refillMp() { _mp.refill(); }
	void initStats();

	void resetPtrOnClone();

	Bar* _hp_bar = nullptr;
	Bar* _mp_bar = nullptr;
	Text* _name_lvl_text = nullptr;

#ifdef DEBUG
	virtual void showInfo() {
		Object::showInfo();
		wcout << "Lvl    : " << _lvl << endl;
		wcout << "Hp : " << _hp.getNow() << "/" << _hp.getMax() << endl;
		wcout << "Mp : " << _mp.getNow() << "/" << _mp.getMax() << endl;
		wcout << "Str: " << _str.getNow() << endl;
		wcout << "End: " << _end.getNow() << endl;
		wcout << "Int: " << _int.getNow() << endl;
		wcout << "Wis: " << _wis.getNow() << endl;
		wcout << "Agi: " << _agi.getNow() << endl;
		wcout << "Luc: " << _luc.getNow() << endl;
	}
#endif // DEBUG

	virtual Stat getPhysDef() { return _phys_abs_def; }
	virtual Stat getPhysDefPer() { return _phys_per_def; }

	virtual Stat getFireDef() { return _fire_abs_def; }
	virtual Stat getFireDefPer() { return _fire_per_def; }

	virtual Stat getFrostDef() { return _frost_abs_def; }
	virtual Stat getFrostDefPer() { return _frost_per_def; }

	virtual Stat getWaterDef() { return _water_abs_def; }
	virtual Stat getWaterDefPer() { return _water_per_def; }

	virtual Stat getElecDef() { return _electricity_abs_def; }
	virtual Stat getElecDefPer() { return _electricity_per_def; }

	virtual Stat getLifeDef() { return _life_abs_def; }
	virtual Stat getLifeDefPer() { return _life_per_def; }

	virtual Stat getDeathDef() { return _death_abs_def; }
	virtual Stat getDeathDefPer() { return _death_per_def; }

	virtual Stat getLightDef() { return _light_abs_def; }
	virtual Stat getLightDefPer() { return _light_per_def; }

	virtual Stat getDarkDef() { return _dark_abs_def; }
	virtual Stat getDarkDefPer() { return _dark_per_def; }

	virtual Stat getPureDef() { return _pure_abs_def; }
	virtual Stat getPureDefPer() { return _pure_per_def; }

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
	Stat _hp;
	Stat _mp;
	Stat _str;
	Stat _end;
	Stat _int;
	Stat _wis;
	Stat _agi;
	Stat _luc;

	//spells
	vector<Spell*> _spells;
	//Spell* _default_attack = new SpellInstantDmg(L"NormalAttack", Element_Type::PHYSICAL, 1, 0.75);
	Spell* _default_attack = nullptr;

	//class
	Class* _class = nullptr;

	//money
	unsigned _money = 0;

	//element affinity
	Stat _phys_abs_def;
	Stat _phys_per_def;


	Stat _fire_abs_def;
	Stat _fire_per_def;


	Stat _frost_abs_def;
	Stat _frost_per_def;

	Stat _electricity_abs_def;
	Stat _electricity_per_def;

	Stat _water_abs_def;
	Stat _water_per_def;

	Stat _life_abs_def;
	Stat _life_per_def;

	Stat _death_abs_def;
	Stat _death_per_def;

	Stat _light_abs_def;
	Stat _light_per_def;

	Stat _dark_abs_def;
	Stat _dark_per_def;
	
	Stat _pure_abs_def;
	Stat _pure_per_def;

private:

};


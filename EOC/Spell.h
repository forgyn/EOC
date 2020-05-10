#pragma once
#include "Utility.h"

class Party;
class DynamicEntity;

class Spell{
public:
	Spell(const wstring& name) : _name(name){}
	virtual ~Spell();
	virtual void use(Party* caster_party,DynamicEntity* caster,Party* target_party,DynamicEntity* target) = 0;
	virtual Spell* clone() = 0;
	wstring getName() { return _name; }
	virtual void setInfoToString(wstringstream& ss, DynamicEntity* caster);
	//x - hp,y - mp
	Vector2f getAbsCost() { return Vector2f(_abs_hp_cost,_abs_mp_cost); }
	//x - hp,y - mp
	Vector2f getPercentCost() { return Vector2f(_percent_hp_cost, _percent_mp_cost); }
protected:
	const wstring _name;
	unsigned _lvl = 1;
	unsigned _xp = 0;
	unsigned _needed_xp = 1;
	bool _can_lvl_up = false;


	double _abs_mp_cost = 0;
	double _percent_mp_cost = 0;

	double _abs_hp_cost = 0;
	double _percent_hp_cost = 0;

	//raw spell values
	double _raw_value_1 = 0;
	double _raw_value_2 = 0;
	double _raw_value_3 = 0;

	//spell multipliers
	double _hp_m = 0;
	double _mp_m = 0;
	double _str_m = 0;
	double _end_m = 0;
	double _int_m = 0; 
	double _wis_m = 0;
	double _agi_m = 0;
	double _luc_m = 0;

	double _lvl_m = 0;
	double _money_m = 0;

	double _accuracy = 1;

	static uniform_real_distribution<double> _random_chance;

	Element_Type _element_type = Element_Type::ERROR;

};


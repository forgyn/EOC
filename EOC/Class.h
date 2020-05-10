#pragma once
#include "Utility.h"
#include "SpellList.h"

class Class
{
public:
	Class(const wstring& name, double hp_m, double mp_m, double str_m, double end_m, double int_m, double wis_m, double agi_m, double luc_m)
		:class_name(name), hp_m(hp_m), mp_m(mp_m), str_m(str_m), end_m(end_m), int_m(int_m), wis_m(wis_m), agi_m(agi_m), luc_m(luc_m) {}
	virtual ~Class() {};
	virtual Class* clone() = 0;

	const wstring class_name;
	const double hp_m;
	const double mp_m;
	const double str_m;
	const double end_m;
	const double int_m;
	const double wis_m;
	const double agi_m;
	const double luc_m;
private:

protected:
	//init class spells
	//vector<Spell*> _spells;
};

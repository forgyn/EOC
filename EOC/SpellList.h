#pragma once
#include "Spell.h"
class Party;
class DynamicEntity;

class SpellInstantDmg : public Spell {
public:
	SpellInstantDmg(const wstring& name, Element_Type element_type,
										const double& raw_dmg,
										const double& accuracy = 1,
										const double& abs_mp_cost = 0,
										const double& percent_mp_cost = 0,
										const double& abs_hp_cost = 0,
										const double& percent_hp_cost = 0,
										const double& str_m = 0,
										const double& end_m = 0,
										const double& int_m = 0,
										const double& wis_m = 0,
										const double& agi_m = 0,
										const double& luc_m = 0,
										const double& hp_m = 0,
										const double& mp_m = 0,										
										const double& lvl_m = 0,
										const double& money_m = 0);



	virtual void use(Party* caster_party, DynamicEntity* caster, Party* target_party, DynamicEntity* target);
	virtual Spell* clone() { return new SpellInstantDmg(*this); }
	virtual void setInfoToString(wstringstream& ss, DynamicEntity* caster);

private:

};


class NormalAttack : public SpellInstantDmg {
public:
	NormalAttack();
	virtual Spell* clone() { return new NormalAttack(*this); }
	//void use(Party* caster_party, DynamicEntity* caster, Party* target_party, DynamicEntity* target);
};




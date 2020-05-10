#include "SpellList.h"
#include "Party.h"


SpellInstantDmg::SpellInstantDmg(const wstring& name, 
	Element_Type element_type,
	const double& raw_dmg,
	const double& accuracy,
	const double& abs_mp_cost,
	const double& percent_mp_cost,
	const double& abs_hp_cost,
	const double& percent_hp_cost,
	const double& str_m,
	const double& end_m,
	const double& int_m,
	const double& wis_m,
	const double& agi_m,
	const double& luc_m,
	const double& hp_m,
	const double& mp_m,
	const double& lvl_m,
	const double& money_m)
:Spell(name){
	_raw_value_1 = raw_dmg;

	_accuracy = accuracy;

	 _hp_m = hp_m;
	 _mp_m = mp_m;

	 _abs_hp_cost = abs_hp_cost;
	 _abs_mp_cost = abs_mp_cost;

	 _percent_hp_cost = percent_hp_cost;
	 _percent_mp_cost = percent_mp_cost;


	 _str_m = str_m;
	 _end_m = end_m;
	 _int_m = int_m;
	 _wis_m = wis_m;
	 _agi_m = agi_m;
	 _luc_m = luc_m;

	 _lvl_m = lvl_m;
	 _money_m = money_m;

	 _element_type = element_type;

	 _can_lvl_up = true;

}

void SpellInstantDmg::use(Party* caster_party, DynamicEntity* caster, Party* target_party, DynamicEntity* target){
	double chance = _random_chance(_Random_Generator);
	//check hit
#ifdef DEBUG
	wcout << "Chance to hit : " <<(((caster->getAgi().getNow() - target->getAgi().getNow()) * 0.025) + (_accuracy))*100 << " %" << endl;
#endif // DEBUG
	
	if (((caster->getAgi().getNow() - target->getAgi().getNow()) * 0.025) + (_accuracy) > chance) {
		//deal dmg
		float pre_reduction_dmg =
			_raw_value_1 +
			caster->getStr().getNow() * _str_m +
			caster->getEnd().getNow() * _end_m +
			caster->getInt().getNow() * _int_m +
			caster->getWis().getNow() * _wis_m +
			caster->getAgi().getNow() * _agi_m +
			caster->getLuc().getNow() * _luc_m +
			caster->getHp().getNow() * _hp_m +
			caster->getMp().getNow() * _mp_m +
			caster->getMoney() * _money_m +
			caster->getLvl() * _lvl_m;


		float after_reduction_dmg = target->dealDmg(pre_reduction_dmg,_element_type);

		
#ifdef DEBUG
		wcout << caster->getName() << L" used " << _name << L" on " << target->getName() << " . Deald " << to_wstring(after_reduction_dmg) << " DMG!" << endl;
#endif // DEBUG

	}
	else {

#ifdef DEBUG
		wcout << caster->getName() << L" used " << _name << " but missed!" << endl;
#endif // DEBUG

	}
	caster->spellCostApply(_abs_hp_cost, _percent_hp_cost, _abs_mp_cost, _percent_mp_cost);
	target->updateBars();
	caster->updateBars();

}

void SpellInstantDmg::setInfoToString(wstringstream& ss,DynamicEntity* caster){
	Spell::setInfoToString(ss, caster);
	ss << "-----------VALUES------------" << endl;
	if (_raw_value_1 != 0)	ss << " RAW DMG   : " << setw(4) << _raw_value_1 << endl;
	if (_hp_m != 0)	ss <<  " HP MULTIPLIER  : " << setw(4) << _hp_m << endl;
	if (_mp_m != 0)	ss <<  " MP MULTIPLIER  : " << setw(4) << _mp_m << endl;
	if (_str_m != 0)	ss <<  " STR MULTIPLIER : " << setw(4) << _str_m << endl;
	if (_end_m != 0)	ss <<  " END MULTIPLIER : " << setw(4) << _end_m << endl;
	if (_int_m != 0)	ss <<  " INT MULTIPLIER : " << setw(4) << _int_m << endl;
	if (_wis_m != 0)	ss <<  " WIS MULTIPLIER : " << setw(4) << _wis_m << endl;
	if (_agi_m != 0)	ss <<  " AGI MULTIPLIER : " << setw(4) << _agi_m << endl;
	if (_luc_m != 0)	ss <<  " LUC MULTIPLIER : " << setw(4) << _luc_m << endl;
	if (_lvl_m != 0)	ss <<  " LVL MULTIPLIER : " << setw(4) << _lvl_m << endl;
	if (_money_m != 0)ss << " MONEY MULTIPLIER : " << setw(4) << _money_m << endl;
	ss << "----------------------------" << endl;

	float pre_reduction =
		_raw_value_1 +
		caster->getStr().getNow() * _str_m +
		caster->getEnd().getNow() * _end_m +
		caster->getInt().getNow() * _int_m +
		caster->getWis().getNow() * _wis_m +
		caster->getAgi().getNow() * _agi_m +
		caster->getLuc().getNow() * _luc_m +
		caster->getHp().getNow() * _hp_m +
		caster->getMp().getNow() * _mp_m +
		caster->getMoney() * _money_m +
		caster->getLvl() * _lvl_m;
	if(pre_reduction < 0)ss << "ESTIMATED HEAL: " << -1*pre_reduction << endl;
	else if (pre_reduction > 0)ss << "ESTIMATED DMG: " << pre_reduction << endl;
}

NormalAttack::NormalAttack()
:SpellInstantDmg(L"Normal Attack",Element_Type::PHYSICAL,1,0.85){
	_str_m = 7;
	_end_m = 2;
	_agi_m = 5;

	_can_lvl_up = false;

}

//void NormalAttack::use(Party* caster_party, DynamicEntity* caster, Party* target_party, DynamicEntity* target){
//	
//	/*float pre_reduction_dmg = caster->getStr().getNow() * _str_m + caster->getEnd().getNow() * _end_m + caster->getAgi().getNow() * _agi_m + _raw_value_1;
//	
//	float after_reduction_dmg = (pre_reduction_dmg - target->getEnd().getNow() *2 - target->getStr().getNow() *0.25);
//	
//	if (after_reduction_dmg < 1)after_reduction_dmg = 1;
//
//	target->dealDmg(after_reduction_dmg);*/
//}

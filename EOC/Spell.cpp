#include "Spell.h"
#include "Party.h"

Spell::~Spell(){

}

void Spell::setInfoToString(wstringstream& ss,DynamicEntity* caster){
	
	ss << "---> "<<caster->getName() << endl;
	ss << " HP  : " << setw(4) << caster->getHp().getNow() << setw(2) << "/" << setw(4) << caster->getHp().getMax() << endl;
	ss << " MP  : " << setw(4) << caster->getMp().getNow() << setw(2) << "/" << setw(4) << caster->getMp().getMax() << endl;
	ss << "----------DETAILS----------" << endl;
	ss << " NAME: " << setw(4) << _name << endl;
	ss << " ELEMENT: ";

	switch (_element_type) {
	case Element_Type::PHYSICAL:
		ss << "PHYSICAL" << endl;
		break;
	case Element_Type::FIRE:
		ss << "FIRE" << endl;
		break;
	case Element_Type::FROST:
		ss << "FROST" << endl;
		break;
	case Element_Type::WATER:
		ss << "WATER" << endl;
		break;
	case Element_Type::ELECTRICITY:
		ss << "ELECTRICITY" << endl;
		break;
	case Element_Type::LIGHT:
		ss << "LIGHT" << endl;
		break;
	case Element_Type::DARK:
		ss << "DARK" << endl;
		break;
	case Element_Type::LIFE:
		ss << "LIFE" << endl;
		break;
	case Element_Type::DEATH:
		ss << "DEATH" << endl;
		break;
	case Element_Type::PURE:
		ss << "PURE" << endl;
		break;
	}

	if (_abs_hp_cost != 0)	ss << " HP COST : " << setw(4) << _abs_hp_cost << endl;
	if (_percent_hp_cost != 0)	ss << " HP COST% : " << setw(4) << _percent_hp_cost * 100 << " (" << _percent_hp_cost * caster->getHp().getMax() << " HP)" << endl;
	if (_abs_mp_cost != 0)	ss << " MP COST : " << setw(4) << _abs_mp_cost << endl;
	if (_percent_mp_cost != 0)	ss << " MP COST% : " << setw(4) << _percent_mp_cost * 100 << " (" << _percent_mp_cost * caster->getMp().getMax() << " MP)" << endl;
	if (_accuracy != 0)	ss << " ACCURACY  : " << setw(4) << _accuracy << endl;
}

#include "Enemy.h"

//Enemy::Enemy(const wstring& name, EnemyType* enemy_type, EnemyClass* enemy_class, GameHandle* gameHandle)
//{
//
//}

Enemy::Enemy(wstring name, Class* enemy_class, unsigned base_lvl, double hp, double mp, unsigned str, unsigned end, unsigned intel, unsigned wis, unsigned agi, unsigned luc)
	:name(name), base_lvl(base_lvl) {
	_name = name;
	_lvl = base_lvl;
	_class = enemy_class;
	_hp = Stat(hp * _class->hp_m);
	_mp = Stat(mp * _class->mp_m);
	_str = Stat(str * _class->str_m);
	_end = Stat(end * _class->end_m);
	_int = Stat(intel * _class->int_m);
	_wis = Stat(wis * _class->wis_m);
	_agi = Stat(agi * _class->agi_m);
	_luc = Stat(luc * _class->luc_m);
	initStats();

	_entity_type = Entity_Type::Enemy;
	_object_type = Object_Type::Dynamic_Entity;
	_stand = Entity_Stand::HOSTILE;
}

Party* Enemy::convertParty()
{
	Party* newParty = nullptr;
	newParty = new HostileParty(this);
	newParty->addMember(this->cloneDE());
	return newParty;
}

void Enemy::resetPtrOnClone(){
	auto temp = _class;
	_class = nullptr;
	_class = temp->clone();
	DynamicEntity::resetPtrOnClone();
}

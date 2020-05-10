#pragma once
#include "Utility.h"
#include "DynamicEntity.h"
#include "Party.h"



class Enemy : public DynamicEntity
{
public:
	/*Enemy(const wstring& name, EnemyClass* enemy_class, GameHandle* gameHandle);*/
	Enemy(wstring name, Class* enemy_class,unsigned base_lvl, double hp, double mp, unsigned str, unsigned end, unsigned intel, unsigned wis, unsigned agi, unsigned luc);
	
	virtual ~Enemy() {};
	virtual Object* cloneObj() = 0;
	virtual string getEntityType() { return "Enemy"; }
	Party* convertParty();
	void resetPtrOnClone();

#ifdef DEBUG
	void showInfo() {
		DynamicEntity::showInfo();
		wcout << "Class: " << _class->class_name << endl;
	}
#endif // DEBUG


	const wstring name;
	const unsigned base_lvl;
	
protected:
	
};


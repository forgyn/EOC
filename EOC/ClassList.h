#pragma once
#include "Class.h"


class Warrior : public Class {
public:
	Warrior()
		: Class(L"Warrior",
			2.50,	//hp_m
			0.25,	//mp_m
			1.50,	//str_m
			1.20,	//end_m
			0.50,	//int_m
			0.20,	//wis_m
			0.50,	//agi_m
			1.00	//luc_m
		)
	{

	}
	virtual Class* clone() { return new auto(*this); }
};

class Monster : public Class {
public:
	Monster()
		:Class(L"Monster", 1, 1, 1, 1, 1, 1, 1, 1)
	{

	}
	~Monster() {}
	virtual Class* clone() { return new Monster(*this); }

};


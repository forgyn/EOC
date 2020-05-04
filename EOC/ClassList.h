#pragma once

#include "Class.h"

class Warrior : public eoc::Class {
public:
	Warrior()
		:eoc::Class(L"Warrior", 
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
	virtual eoc::Class* clone() { return new auto(*this); }
};

class Monster : public eoc::Class {
public:
	Monster()
		:eoc::Class(L"Monster", 1, 1, 1, 1, 1, 1, 1, 1)
	{

	}
	~Monster() {}
	virtual eoc::Class* clone() { return new Monster(*this); }

};


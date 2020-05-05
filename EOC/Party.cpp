#include "Party.h"
#include "DynamicEntity.h"

Party::~Party() { 
	LOOP(_party.size()) {
		delete _party[i];
	}
	if (_stand != Entity_Stand::PLAYER) { 
		delete _representative;
		_representative = nullptr;
	}
	Object::~Object(); 
};



void Party::update() { 
	_representative->update();
}

void Party::addMember(DynamicEntity* member)
{
	_party.push_back(member);
}

void Party::init(const double& pos_y)
{
	_pos_y = pos_y;

	unsigned size_x_1 = 0;
	double space_size_1 = 0;
	unsigned size_x_2 = 0;
	double space_size_2 = 0;

	LOOP(_party.size()) {
		_party[i]->scale(3);
		size_x_1 += _party[i]->getRecSize().x;
	}
	space_size_1 = (static_cast<double>(GameHandle::getWinSize().x)-static_cast<double>(size_x_1)) / static_cast<double>(1 + _party.size());

	LOOP(_party.size()) {
		if (i == 0) {
			_party[i]->setAbsPosition(space_size_1 + _party[i]->getRecSize().x / 2, _pos_y);
			//_background_side_1[i]->setPosition(space_size_1, _pos_y);
		}
		else {
			_party[i]->setAbsPosition(_party[i - 1]->getPosition().x + space_size_1 + _party[i - 1]->getRecSize().x / 2 + _party[i]->getRecSize().x / 2,_pos_y);
			//_background_side_1[i]->setPosition(_background_side_1[i - 1]->getPosition().x + space_size_1 + _background_side_1[i - 1]->getSize().x / 2 + _background_side_1[i]->getSize().x / 2, 250);
		}
	}



}

PlayerParty::PlayerParty(Player* player){
	_stand = Entity_Stand::PLAYER;
	_entity_type = Entity_Type::Party;
	_object_type = Object_Type::Dynamic_Entity;
	_player = player;
	_party.push_back(_player);
	_representative = _player->cloneDE();
	
}

Object* PlayerParty::cloneObj(){
	auto* temp = new auto(*this);
	temp->resetPtrOnClone();
	return  temp;
}

DynamicEntity* PlayerParty::cloneDE()
{
	auto* temp = new auto(*this);
	temp->resetPtrOnClone();
	return  temp;
}

void Party::resetPtrOnClone()
{	
	DynamicEntity* temp_rep = _representative;
	_representative = nullptr;
	_representative = temp_rep->cloneDE();
	_representative->resetPtrOnClone();

	vector<DynamicEntity*> temp_party;

	LOOP(_party.size()) {
		temp_party.push_back(_party[i]->cloneDE());
	}

	_party.clear();

	LOOP(temp_party.size()) {
		_party.push_back(temp_party[i]->cloneDE());
	}

	temp_party.clear();

	Object::resetPtrOnClone();
}

void Party::drawInCombat()
{
	LOOP(_party.size()) {
		_party[i]->draw();
	}
}

void Party::combatUpdate()
{
	LOOP(_party.size()) {
		_party[i]->update();
	}
}

void Party::draw()
{
	_representative->draw();
}

void Party::removeDead()
{
	unsigned dead_id = 0;
	bool someone_is_dead = false;

	LOOP(_party.size()) {
		if (_party[i]->isDead()) {
			dead_id = i;
			someone_is_dead = true;
			break;
		}
	}

	if (!someone_is_dead)return;

	if (_party.size() > 1) {
		DynamicEntity* temp = _party[dead_id];
		vector<DynamicEntity*> temp2;


		LOOP(_party.size() - 1) {
			if (i != dead_id)temp2.push_back(_party[i]);
		}
		_party.clear();

		LOOP(temp2.size()) {
			_party.push_back(temp2[i]);
		}

		temp2.clear();

		delete temp; temp = nullptr;
	}
	else {
		_is_dead = true;
		delete _party.back(); _party.back() = nullptr;
		_party.clear();
	}
}

HostileParty::HostileParty(DynamicEntity* representative)
{
	_stand = Entity_Stand::HOSTILE;
	_entity_type = Entity_Type::Party;
	_object_type = Object_Type::Dynamic_Entity;
	_rectangle_size = representative->getRecSize();
	_representative = representative;

}

FriendlyParty::FriendlyParty(DynamicEntity* representative) {
	_stand = Entity_Stand::FRIENDLY;
	_entity_type = Entity_Type::Party;
	_object_type = Object_Type::Dynamic_Entity;
	
	_representative = representative;
}
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
	_have_player = true;
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
	//Object::resetPtrOnClone();

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

	if (_show_hp_bar)_hp_bar->draw();
	if (_show_mp_bar)_mp_bar->draw();

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

bool Party::isDead(){
	unsigned num_of_dead = 0;

	LOOP(_party.size()) {
		if (_party[i]->isDead())num_of_dead++;
	}
	return num_of_dead == _party.size();
}

void Party::setInfoString(wstringstream& ss){
	_party[_member_info]->setInfoString(ss);
	/*ss << "Name: " << _party[_member_info]->getName() << endl;
	ss << "Stand: ";
	switch (_party[_member_info]->getStand()) {
	case Entity_Stand::PLAYER:
		ss << "PLAYER";
		break;
	case Entity_Stand::FRIENDLY:
		ss << "FRIENDLY";
		break;
	case Entity_Stand::HOSTILE:
		ss << "HOSTILE";
		break;
	case Entity_Stand::ERROR:
		ss << "ERROR";
		break;
	case Entity_Stand::NEUTRAL:
		ss << "NEUTRAL";
		break;
	}
	ss << endl;
	ss << ":----------STATS----------:" << endl;
	ss << " HP  : " << setw(4) << _party[_member_info]->getHp().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getHp().getMax() << endl;
	ss << " MP  : " << setw(4) << _party[_member_info]->getMp().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getMp().getMax() << endl;
	ss << " STR : " << setw(4) << _party[_member_info]->getStr().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getStr().getMax() << endl;
	ss << " END : " << setw(4) << _party[_member_info]->getEnd().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getEnd().getMax() << endl;
	ss << " INT : " << setw(4) << _party[_member_info]->getInt().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getInt().getMax() << endl;
	ss << " WIS : " << setw(4) << _party[_member_info]->getWis().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getWis().getMax() << endl;
	ss << " AGI : " << setw(4) << _party[_member_info]->getAgi().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getAgi().getMax() << endl;
	ss << " LUC : " << setw(4) << _party[_member_info]->getLuc().getNow() << setw(2) << "/" << setw(4) << _party[_member_info]->getLuc().getMax() << endl;
	ss << ":-------------------------:" << endl;*/
}

void Party::nextMemberInfo(){
	_member_info++;
	if (_member_info > _party.size() - 1)_member_info = 0;
}

void Party::previousMemberInfo(){
	if (_member_info > 0) {
		_member_info--;
	}
	else {
		_member_info = _party.size() - 1;
	}
}

void Party::showBars(const bool& hp_bar, const bool& mp_bar){
	if (!_representative->isMoving()) {

		_show_hp_bar = hp_bar;
		_show_mp_bar = mp_bar;

		float _current_hp = 0;
		float _max_hp = 0;

		float _current_mp = 0;
		float _max_mp = 0;

		LOOP(_party.size()) {
			_current_hp += _party[i]->getHp().getNow();
			_max_hp += _party[i]->getHp().getMax();
			_current_mp += _party[i]->getMp().getNow();
			_max_mp += _party[i]->getMp().getMax();
		}

		if (_max_mp <= 0)_show_mp_bar = false;

		if (_show_hp_bar && _show_mp_bar) {
			_hp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _representative->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _representative->getPosition().y + static_cast<double>(GameHandle::getWinSize().y) / 100);
			_hp_bar->setColor(Color::Black, Color::Red);
			_hp_bar->setValue(_current_hp / _max_hp);

			_mp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _representative->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _representative->getPosition().y + static_cast<double>(GameHandle::getWinSize().y) / 40 + static_cast<double>(GameHandle::getWinSize().y) / 100);
			_mp_bar->setColor(Color::Black, Color(49, 76, 247));
			_mp_bar->setValue(_current_mp / _max_mp);
		}

		if (_show_hp_bar && !_show_mp_bar) {
			_hp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _representative->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _representative->getPosition().y + static_cast<double>(GameHandle::getWinSize().y) / 100);
			_hp_bar->setColor(Color::Black, Color::Red);
			_hp_bar->setValue(_current_hp / _max_hp);
		}

		if (_show_mp_bar && !_show_hp_bar) {
			_mp_bar = new Bar(GameHandle::getWinSize().x / BAR_WINDOW_PORTION, GameHandle::getWinSize().y / 40, _representative->getPosition().x - GameHandle::getWinSize().x / (BAR_WINDOW_PORTION * 2), _representative->getPosition().y);
			_mp_bar->setColor(Color::Black, Color(49, 76, 247));
			_mp_bar->setValue(_current_mp / _max_mp);
		}
	}
}

void Party::hideBars(){
	if (_show_hp_bar) {
		_show_hp_bar = false;
		delete _hp_bar; _hp_bar = nullptr;
	}
	if (_show_mp_bar) {
		_show_mp_bar = false;
		delete _mp_bar; _mp_bar = nullptr;
	}

}

HostileParty::HostileParty(DynamicEntity* representative)
{
	_stand = Entity_Stand::HOSTILE;
	_entity_type = Entity_Type::Party;
	_object_type = Object_Type::Dynamic_Entity;
	_rectangle_size = representative->getRecSize();
	_representative = representative;
	_representative->scale(1.4);

}

FriendlyParty::FriendlyParty(DynamicEntity* representative) {
	_stand = Entity_Stand::FRIENDLY;
	_entity_type = Entity_Type::Party;
	_object_type = Object_Type::Dynamic_Entity;
	
	_representative = representative;
}
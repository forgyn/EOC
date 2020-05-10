#pragma once

#include "Player.h"

class DynamicEntity;


class Party : public DynamicEntity {
public:
	virtual ~Party();
	virtual Object* cloneObj() = 0;
	DynamicEntity* cloneDE() { return nullptr; }
	Party* convertParty() { return this; }
	virtual void update();
	void addMember(DynamicEntity* member);
	void setPosY(const double& y) { _pos_y = y; }
	void init(const double& pos_y);
	size_t getSize() { return _party.size(); }
	DynamicEntity* operator[](const size_t& n) { return _party[n]; }
	virtual void resetPtrOnClone();
	void drawInCombat();
	void combatUpdate();
	void draw();
	void scale(const Vector2f& mult) { _representative->scale(mult); }
	void scale(const float& mult) { _representative->scale(mult); }
	//void move(const float& x, const float& y) { _representative->move(x, y); }
	bool isMoving() { return _representative->isMoving(); }
	void setGridPosition(const float& x, const float& y) { _representative->setGridPosition(x, y); }
	void setAbsPosition(const float& x, const float& y) { _representative->setAbsPosition(x, y); }
	void setDefaultTexture(Texture* texture) { _representative->setDefaultTexture(texture); }
	void setId(const unsigned& id) { _representative->setId(id); }
	unsigned getId() { return _representative->getId(); }
	Vector2f getRecSize() { return _representative->getRecSize(); }
	void setColor(const Color& color) { _representative->setColor(color); }
	void startAnimation(const wstring& animation_name, const size_t& num_of_play = 0, const double& pause_time_s = 0) { _representative->startAnimation(animation_name, num_of_play,pause_time_s); }
	void copyAnimations(Object* copy, Object* paste) { _representative->copyAnimations(copy, paste); }
	void placeView(View* view) { _representative->placeView(view); }
	vector<Animation*>* getAnimations() { return _representative->getAnimations(); }
	Entity_Stand getStand() { return _representative->getStand(); };
	Vector2f getPosition() { return _representative->getPosition(); }
	Vector2u getGridPosition() { return _representative->getGridPosition(); }
	bool movingFinished() { return _representative->movingFinished(); }
	void stopMoving() { _representative->stopMoving(); }

	bool addMove(const Direction& dir) {return  _representative->addMove(dir); }
	void addMove(const float& x, const float& y) { _representative->addMove(x,y); };
	void removeLastMove() { _representative->removeLastMove(); }
	void updateMovePos() { _representative->updateMovePos(); }
	void playMoveAnim() { _representative->playMoveAnim(); }
	Vector2u getNextPos() { return _representative->getNextPos(); }
	bool isPlayer() { return _have_player; }
	void removeDead();
	bool isDead();

	DynamicEntity* getEntityOfInterest() { return _entity_of_interest; }
	void setEntityOfInterest(const unsigned& id) { _entity_of_interest = _party[id]; }
	virtual string getEntityType() { return "Party"; }
	virtual void setInfoString(wstringstream& ss);

	void nextMemberInfo();
	void previousMemberInfo();

	void showBars(const bool& hp_bar = true, const bool& mp_bar = true);
	void hideBars();
#ifdef DEBUG
	void showInfo() {
		_representative->showInfo();
	};
#endif // DEBUG

protected:
	vector<DynamicEntity*> _party;
	DynamicEntity* _representative = nullptr;
	DynamicEntity* _entity_of_interest = nullptr;
	double _pos_y = 0;
	bool _have_player = false;
	unsigned _member_info = 0;
};

class PlayerParty : public Party {
public:
	PlayerParty(Player* player);/*{ _player = player; _representative = _player; _gameHandle = gameHandle; }*/
	~PlayerParty() {};
	Object* cloneObj();
	DynamicEntity* cloneDE();
	

private:
	Player* _player = nullptr;
};

class HostileParty : public Party {
public:
	HostileParty(DynamicEntity* representative); /*{_representative = representative;};*/
	~HostileParty() {};
	//void setRepresentative(const size_t& n) { _representative = n; };
	Object* cloneObj() {
		auto* temp = new auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
	DynamicEntity* cloneDE() {
		auto* temp = new auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}

private:

};

class FriendlyParty : public Party {
public:
	FriendlyParty(DynamicEntity* representative);
	~FriendlyParty() {};
	Object* cloneObj() {
		auto* temp = new auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
	DynamicEntity* cloneDE() {
		auto* temp = new auto(*this);
		temp->resetPtrOnClone();
		return  temp;
	}
};
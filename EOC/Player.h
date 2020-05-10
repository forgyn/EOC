#pragma once
#include "DynamicEntity.h"
#include "ClassList.h"

class GameHandle;

class Player : public DynamicEntity {
public:
	Player(const wstring& name,Class* player_class);
	~Player();
	void update();
	//void placeView(View* view);
	Object* cloneObj();
	DynamicEntity* cloneDE();
	void resetPtrOnClone();
	Party* convertParty();
	virtual string getEntityType() { return "Party"; }
	//void move(const float& x, const float& y);
	void draw();
private:
	Class* _class = nullptr;
	uint16_t _xp = 0;
	Clock _timer;
	Clock* _blink_timer = nullptr;

};


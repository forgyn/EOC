#pragma once
#include "Utility.h"
#include "Object.h" 

enum class Static_Entity_Type {ERROR,Tree};


class StaticEntity : public Object {
public:
	//StaticEntity() {};
	//StaticEntity(const wstring& name, const size_t& size_x, const size_t& size_y, GameHandle* gameHandle);
	virtual  Object* cloneObj() = 0;
	virtual Party* convertParty() { return nullptr; }
	//virtual const  Object* cloneObj() = 0;
	virtual StaticEntity* cloneSE() = 0;
	virtual ~StaticEntity();

protected:
	Static_Entity_Type _static_entity_type = Static_Entity_Type::ERROR;

private:
};


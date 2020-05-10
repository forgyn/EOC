#pragma once
#include "StaticEntity.h"
#include "Object.h"

enum class TreeType {Apple,Orange,Banana};



class Tree : public StaticEntity{
public:
	Tree(TreeType type);
	~Tree();
	Party* convertParty() { return nullptr; }
	virtual StaticEntity* cloneSE() { return new Tree(*this); }
	virtual Object* cloneObj();
	//virtual const Object* cloneObj();
private:
	void init();

	TreeType _tree_type = TreeType::Apple;



};


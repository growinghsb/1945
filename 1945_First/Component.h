#pragma once

#include "Game.h"

class Obj;

class Component
{
public:
	Component(COMPONENT_TYPE type, Obj* owner);
	virtual ~Component() = default;

	virtual void update() = 0;
	virtual void render(HDC backDC) {};

	Obj* getOwner() const
	{
		return mOwnerObj;
	}

	COMPONENT_TYPE getType() const 
	{
		return mType;
	}

protected:
	const  COMPONENT_TYPE mType;
	Obj* mOwnerObj;
};


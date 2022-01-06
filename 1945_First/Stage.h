#pragma once

#include "Game.h"

class Stage
{
public:
	virtual ~Stage() = default;

	virtual void enter() = 0;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;
	virtual void exit() = 0;

	int getOrderNum() const
	{
		return mOrderNum;
	}

protected:
	Stage(int orderNum);
	
	int mOrderNum;
};


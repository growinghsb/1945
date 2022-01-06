#pragma once

#include "Game.h"

class TimeManager
{
public:
	SINGLE(TimeManager);
	
	void init();
	void update(HWND hWnd);

	float getDS() const
	{
		return mDS;
	}

private:
	TimeManager();
	~TimeManager() = default;

	LARGE_INTEGER mFrequency;
	LARGE_INTEGER mPrevCounter;
	LARGE_INTEGER mCurCounter;

	float mDS;
	int	  mFPS;
	int   mSecond;
};


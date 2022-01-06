#pragma once

#include "Game.h"

class InputManager
{
public:
	SINGLE(InputManager);

	void update();

	bool isTic(KEY_LIST key) 
	{
		return mKeyStates[(UINT)key] == KEY_STATE::TIC;
	}

	bool isPress(KEY_LIST key) 
	{
		return mKeyStates[(UINT)key] == KEY_STATE::PRESS;
	}

	bool isBack(KEY_LIST key)
	{
		return mKeyStates[(UINT)key] == KEY_STATE::BACK;
	}

private:
	InputManager();
	~InputManager() = default;

	int mKeyCodeBoard[(UINT)KEY_LIST::END];
	KEY_STATE mKeyStates[(UINT)KEY_LIST::END];
};


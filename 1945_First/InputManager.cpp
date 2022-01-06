#include "InputManager.h"

InputManager::InputManager()
	: mKeyCodeBoard{
'A',
'B',
'C',
'D',
'E',
'F',
'G',
'H',
'I',
'J',
'K',
'L',
'M',
'N',
'O',
'P',
'Q',
'R',
'S',
'T',
'U',
'V',
'W',
'X',
'Y',
'Z',
'0',
'1',
'2',
'3',
'4',
'5',
'6',
'7',
'8',
'9',
VK_ESCAPE,
VK_SPACE,
VK_LEFT,
VK_UP,
VK_RIGHT,
VK_DOWN,
VK_LSHIFT,
VK_LCONTROL,
VK_LMENU,
VK_LBUTTON,
VK_RBUTTON
}
, mKeyStates{}
{
	for (int i = 0; i < (UINT)KEY_LIST::END; ++i)
	{
		mKeyStates[i] = { KEY_STATE::NONE };
	}
}

void InputManager::update()
{
	for (int i = 0; i < (UINT)KEY_LIST::END; ++i)
	{
		if (GetAsyncKeyState(mKeyCodeBoard[i]) & 0x8000)
		{
			if (mKeyStates[i] == KEY_STATE::NONE)
			{
				mKeyStates[i] = KEY_STATE::TIC;
				continue;
			}

			if (mKeyStates[i] == KEY_STATE::TIC)
			{
				mKeyStates[i] = KEY_STATE::PRESS;
				continue;
			}
		}
		else
		{
			if (mKeyStates[i] == KEY_STATE::TIC ||
				mKeyStates[i] == KEY_STATE::PRESS)
			{
				mKeyStates[i] = KEY_STATE::BACK;
			}
			else
			{
				mKeyStates[i] = KEY_STATE::NONE;
			}
		}
	}
}

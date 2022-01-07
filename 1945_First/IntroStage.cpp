#include "IntroStage.h"
#include "InputManager.h"
#include "CoreManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "EventManager.h"
#include "Player.h"
#include "StageManager.h"
#include "TimeManager.h"

extern bool excuteTimer;

IntroStage::IntroStage(int orderNum)
	: Stage(orderNum)
	, mPlayerTextures{}
	, mChoiceOrder(0)
{
	mPlayerTextures.reserve(32);
}

void IntroStage::enter()
{
	excuteTimer = false;
	TimeManager::getInstance()->clear();

	init();
}

void IntroStage::init()
{
	mPlayerTextures = ResourceManager::getInstance()->containsTexture(L"player");
}

void IntroStage::update()
{
	if (IS_TIC(KEY_LIST::RIGHT))
	{
		++mChoiceOrder;
	}

	if (IS_TIC(KEY_LIST::LEFT))
	{
		--mChoiceOrder;
	}

	if (IS_TIC(KEY_LIST::ENTER)) 
	{
		ADD_STAGE_CHANGE(EVENT_TYPE::STAGE_CHANGE, CHANGE_STAGE_TYPE::NEXT);
	}

	if (mChoiceOrder == mPlayerTextures.size())
	{
		mChoiceOrder = (int)mPlayerTextures.size() - 1;
	}

	if (mChoiceOrder < 0)
	{
		mChoiceOrder = 0;
	}
}

void IntroStage::render(HDC backDC)
{
	int startX = 0;
	int x = 0;
	int y = 400;
	POINT res = {};
	RECT choiceWindow = {};

	int interval = WINDOW.right / (int)mPlayerTextures.size();

	HBRUSH curBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, curBrush);

	for (size_t i = 0; i < mPlayerTextures.size(); ++i)
	{
		res = mPlayerTextures[i]->getResolution();
		x = startX + ((interval - res.x) / 2);
		TransparentBlt(backDC, x, y, res.x, res.y, mPlayerTextures[i]->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);

		startX += interval;

		if (i == mChoiceOrder)
		{
			choiceWindow = { x - 10, y - 10, x + res.x + 10, y + res.y + 10 };
			Rectangle(backDC, choiceWindow.left, choiceWindow.top, choiceWindow.right, choiceWindow.bottom);
		}
	}
	SelectObject(backDC, oldBrush);
	DeleteObject(curBrush);
}

void IntroStage::exit()
{
	TimeManager::getInstance()->init();
	excuteTimer = true;

	Texture* texture = mPlayerTextures[mChoiceOrder];
	StageManager::getInstance()->setPlayerTexture(texture);
}

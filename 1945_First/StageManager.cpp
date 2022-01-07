#include "StageManager.h"
#include "IntroStage.h"
#include "PlayStage1.h"

StageManager::StageManager()
	: mStages{}
	, mCurrentStage(nullptr)
	, mPlayerTexture(nullptr)
	, mCurrentPlayer(nullptr)
{
	mStages.reserve(8);

	mStages.push_back(new IntroStage(0));
	mStages.push_back(new PlayStage1(1));

	mCurrentStage = mStages[0];
}

StageManager::~StageManager()
{
	for (auto element : mStages)
	{
		delete element;
	}
	mStages.clear();
}

void StageManager::init()
{
	mCurrentStage->init();
}

void StageManager::update()
{
	mCurrentStage->update();
}

void StageManager::render(HDC backDC)
{
	mCurrentStage->render(backDC);
}

void StageManager::changeStage(CHANGE_STAGE_TYPE type)
{
	mCurrentStage->exit();

	int orderNum = mCurrentStage->getOrderNum();

	switch (type)
	{
	case CHANGE_STAGE_TYPE::INTRO:
		orderNum = 0;
		break;
	case CHANGE_STAGE_TYPE::NEXT:
		orderNum += 1;
		break;
	case CHANGE_STAGE_TYPE::PREV:
		orderNum -= 1;
		break;
	default:
		orderNum = 0;
		break;
	}

	if (orderNum == mStages.size())
	{
		orderNum = (int)mStages.size() - 1;
	}

	if (orderNum < 0)
	{
		orderNum = 0;
	}

	mCurrentStage = mStages[orderNum];
	mCurrentStage->enter();
}


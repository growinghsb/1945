#include "StageManager.h"
#include "IntroStage.h"

StageManager::StageManager()
	: mStages{ new IntroStage(0) }
	, mCurrentStage(mStages[0])
{
	mStages.reserve(16);
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
	for (auto element : mStages) 
	{
		element->init();
	}
}

void StageManager::update()
{
	for (auto element : mStages)
	{
		element->update();
	}
}

void StageManager::render(HDC backDC)
{
	for (auto element : mStages)
	{
		element->render(backDC);
	}
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
	mCurrentStage = mStages[orderNum];
	mCurrentStage->enter();
}


#pragma once

#include "Game.h"

class Stage;

class StageManager
{
public:
	SINGLE(StageManager);

	void init();
	void update();
	void render(HDC backDC);

	void changeStage(CHANGE_STAGE_TYPE type);

private:
	StageManager();
	~StageManager();
	
	vector<Stage*> mStages;
	Stage* mCurrentStage;
};


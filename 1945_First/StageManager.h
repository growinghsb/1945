#pragma once

#include "Game.h"

class Stage;
class Player;
class Texture;

class StageManager
{
public:
	SINGLE(StageManager);

	void init();
	void update();
	void render(HDC backDC);

	void changeStage(CHANGE_STAGE_TYPE type);
	
	void setPlayerTexture(Texture* texture)
	{
		mPlayerTexture = texture;
	}

	void setPlayer(Player* player) 
	{
		mCurrentPlayer = player;
	}

	Texture* getPlayerTexture() const 
	{
		return mPlayerTexture;
	}

	Player* getPlayer() const 
	{
		return mCurrentPlayer;
	}

private:
	StageManager();
	~StageManager();
	
	vector<Stage*> mStages;
	Stage* mCurrentStage;
	Texture* mPlayerTexture;
	Player* mCurrentPlayer;
};


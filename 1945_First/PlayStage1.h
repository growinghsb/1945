#pragma once

#include "Stage.h"

class Layer;
class ObjLayer;

class PlayStage1 :
    public Stage
{
public:
	PlayStage1(int orderNum);
	~PlayStage1();

	virtual void enter() override;
	virtual void init() override;
	virtual void update() override;
	virtual void render(HDC backDC) override;
	virtual void exit() override;

private:
    vector<Layer*> mLayer;
};


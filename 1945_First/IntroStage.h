#pragma once

#include "Stage.h"

class Texture;

class IntroStage
	: public Stage
{
public:
	IntroStage(int orderNum);
	~IntroStage() = default;

	 void enter() override;
	 void init() override;
	 void update() override;
	 void render(HDC backDC) override;
	 void exit() override;

private:
	vector<Texture*> mPlayerTextures;
};


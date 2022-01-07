#pragma once

#include "Layer.h"

class Texture;

class UILayer :
    public Layer
{
public:
	UILayer(Texture* texture);

	virtual void init();
	virtual void update();
	virtual void render(HDC backDC);

private:
	Texture* mLifePointTexture;
};


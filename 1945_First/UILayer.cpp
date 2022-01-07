#include "UILayer.h"
#include "StageManager.h"
#include "Player.h"
#include "Texture.h"
#include "CoreManager.h"

UILayer::UILayer(Texture* texture)
	: mLifePointTexture(texture)
{
}

void UILayer::init()
{
}

void UILayer::update()
{
}

void UILayer::render(HDC backDC)
{
	POINT res = mLifePointTexture->getResolution();
	POINT pos = { 10, WINDOW.bottom - res.y - 10 };

	int count = StageManager::getInstance()->getPlayer()->getLifePointCount();

	for (int i = 0; i < count; ++i)
	{
		TransparentBlt(backDC, pos.x, pos.y, res.x, res.y, mLifePointTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
		
		pos.x += res.x + 10;
	}
}

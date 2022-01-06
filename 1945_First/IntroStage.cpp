#include "IntroStage.h"
#include "InputManager.h"
#include "CoreManager.h"
#include "ResourceManager.h"
#include "Texture.h"

IntroStage::IntroStage(int orderNum)
	: Stage(orderNum)
	, mPlayerTextures{}
{
	mPlayerTextures.reserve(32);
}

void IntroStage::enter()
{
	init();
}

void IntroStage::init()
{
	mPlayerTextures = ResourceManager::getInstance()->containsTexture(L"player");
}

void IntroStage::update()
{
	if (IS_TIC(KEY_LIST::LBUTTON))
	{
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(CoreManager::getInstance()->getHWnd(), &pos);
	}
}

void IntroStage::render(HDC backDC)
{
	int startX = 0;
	int x = 0;
	int y = 400;
	POINT res = {};

	int interval = WINDOW.right / 3;

	for (const auto element : mPlayerTextures)
	{
		res = element->getResolution();
		x = startX + ((interval - res.x) / 2);
		TransparentBlt(backDC, x, y, res.x, res.y, element->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
		
		startX += interval;
	}
}

void IntroStage::exit()
{

}

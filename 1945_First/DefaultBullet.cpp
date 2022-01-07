#include "DefaultBullet.h"
#include "TimeManager.h"
#include "Texture.h"

DefaultBullet::DefaultBullet(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: Obj(tag, pos, scale, texture, layer)
	, mSpeed(700)
	, mOffencePower(2) // 2 - 4 - 6 - 8 ·Î Áõ°¡
{
}

void DefaultBullet::update()
{
	mPos.y -= mSpeed * DS;
}

void DefaultBullet::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.x, (int)mPos.y, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

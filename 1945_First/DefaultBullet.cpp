#include "DefaultBullet.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Component.h"
#include "ObjLayer.h"
#include "EventManager.h"

DefaultBullet::DefaultBullet(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: Obj(tag, pos, scale, texture, layer)
	, mSpeed(700)
	, mOffencePower(2) // 2 - 4 - 6 - 8 ·Î Áõ°¡
{
}

DefaultBullet::~DefaultBullet()
{
	for (auto component : mComponents) 
	{
		delete component;
	}
	mComponents.clear();
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

void DefaultBullet::onCollision(OBJ_TYPE collisionTarget)
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	switch (collisionTarget)
	{
	case OBJ_TYPE::OBSTACLE:
		DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::P_DEFAULT_BULLET, this);
		break;
	default:
		break;
	}
}

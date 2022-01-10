#include "DefaultBullet.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Component.h"
#include "ObjLayer.h"
#include "EventManager.h"
#include "Collider.h"
#include "Player.h"

DefaultBullet::DefaultBullet(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer, float speed, int offencePower, int level, float angle)
	: Obj(tag, pos, scale, texture, layer)
	, mSpeed(speed)
	, mOffencePower(offencePower) // 2 - 4 - 6 - 8 로 증가
	, mCurrentBulletLevel(level) // 1 ~ 4까지
	, mAngle(angle)
{
	setComponent(new Collider(COMPONENT_TYPE::COLLIDER, this, pos, PointF{}, mTexture->getResolution()));
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
	if (mTag == L"playerBullet" || mTag == L"secondPlayerBullet")
	{
		mPos.y -= mSpeed * DS;
	}
	else
	{
		mPos.x += mSpeed * DS * cosf(PI / 180 * mAngle);
		mPos.y += mSpeed * DS * sinf(PI / 180 * mAngle);
	}
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
		if (mTag != L"playerBullet")
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::SP_DEFAULT_BULLET, this);
		}
		else
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::P_DEFAULT_BULLET, this);
		}
		break;
	case OBJ_TYPE::ENEMY:
		if (mTag != L"playerBullet")
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::SP_DEFAULT_BULLET, this);
		}
		else
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::P_DEFAULT_BULLET, this);
		}
		break;
	case OBJ_TYPE::PLAYER:
		if (mTag != L"playerBullet" && mTag != L"secondPlayerBullet")
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::E_DEFAULT_BULLET, this);
		}
		break;
	default:
		break;
	}
}

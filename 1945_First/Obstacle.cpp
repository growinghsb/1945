#include "Obstacle.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Collider.h"
#include "ObjLayer.h"
#include "DefaultBullet.h"
#include "EventManager.h"

Obstacle::Obstacle(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer, int hp, float speed)
	: Obj(tag, pos, scale, texture, layer)
	, mHP(hp)
	, mSpeed(speed)
{
	POINT colScale = { int(mScale.x * 0.7), int(mScale.y * 0.7) };
	PointF offset = { float(mScale.x - colScale.x) / 2, float(mScale.y - colScale.y) / 2 };

	setComponent(new Collider(COMPONENT_TYPE::COLLIDER, this, mPos, offset, colScale));
}

Obstacle::~Obstacle()
{
	for (auto component : mComponents)
	{
		delete component;
	}
	mComponents.clear();
}

void Obstacle::update()
{
	mPos.y += mSpeed * DS;
}

void Obstacle::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.x, (int)mPos.y, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void Obstacle::onCollision(OBJ_TYPE collisionTarget)
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	switch (collisionTarget)
	{
	case OBJ_TYPE::PLAYER:
		DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::OBSTACLE, this);
		break;
	case OBJ_TYPE::P_DEFAULT_BULLET:
	{
		DefaultBullet* bullet = (DefaultBullet*)layer->getObjList(OBJ_TYPE::P_DEFAULT_BULLET).back();
		mHP -= bullet->getOffencePower();

		if (mHP <= 0)
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::OBSTACLE, this);
		}
		break;
	}
	default:
		break;
	}
}

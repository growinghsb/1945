#include "Enemy.h"
#include "Obj.h"
#include "Collider.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ObjLayer.h"
#include "EventManager.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "DefaultBullet.h"

Enemy::Enemy(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: Obj(tag, pos, scale, texture, layer)
	, mSpeed(300.f)
	, mCurrentHP(MAX_HP)
{
	POINT colScale = { int(mScale.x * 0.8), int(mScale.y * 0.5) };
	PointF offset = { float(mScale.x - colScale.x) / 2, float(mScale.y - colScale.y) / 2 };

	setComponent(new Collider(COMPONENT_TYPE::COLLIDER, this, mPos, offset, colScale));
}

Enemy::~Enemy()
{
	for (auto component : mComponents)
	{
		delete component;
	}
	mComponents.clear();
}

void Enemy::update()
{
	if (mPos.y > 20)
	{
		mPos.y -= mSpeed * DS;
	}
	else
	{
		static int second = 0;
		static float ds = 0.f;

		second = TimeManager::getInstance()->getSecond();
		ds += DS;

		if (second % 3 == 0)
		{
			if (ds > 0.15f)
			{
				rudderBullet();
				defaultBullet();
				ds = 0.f;
			}
		}
		else if (second % 4 == 0)
		{
			if (ds > 0.33f)
			{
				nWayBullet();
				ds = 0.f;
			}
		}
		else if (second % 7 == 0) 
		{
			if (ds > 0.49f)
			{
				circleBullet();
				ds = 0.f;
			}
		}
	}
}

void Enemy::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.x, (int)mPos.y, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void Enemy::onCollision(OBJ_TYPE collisionTarget)
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	switch (collisionTarget)
	{
	case OBJ_TYPE::P_DEFAULT_BULLET:

		mCurrentHP -= layer->getBulletOffencePower();
		if (mCurrentHP <= 0)
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::ENEMY, this);
		}
		break;
	default:
		break;
	}
}

void Enemy::defaultBullet()
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	
	PointF pos = { mPos.x, mPos.y + mScale.y / 2 + 20};
	layer->addObj(OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"defaultBullet", pos, res, texture, layer, 600.f, 0, 0, 75));

	pos = { mPos.x + mScale.x, mPos.y + mScale.y / 2 + 20 };
	layer->addObj(OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"defaultBullet", pos, res, texture, layer, 600.f, 0, 0, 105));
}

void Enemy::rudderBullet()
{
	ObjLayer* layer = (ObjLayer*)mLayer;
	PointF pPos = layer->getPlayer()->getPos();

	float x1 = pPos.x - mPos.x;
	float y1 = pPos.y - mPos.y;

	float degree = atan2(y1, x1) * 180 / PI;
	if (degree < 0) degree += 360;

	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	float x = float(mPos.x + ((mScale.x - res.x)) / 2);
	PointF pos = { x, mPos.y + 150 };

	layer->addObj(OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"rudderBullet", pos, res, texture, layer, 600.f, 0, 0, degree));
}

void Enemy::nWayBullet()
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	float x = float(mPos.x + ((mScale.x - res.x)) / 2);
	PointF pos = { x, mPos.y + 150 };

	static float range = 22.5f;
	for (float i = 0; i < 180.f; i += range)
	{
		layer->addObj(OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"nWayBullet", pos, res, texture, layer, 350.f, 0, 0, i));
	}
	range == 22.5f ? range = 11.25 : range = 22.5f;
}

void Enemy::circleBullet()
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	float x = float(mPos.x + ((mScale.x - res.x)) / 2);
	PointF pos = { x, mPos.y + 150 };

	static float range = 18.f;
	for (float i = 0; i < 360.f; i += range)
	{
		layer->addObj(OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"circleBullet", pos, res, texture, layer, 350.f, 0, 0, i));
	}
}

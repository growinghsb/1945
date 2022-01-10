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
	static int second = 0;

	if (mPos.y > 20)
	{
		mPos.y -= mSpeed * DS;
	}
	else if(mTag == L"boss0" || mTag == L"boss1" || mTag == L"boss2")
	{
		static float bossDs = 0.f;

		second = TimeManager::getInstance()->getSecond();
		bossDs += DS;

		if (second % 2 == 0)
		{
			if (bossDs > 0.25f)
			{
				rudderBullet();
				defaultBullet();
				bossDs = 0.f;
			}
		}
		else if (second % 3 == 0)
		{
			if (bossDs > 0.5f)
			{
				nWayBullet();
				bossDs = 0.f;
			}
		}
		else if (second % 5 == 0)
		{
			if (bossDs > 1.f)
			{
				circleBullet();
				bossDs = 0.f;
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
	{
		DefaultBullet* bullet = (DefaultBullet*)layer->getObjList(OBJ_TYPE::P_DEFAULT_BULLET).back();
		mCurrentHP -= bullet->getOffencePower();
		if (mCurrentHP <= 0)
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::ENEMY, this);
		}
	}
	break;
	case OBJ_TYPE::SP_DEFAULT_BULLET:
	{
		DefaultBullet* bullet = (DefaultBullet*)layer->getObjList(OBJ_TYPE::SP_DEFAULT_BULLET).back();
		mCurrentHP -= bullet->getOffencePower();
		if (mCurrentHP <= 0)
		{
			DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::ENEMY, this);
		}
	}
	break;
	default:
		break;
	}
}

void Enemy::defaultBullet()
{
	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();

	PointF pos = { mPos.x, mPos.y + mScale.y / 2 + 20 };
	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"defaultBullet", pos, res, texture, mLayer, 600.f, 0, 0, 90));

	pos = { mPos.x + mScale.x, mPos.y + mScale.y / 2 + 20 };
	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"defaultBullet", pos, res, texture, mLayer, 600.f, 0, 0, 90));
}

void Enemy::rudderBullet()
{
	ObjLayer* layer = (ObjLayer*)mLayer;
	PointF pPos = layer->getPlayer()->getPos();

	float x1 = pPos.x - mPos.x;
	float y1 = pPos.y - mPos.y;

	float degree = atan2(y1, x1) * 180 / PI;
	if (degree < 0) degree += 360.f;

	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	float x = float(mPos.x + ((mScale.x - res.x)) / 2);
	PointF pos = { x, mPos.y + mScale.y / 2 };

	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"rudderBullet", pos, res, texture, mLayer, 500.f, 0, 0, degree + 7.5f));
}

void Enemy::nWayBullet()
{
	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	float x = float(mPos.x + ((mScale.x - res.x)) / 2);
	PointF pos = { x, mPos.y + mScale.y / 2 };

	float angle = 22.5f;
	for (float i = 0; i < 180.f; i += angle)
	{
		CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"nWayBullet", pos, res, texture, mLayer, 330.f, 0, 0, i));
	}
	angle == 22.5f ? angle = 11.25 : angle = 22.5f;
}

void Enemy::circleBullet()
{
	Texture* texture = FIND_TEXTURE(L"bullet0");
	POINT res = texture->getResolution();
	float x = float(mPos.x + ((mScale.x - res.x)) / 2);
	PointF pos = { x, mPos.y + mScale.y / 2 };

	enum { ANGLE = 18 };
	for (int i = 0; i < 360; i += ANGLE)
	{
		CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::E_DEFAULT_BULLET, new DefaultBullet(L"circleBullet", pos, res, texture, mLayer, 300.f, 0, 0, float(i)));
	}
}

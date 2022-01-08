#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CoreManager.h"
#include "Texture.h"
#include "ObjLayer.h"
#include "DefaultBullet.h"
#include "ResourceManager.h"
#include "Component.h"
#include "Collider.h"
#include "EventManager.h"
#include "Obj.h"

Player::Player(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: Obj(tag, pos, scale, texture, layer)
	, mLifePointCount(5)
	, mSpeed(450.f)
{
	// 충돌체 컴포넌트 추가
	POINT colScale = { int(mScale.x * 0.5), int(mScale.y * 0.7) };
	PointF offset = { float(mScale.x - colScale.x) / 2, float(mScale.y - colScale.y) / 2 };
	setComponent(new Collider(COMPONENT_TYPE::COLLIDER, this, pos, offset, colScale));
}

Player::~Player()
{
	for (auto component : mComponents)
	{
		delete component;
	}
	mComponents.clear();
}

void Player::update()
{
	if (IS_PRESS(KEY_LIST::TOP))
	{
		mPos.y -= mSpeed * DS;

		if (mPos.y < 0)
		{
			mPos.y = 0;
		}
	}
	if (IS_PRESS(KEY_LIST::BOTTOM))
	{
		mPos.y += mSpeed * DS;

		if (mPos.y + mScale.y > WINDOW.bottom)
		{
			mPos.y = (float)WINDOW.bottom - mScale.y;
		}
	}

	if (IS_PRESS(KEY_LIST::LEFT))
	{
		mPos.x -= mSpeed * DS;

		if (mPos.x < 0)
		{
			mPos.x = 0;
		}
	}

	if (IS_PRESS(KEY_LIST::RIGHT))
	{
		mPos.x += mSpeed * DS;

		if (mPos.x + mScale.x > WINDOW.right)
		{
			mPos.x = (float)WINDOW.right - mScale.x;
		}
	}

	static float regen = 0.f;
	regen += DS;

	if (IS_PRESS(KEY_LIST::SPACE))
	{
		if (regen > 0.06f)
		{
			ObjLayer* layer = (ObjLayer*)mLayer;
			layer->createBullet();
			regen = 0.f;
		}
	}
}

void Player::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.x, (int)mPos.y, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void Player::onCollision(OBJ_TYPE collisionTarget)
{
	// 플레이어가 다른 오브젝트와 충돌 했을 때
	switch (collisionTarget)
	{
	case OBJ_TYPE::OBSTACLE:
		collisionObstacle();
		break;
	case OBJ_TYPE::E_DEFAULT_BULLET:
		collisionObstacle();
	default:
		break;
	}
}

void Player::collisionObstacle()
{
	--mLifePointCount;

	if (0 == mLifePointCount)
	{
		ADD_STAGE_CHANGE(EVENT_TYPE::STAGE_CHANGE, CHANGE_STAGE_TYPE::INTRO);
	}
}



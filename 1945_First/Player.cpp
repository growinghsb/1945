#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "CoreManager.h"
#include "Texture.h"
#include "ObjLayer.h"
#include "DefaultBullet.h"
#include "ResourceManager.h"

Player::Player(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: Obj(tag, pos, scale, texture, layer)
	, mLifePoint(3)
	, mSpeed(450.f)
{
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
			createBullet();
			regen = 0.f;
		}
	}
}

void Player::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.x, (int)mPos.y, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void Player::createBullet()
{
	Texture* texture = nullptr;
	POINT res = {};
	float x = 0.f;
	PointF pos = {};

	if (mTexture->getTag() == L"player1")
	{
		texture = ResourceManager::getInstance()->findTexture(L"bullet1-1");
	}
	else 
	{
		texture = ResourceManager::getInstance()->findTexture(L"bullet2-1");
	}

	res = texture->getResolution();
	x = float(mPos.x + ((mScale.x - res.x)) / 2);
	pos = { x, mPos.y };

	DefaultBullet* bullet = new DefaultBullet(L"playerBullet", pos, res, texture, mLayer);
	
	// 총알 생성 후 오브젝트 레이어에 저장
	ObjLayer* layer = (ObjLayer*)mLayer;
	layer->addObj(OBJ_TYPE::P_DEFAULT_BULLET, bullet);
}

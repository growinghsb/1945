#include "Item.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Player.h"
#include "ObjLayer.h"
#include "Collider.h"
#include "EventManager.h"

Item::Item(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: Obj(tag, pos, scale, texture, layer)
	, mSpeed(200)
{
	setComponent(new Collider(COMPONENT_TYPE::COLLIDER, this, mPos, PointF{}, mTexture->getResolution()));
}

Item::~Item()
{
	for (auto component : mComponents)
	{
		delete component;
	}
	mComponents.clear();
}

void Item::update()
{
	mPos.y += mSpeed * DS;
}

void Item::render(HDC backDC)
{
	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.x, (int)mPos.y, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void Item::onCollision(OBJ_TYPE collisionTarget)
{
	ObjLayer* layer = (ObjLayer*)mLayer;

	switch (collisionTarget)
	{
	case OBJ_TYPE::PLAYER:
		applyItem(layer);
		DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::ITEM, this);
		break;
	default:
		break;
	}
}

void Item::applyItem(ObjLayer* layer)
{
	// 플레이어 생명 증가
	if (mTexture->getTag() == L"item0")
	{
		Player* player = layer->getPlayer();
		player->increaseLifePointCount();
	}

	// 총알 업그레이드
	if (mTexture->getTag() == L"item1")
	{
		layer->bulletUpgrade();
	}
}

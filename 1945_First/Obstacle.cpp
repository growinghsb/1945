#include "Obstacle.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Collider.h"
#include "ObjLayer.h"
#include "DefaultBullet.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "Item.h"

Obstacle::Obstacle(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer, int hp, float speed)
	: Obj(tag, pos, scale, texture, layer)
	, mHP(hp)
	, mSpeed(speed)
{
	POINT colScale = { int(mScale.x * 0.8), int(mScale.y * 0.8) };
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
		isDie();

		break;
	}
	default:
		break;
	}
}

void Obstacle::isDie()
{
	if (mHP <= 0)
	{
		if (rand() % 4 == 0)
		{
			createItem();
		}
		DELETE_OBJ(EVENT_TYPE::DELETE_OBJ, OBJ_TYPE::OBSTACLE, this);
	}
}

void Obstacle::createItem()
{
	enum { ITEM_COUNT = 2 };

	wstring tag(L"item");
	tag += to_wstring(rand() % ITEM_COUNT);
	Texture* texture = FIND_TEXTURE(tag.c_str());

	POINT res = texture->getResolution();

	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::ITEM, new Item(L"item", PointF{ mPos.x, mPos.y - 30 }, res, texture, mLayer));
}

#include "ObjLayer.h"
#include "Obj.h"
#include "Player.h"
#include "StageManager.h"
#include "Texture.h"
#include "CoreManager.h"
#include "Obstacle.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Component.h"
#include "InputManager.h"
#include "EventManager.h"
#include "DefaultBullet.h"
#include "Enemy.h"

static bool bossRegen = true;

ObjLayer::ObjLayer()
	: mObjs{}
	, isRender(true)
	, mBulletLevel(1)
	, mBulletOffencePower(2)
{
}

ObjLayer::~ObjLayer()
{
	bossRegen = true;

	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (auto& element : mObjs[i])
		{
			delete element;
		}
		mObjs[i].clear();
	}
}

void ObjLayer::init()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (const auto element : mObjs[i])
		{
			element->init();
		}
	}
}

void ObjLayer::update()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (const auto element : mObjs[i])
		{
			element->update();
		}
	}

	deleteInvalidObj(OBJ_TYPE::P_DEFAULT_BULLET); // 유효하지 않은 범위의 플레이어 총알 삭제
	deleteInvalidObj(OBJ_TYPE::OBSTACLE);		  // 유효하지 않은 범위의 장애물 삭제
	deleteInvalidObj(OBJ_TYPE::E_DEFAULT_BULLET); // 유효하지 않은 범위의 적 총알 삭제

	createObstacle(); // 장애물 생성

	if (TimeManager::getInstance()->getSecond() > 3 && bossRegen)
	{
		createBoss();
		bossRegen = false;
	}

	// 충돌체 업데이트 진행
	colliderUpdate();
}

void ObjLayer::render(HDC backDC)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (const auto element : mObjs[i])
		{
			element->render(backDC);
		}
	}

	if (IS_TIC(KEY_LIST::_1))
	{
		isRender ? isRender = false : isRender = true;
	}

	if (isRender)
	{
		// 충돌체 렌더링 진행
		colliderRender(backDC);
	}
}

void ObjLayer::deleteObj(OBJ_TYPE type, Obj* targetObj)
{
	auto& list = mObjs[(UINT)type];

	auto iter = list.begin();
	auto endIter = list.end();

	while (iter != endIter)
	{
		if ((*iter) == targetObj)
		{
			delete (*iter);
			list.erase(iter);

			return;
		}
		else
		{
			++iter;
		}
	}
}

void ObjLayer::bulletUpgrade()
{
	// 모든 불릿 텍스처 변경 후 공격력 증가 함수 호출
	auto& list = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET];

	if (list.empty())
	{
		mBulletOffencePower += 2;
		++mBulletLevel;
	}
	else
	{
		wstring tag(L"bullet");
		DefaultBullet* bullet = (DefaultBullet*)list.back();

		if (!bullet->isMaxBulletLevel())
		{
			if (getPlayer()->getTag() == L"player1")
			{
				tag += L"1-";
				tag += to_wstring(++mBulletLevel);
			}
			else
			{
				tag += L"2-";
				tag += to_wstring(++mBulletLevel);
			}

			Texture* texture = FIND_TEXTURE(tag.c_str());

			mBulletOffencePower += 2;

			for (auto element : list)
			{
				bullet = (DefaultBullet*)element;

				bullet->changeTexture(texture);
				bullet->setOffencePowerUp(mBulletOffencePower);
				bullet->setBulletLevel(mBulletLevel);
			}
		}
	}
}

void ObjLayer::createObstacle()
{
	static float regen = 0.f;
	regen += DS;

	if (regen > 0.8f)
	{
		enum { OBSTACLE_COUNT = 2 };

		wstring tag(L"obstacle");
		tag += to_wstring(rand() % OBSTACLE_COUNT);
		Texture* texture = FIND_TEXTURE(tag.c_str());

		POINT res = texture->getResolution();
		float x = float(rand() % (WINDOW.right - 100));
		PointF pos = { x, 0 };
		int hp = rand() % 20 + 10;
		float speed = float(rand() % 300 + 250);

		CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::OBSTACLE, new Obstacle(L"obstacle", pos, res, texture, this, hp, speed));

		regen = 0.f;
	}
}

void ObjLayer::createBoss()
{
	wstring tag(L"boss0");
	Texture* texture = FIND_TEXTURE(tag.c_str());

	POINT res = texture->getResolution();
	float x = float(WINDOW.right - res.x) / 2;
	PointF pos = { x, float(WINDOW.bottom + 5) };

	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::ENEMY, new Enemy(texture->getTag(), pos, res, texture, this));
}

void ObjLayer::createBullet()
{
	Texture* texture = nullptr;
	POINT res = {};
	float x = 0.f;
	PointF pos = {};

	wstring tag(L"bullet");
	list<Obj*>& bulletList = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET];

	if (bulletList.empty())
	{
		if (getPlayer()->getTag() == L"player1")
		{
			tag += L"1-";
			tag += to_wstring(mBulletLevel);
			texture = FIND_TEXTURE(tag.c_str());
		}
		else
		{
			tag += L"2-";
			tag += to_wstring(mBulletLevel);
			texture = FIND_TEXTURE(tag.c_str());
		}
	}
	else
	{
		if (getPlayer()->getTag() == L"player1")
		{
			tag += L"1-";
			tag += to_wstring(mBulletLevel);
			texture = FIND_TEXTURE(tag.c_str());
		}
		else
		{
			tag += L"2-";
			tag += to_wstring(mBulletLevel);
			texture = FIND_TEXTURE(tag.c_str());
		}
	}
	res = texture->getResolution();
	x = float(getPlayer()->getPos().x + ((getPlayer()->getScale().x - res.x)) / 2);
	pos = { x, getPlayer()->getPos().y };

	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::P_DEFAULT_BULLET, new DefaultBullet(L"playerBullet", pos, res, texture, this, 800.f, mBulletOffencePower, mBulletLevel, 0.f));
}

void ObjLayer::colliderUpdate()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (const auto element : mObjs[i])
		{
			vector<Collider*> components = element->getColliderVector();

			for (const auto component : components)
			{
				component->update();
			}
		}
	}
}

void ObjLayer::colliderRender(HDC backDC)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (const auto element : mObjs[i])
		{
			vector<Collider*> components = element->getColliderVector();

			for (const auto component : components)
			{
				component->render(backDC);
			}
		}
	}
}

void ObjLayer::deleteInvalidObj(OBJ_TYPE type)
{
	auto& list = mObjs[(UINT)type];

	auto iter = list.begin();
	auto endIter = list.end();

	while (iter != endIter)
	{
		if (type == OBJ_TYPE::E_DEFAULT_BULLET)
		{
			if ((*iter)->isValidDown() &&
				(*iter)->isValidUp() && 
				(*iter)->getPos().x < WINDOW.right &&
				(*iter)->getPos().y < WINDOW.bottom)
			{
				++iter;
				continue;
			}
		}
		else
		{
			if ((*iter)->isValidUp())
			{
				++iter;
				continue;
			}
		}
		delete (*iter);
		iter = list.erase(iter);
		endIter = list.end();
	}
}
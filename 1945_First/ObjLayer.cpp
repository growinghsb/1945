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
		if (i == (UINT)OBJ_TYPE::ENEMY)
		{
			mObjs[i].size() == 0 ? bossRegen = true : bossRegen = false;
		}
		for (const auto element : mObjs[i])
		{
			element->update();
		}
	}

	// 세컨드 플레이어 위치 업데이트
	Player* player = getPlayer();
	PointF pPos = player->getPos();
	POINT pScale = player->getScale();

	float x = (float)-pScale.x;
	float y = pPos.y + pScale.y + 20;

	for (const auto element : mObjs[(UINT)OBJ_TYPE::SECOND_PLAYER])
	{
		element->changePos(PointF{ pPos.x + x, y });
		x *= -1.f;
	}

	// 오브젝트 삭제
	deleteInvalidObj(OBJ_TYPE::P_DEFAULT_BULLET);
	deleteInvalidObj(OBJ_TYPE::OBSTACLE);
	deleteInvalidObj(OBJ_TYPE::E_DEFAULT_BULLET);
	deleteInvalidObj(OBJ_TYPE::SP_DEFAULT_BULLET);

	// 장애물 생성
	createObstacle();

	// 보스생성
	if (bossRegen)
	{
		if (mBulletLevel == MAX_BULLET_LEVEL)
		{
			createBoss();
			bossRegen = false;
		}
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

	// 충돌체를 껐다 켰다 할 수 있는 옵션
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

// 모든 불릿 텍스처 변경 후 공격력 증가 함수 호출
void ObjLayer::bulletUpgrade()
{
	auto& list = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET];

	if (list.empty())
	{
		if (mBulletLevel != MAX_BULLET_LEVEL)
		{
			mBulletOffencePower += 2;
			++mBulletLevel;
		}
	}
	else
	{
		wstring tag(L"bullet");
		DefaultBullet* bullet = (DefaultBullet*)list.back();

		if (mBulletLevel != MAX_BULLET_LEVEL)
		{
			if (getPlayer()->getTag() == L"player1")
			{
				tag += L"1-";
			}
			else
			{
				tag += L"2-";
			}

			mBulletOffencePower += 2;
			tag += to_wstring(++mBulletLevel);
			Texture* texture = FIND_TEXTURE(tag.c_str());

			for (auto element : list)
			{
				bullet = (DefaultBullet*)element;

				bullet->changeTexture(texture);
				bullet->setBulletLevel(mBulletLevel);
				bullet->setOffencePowerUp(mBulletOffencePower);
			}
		}
		else
		{
			if (mObjs[(UINT)OBJ_TYPE::SECOND_PLAYER].size() != MAX_SECOND_PLAYER_COUNT)
			{
				Player* player = getPlayer();
				PointF pPos = player->getPos();
				POINT pScale = player->getScale();

				float x = 0.f;
				if (mObjs[(UINT)OBJ_TYPE::SECOND_PLAYER].empty())
				{
					x = pPos.x - pScale.x;
				}
				else
				{
					x = pPos.x + pScale.x;
				}
				CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::SECOND_PLAYER, new Player(L"secondPlayer", PointF{ x, pPos.y + pScale.y + 20 }, pScale, player->getTexture(), this));
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
	static int bossCount = 0;

	wstring tag(L"boss");
	tag += to_wstring(bossCount);
	Texture* texture = FIND_TEXTURE(tag.c_str());

	POINT res = texture->getResolution();
	float x = float(WINDOW.right - res.x) / 2;
	PointF pos = { x, float(WINDOW.bottom + 5) };

	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::ENEMY, new Enemy(texture->getTag(), pos, res, texture, this));
	
	if (bossCount != 2) 
	{
		++bossCount;
	}
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
		}
		else
		{
			tag += L"2-";
		}
	}
	else
	{
		if (getPlayer()->getTag() == L"player1")
		{
			tag += L"1-";
		}
		else
		{
			tag += L"2-";
		}
	}
	tag += to_wstring(mBulletLevel);
	texture = FIND_TEXTURE(tag.c_str());

	res = texture->getResolution();
	x = float(getPlayer()->getPos().x + ((getPlayer()->getScale().x - res.x)) / 2);
	pos = { x, getPlayer()->getPos().y };

	CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::P_DEFAULT_BULLET, new DefaultBullet(L"playerBullet", pos, res, texture, this, 800.f, mBulletOffencePower, mBulletLevel, 0.f));
}

void ObjLayer::createSecondPlayerBullet()
{
	if (!mObjs[(UINT)OBJ_TYPE::SECOND_PLAYER].empty())
	{
		Texture* texture = nullptr;
		POINT res = {};
		float x = 0.f;
		PointF pos = {};

		for (const auto& element : mObjs[(UINT)OBJ_TYPE::SECOND_PLAYER])
		{
			texture = FIND_TEXTURE(L"secondBullet");

			x = float(element->getPos().x + ((element->getScale().x - res.x)) / 2);
			pos = { x, element->getPos().y };

			CREATE_OBJ(EVENT_TYPE::CREATE_OBJ, OBJ_TYPE::SP_DEFAULT_BULLET, new DefaultBullet(L"secondPlayerBullet", pos, res, texture, this, 550.f, 3, 0, 0.f));
		}
	}
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
		if ((*iter)->isValidLeft()  &&
			(*iter)->isValidTop()	&&
			(*iter)->isValidRight() &&
			(*iter)->isValidBottom())
		{
			++iter;
		}
		else
		{
			delete (*iter);
			iter = list.erase(iter);
			endIter = list.end();
		}
	}
}
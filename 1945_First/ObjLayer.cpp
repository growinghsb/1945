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

ObjLayer::ObjLayer()
	: mObjs{}
	, isRender(true)
{
}

ObjLayer::~ObjLayer()
{
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
	createObstacle();

	deleteObj(OBJ_TYPE::P_DEFAULT_BULLET); // 유효하지 않은 범위의 플레이어 총알 삭제
	deleteObj(OBJ_TYPE::OBSTACLE); // 유효하지 않은 범위의 장애물 삭제

	// 충돌체 업데이트 진행
	colliderUpdate();

	// 오브젝트간 충돌체크 진행
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

void ObjLayer::createObstacle()
{
	static float regen = 0.f;
	regen += DS;

	if (regen > 0.8f)
	{
		wstring tag(L"obstacle");
		tag += to_wstring(rand() % 3);
		Texture* texture = FIND_TEXTURE(tag.c_str());

		POINT res = texture->getResolution();
		float x = float(rand() % (WINDOW.right - 100));
		PointF pos = { x, 0 };
		int hp = rand() % 20 + 10;
		float speed = float(rand() % 300 + 250);

		mObjs[(UINT)OBJ_TYPE::OBSTACLE].push_back(new Obstacle(L"obstacle", pos, res, texture, this, hp, speed));

		regen = 0.f;
	}
}

void ObjLayer::colliderUpdate()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		for (const auto element : mObjs[i])
		{
			vector<Component*> components = element->getComponents(COMPONENT_TYPE::COLIIDER);

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
			vector<Component*> components = element->getComponents(COMPONENT_TYPE::COLIIDER);

			for (const auto component : components)
			{
				component->render(backDC);
			}
		}
	}
}

void ObjLayer::deleteObj(OBJ_TYPE type)
{
	auto iter = mObjs[(UINT)type].begin();
	auto endIter = mObjs[(UINT)type].end();

	while (iter != endIter)
	{
		if ((*iter)->isValidUp())
		{
			++iter;
		}
		else
		{
			delete (*iter);
			iter = mObjs[(UINT)type].erase(iter);
			endIter = mObjs[(UINT)type].end();
		}
	}
}





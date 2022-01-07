#include "ObjLayer.h"
#include "Obj.h"
#include "Player.h"
#include "StageManager.h"

ObjLayer::ObjLayer()
	: mObjs{}
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
	deleteBullet(); // 유효하지 않은 범위의 총알 삭제
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
}

void ObjLayer::createObstacle()
{
}

void ObjLayer::deleteBullet()
{
	auto iter = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET].begin();
	auto endIter = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET].end();

	while (iter != endIter) 
	{
		if ((*iter)->getPos().y < 0) 
		{
			delete (*iter);
			iter = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET].erase(iter);
			endIter = mObjs[(UINT)OBJ_TYPE::P_DEFAULT_BULLET].end();
		}
		else 
		{
			++iter;
		}
	}
}



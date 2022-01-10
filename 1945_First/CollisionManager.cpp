#include "CollisionManager.h"
#include "Obj.h"
#include "ObjLayer.h"
#include "Collider.h"
#include "Component.h"

CollisionManager::CollisionManager()
	: mCollisionTargets{}
{
	mCollisionTargets.reserve(8);

	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::PLAYER, OBJ_TYPE::OBSTACLE });
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM });
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::PLAYER, OBJ_TYPE::E_DEFAULT_BULLET });
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::P_DEFAULT_BULLET, OBJ_TYPE::ENEMY });
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::P_DEFAULT_BULLET, OBJ_TYPE::OBSTACLE });
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::SP_DEFAULT_BULLET, OBJ_TYPE::ENEMY });
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::SP_DEFAULT_BULLET, OBJ_TYPE::OBSTACLE });
}

void CollisionManager::update(ObjLayer* layer)
{
	for (auto colGroup : mCollisionTargets)
	{
		list<Obj*>& objList1 = layer->getObjList(colGroup.obj1);
		list<Obj*>& objList2 = layer->getObjList(colGroup.obj2);

		for (auto obj1 : objList1)
		{
			vector<Collider*> colVec1 = obj1->getColliderVector();

			for (auto obj2 : objList2)
			{
				vector<Collider*> colVec2 = obj2->getColliderVector();

				if (isCollision(colVec1, colVec2))
				{
					obj1->onCollision(colGroup.obj2);
					obj2->onCollision(colGroup.obj1);
				}
			}
		}
	}
}

bool CollisionManager::isCollision(vector<Collider*>& colVec1, vector<Collider*>& colVec2)
{
	for (auto col1 : colVec1)
	{
		for (auto col2 : colVec2)
		{
			if (col1->isCollision(col2))
			{
				return true;
			}
		}
	}
	return false;
}
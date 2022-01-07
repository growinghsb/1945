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
	mCollisionTargets.push_back(CollisionGroup{ OBJ_TYPE::P_DEFAULT_BULLET, OBJ_TYPE::OBSTACLE });
}

void CollisionManager::update(ObjLayer* layer)
{
	
}

bool CollisionManager::isCollision(vector<Collider*>& colVec1, vector<Collider*>& colVec2)
{
	return false;
}


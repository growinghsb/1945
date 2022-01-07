#pragma once

#include "Game.h"

class Obj;
class ObjLayer;
class Component;
class Collider;

class CollisionManager
{
public:
	SINGLE(CollisionManager);

	CollisionManager();

	void update(ObjLayer* layer);

private:
	bool isCollision(vector<Collider*>& colVec1, vector<Collider*>& colVec2);
	
	vector<CollisionGroup> mCollisionTargets;
};


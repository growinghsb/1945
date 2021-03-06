#pragma once

#include "Layer.h"

class Obj;
class Player;

class ObjLayer :
	public Layer
{
public:
	ObjLayer();
	~ObjLayer();

	void init() override;
	void update() override;
	void render(HDC backDC) override;

	void deleteObj(OBJ_TYPE type, Obj* targetObj);
	void addObj(OBJ_TYPE type, Obj* obj)
	{
		mObjs[(UINT)type].push_back(obj);
	}


	Player* getPlayer() const
	{
		return (Player*)mObjs[(UINT)OBJ_TYPE::PLAYER].front();
	}

	list<Obj*>& getObjList(OBJ_TYPE type)
	{
		return mObjs[(UINT)type];
	}

	void bulletUpgrade();
	void createBullet();
	void createSecondPlayerBullet();

	int getBulletOffencePower() 
	{
		return mBulletOffencePower;
	}

private:
	void createObstacle();
	void createBoss();
	void deleteInvalidObj(OBJ_TYPE type);
	void colliderUpdate();
	void colliderRender(HDC backDC);

	list<Obj*> mObjs[(UINT)OBJ_TYPE::END];
	bool isRender;

	enum {MAX_BULLET_LEVEL = 4, MAX_SECOND_PLAYER_COUNT = 2};
	int mBulletLevel;
	int mBulletOffencePower;
};


#pragma once

#include "Obj.h"

class Obstacle :
	public Obj
{
public:
	Obstacle(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer, int hp, float speed);
	~Obstacle();

	void update() override;
	void render(HDC backDC) override;
	void onCollision(OBJ_TYPE collisionTarget) override;

	void decreaseHP(int offencePower)
	{
		mHP -= offencePower;
	}

	void isDie();

private:
	void createItem();

	int mHP;
	float mSpeed;
};


#pragma once

#include "Component.h"

class Collider :
	public Component
{
public:
	Collider(COMPONENT_TYPE type, Obj* owner, PointF pos, PointF offset, POINT scale);
	~Collider() = default;

	void update() override;
	void render(HDC backDC) override;

	RECT getCollider() const
	{
		return RECT{ int(mPos.x), int(mPos.y), int(mPos.x + mScale.x), int(mPos.y + mScale.y) };
	}

	bool isCollision(Collider* target)
	{
		if (mPos.x			  < target->mPos.x + target->mScale.x &&
			mPos.x + mScale.x > target->mPos.x &&
			mPos.y			  < target->mPos.y + target->mScale.y &&
			mPos.y + mScale.y > target->mPos.y)
		{
			return true;
		}
		return false;

	/*	float xDist = abs(mPos.x - target->mPos.x);

		if (xDist > mScale.x / 2 + target->mScale.y / 2)
		{
			return false;
		}

		float yDist = abs(mPos.y - target->mPos.y);

		if (yDist > mScale.y / 2 + target->mScale.y / 2)
		{
			return false;
		}

		return true;*/
	}

private:
	PointF mPos;
	PointF mOffset;
	POINT mScale;
};


#pragma once

struct PointF
{
	float x;
	float y;

	PointF operator +(const PointF rhs)
	{
		return PointF{ x + rhs.x, y + rhs.y };
	}
};

struct EventInfo
{
	EVENT_TYPE mType;
	DWORD_PTR mLow;
	DWORD_PTR mHigh;
};

struct CollisionGroup 
{
	OBJ_TYPE obj1;
	OBJ_TYPE obj2;
};
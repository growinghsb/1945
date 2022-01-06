#pragma once

struct PointF
{
	float x;
	float y;
};

struct EventInfo
{
	EVENT_TYPE mType; 
	DWORD_PTR mLow;
	DWORD_PTR mHigh;
};
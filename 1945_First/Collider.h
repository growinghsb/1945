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

private:
	PointF mPos;
	PointF mOffset;
	POINT mScale;
};


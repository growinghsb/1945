#include "Collider.h"
#include "Obj.h"

Collider::Collider(COMPONENT_TYPE type, Obj* owner, PointF pos, PointF offset, POINT scale)
	: Component(type, owner)
	, mPos(pos)
	, mOffset(offset)
	, mScale(scale)
{
}

void Collider::update()
{
	mPos = mOwnerObj->getPos() + mOffset;
}

void Collider::render(HDC backDC)
{
	HBRUSH curBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(backDC, curBrush);

	Rectangle(backDC, (int)mPos.x, (int)mPos.y, (int)mPos.x + mScale.x, (int)mPos.y + mScale.y);

	SelectObject(backDC, oldBrush);
	DeleteObject(curBrush);
}

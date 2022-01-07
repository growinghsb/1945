#include "Obj.h"
#include "CoreManager.h"
#include "Component.h"
#include "Collider.h"

Obj::Obj(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: mTag(tag)
	, mPos(pos)
	, mScale(scale)
	, mTexture(texture)
	, mLayer(layer)
	, mComponents{}
{
	mComponents.reserve(4);
}

vector<Collider*> Obj::getColliderVector()
{
	vector<Collider*> comps;
	comps.reserve(4);

	for (auto element : mComponents)
	{
		if (element->getType() == COMPONENT_TYPE::COLLIDER)
		{
			comps.push_back((Collider*)element);
		}
	}
	return comps;
}

bool Obj::isValidDown()
{
	return mPos.y < WINDOW.bottom;
}
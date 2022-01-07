#include "Obj.h"
#include "CoreManager.h"
#include "Component.h"

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

vector<Component*> Obj::getComponents(COMPONENT_TYPE type)
{
	vector<Component*> comps;
	comps.reserve(4);

	for (auto element : mComponents)
	{
		if (element->getType() == type)
		{
			comps.push_back(element);
		}
	}
	return comps;
}

bool Obj::isValidDown()
{
	return mPos.y < WINDOW.bottom;
}
#include "Obj.h"

Obj::Obj(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer)
	: mTag(tag)
	, mPos(pos)
	, mScale(scale)
	, mTexture(texture)
	, mLayer(layer)
{
}

#pragma once

#include "Game.h"

class Texture;
class Layer;

class Obj
{
public:
	virtual ~Obj() = default;

	virtual void init() {};
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;

	const wstring& getTag() const 
	{
		return mTag;
	}

	PointF getPos() const
	{
		return mPos;
	}

	POINT getScale() const 
	{
		return mScale;
	}

	void changeTexture(Texture* texture) 
	{
		mTexture = texture;
	}

protected:
	Obj(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);

	const wstring mTag;
	PointF mPos;
	POINT mScale;
	Texture* mTexture;
	Layer* mLayer;
};


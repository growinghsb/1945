#pragma once
#include "CResource.h"

class Texture :
	public CResource
{
public:
	Texture(wstring tag);
	~Texture();

	bool load(wstring path) override;

	HDC getTextureDC() const
	{
		return mTextureDC;
	}

	POINT getResolution() const
	{
		return mResolution;
	}

private:
	HDC mTextureDC;
	HBITMAP mTextureBitmap;
	POINT mResolution;
};


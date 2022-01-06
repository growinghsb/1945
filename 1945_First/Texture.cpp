#include "Texture.h"
#include "CoreManager.h"

Texture::Texture(wstring tag)
	: CResource(tag)
	, mTextureDC(nullptr)
	, mTextureBitmap(nullptr)
	, mResolution{}
{
	mTextureDC = CreateCompatibleDC(CoreManager::getInstance()->getMainDC());
}

Texture::~Texture()
{
	DeleteDC(mTextureDC);
	DeleteObject(mTextureBitmap);
}

bool Texture::load(wstring path)
{
	path += L"\\" + mTag + L".bmp";
	mTextureBitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
	
	if(nullptr == mTextureBitmap)
	{
		return false;
	}

	BITMAP info = {};
	GetObject(mTextureBitmap, sizeof(BITMAP), &info);

	mResolution.x = info.bmWidth;
	mResolution.y = info.bmHeight;

	HBITMAP oldBitmap = (HBITMAP)SelectObject(mTextureDC, mTextureBitmap);
	DeleteObject(oldBitmap);

	return true;
}

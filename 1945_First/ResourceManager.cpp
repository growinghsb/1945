#include "ResourceManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
	: mResources{}
	, mAbsolutePath{}
{
	setAbsolutePath();
	setTextureNames();
}

ResourceManager::~ResourceManager()
{
	for (auto element : mResources)
	{
		delete element.second;
	}
	mResources.clear();
}

void ResourceManager::init()
{
	loadTexture();
}

void ResourceManager::loadTexture()
{
	for (const auto& element : mFileList) 
	{
		Texture* texture = new Texture(element.c_str());

		if (texture->load(mAbsolutePath)) 
		{
			mResources.insert(make_pair(element, texture));
		}
	}
}

void ResourceManager::setAbsolutePath()
{
	enum { LENGTH = 256 };
	mAbsolutePath.reserve(LENGTH);

	wchar_t path[LENGTH] = {};
	GetCurrentDirectory(LENGTH, path);

	int len = (int)wcslen(path);

	for (int i = len - 1; i >= 0; --i)
	{
		if ('\\' == path[i])
		{
			path[i] = '\0';
			break;
		}
	}
	mAbsolutePath = path;
	mAbsolutePath += L"\\texture";
}

void ResourceManager::setTextureNames()
{
	enum { TEXTURE_COUNT = 256 };
	mFileList.reserve(TEXTURE_COUNT);

	WIN32_FIND_DATAW data = {};
	wstring path = mAbsolutePath;
	path += L"\\*";

	HANDLE handle = FindFirstFileW(path.c_str(), &data);

	while (FindNextFileW(handle, &data))
	{
		if ((data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) &&
			!(data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
		{
			wstring name = data.cFileName;
			mFileList.push_back(name.substr(0, name.rfind('.')));
		}
	}
	FindClose(handle);
}

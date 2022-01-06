#pragma once

#include "Game.h"

class CResource;
class Texture;

class ResourceManager
{
public:
	SINGLE(ResourceManager);

	ResourceManager();
	~ResourceManager();

	void init();

	Texture* findTexture(const wchar_t* tag) const
	{
		auto iter = mResources.find(tag);

		if (mResources.end() != iter) 
		{
			return (Texture*)(*iter).second;
		}
		return nullptr;
	}

private:
	void setAbsolutePath();
	void setTextureNames();
	void loadTexture();

	vector<wstring> mFileList;
	map<wstring, CResource*> mResources;
	wstring mAbsolutePath;
};


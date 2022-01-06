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

	vector<Texture*> containsTexture(const wchar_t* tag) const
	{
		vector<Texture*> textures;
		textures.reserve(8);

		for (const auto& pair : mResources) 
		{
			if (ContainsString(tag, pair.first.c_str())) 
			{
				textures.push_back((Texture*)pair.second);
			}
		}
		return textures;
	}

private:
	void setAbsolutePath();
	void setTextureNames();
	void loadTexture();

	vector<wstring> mFileList;
	map<wstring, CResource*> mResources;
	wstring mAbsolutePath;
};


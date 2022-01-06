#pragma once

#include "Game.h"

class CResource
{
public:
	CResource(wstring tag);
	virtual ~CResource() = default;

	virtual bool load(wstring path) = 0;

	wstring getTag() const
	{
		return mTag;
	}

protected:
	const wstring mTag;
};


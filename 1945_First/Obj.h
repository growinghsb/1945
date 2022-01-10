#pragma once

#include "Game.h"

class Texture;
class Layer;
class Component;
class Collider;

class Obj
{
public:
	virtual ~Obj() = default;

	virtual void init() {};
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;
	virtual void onCollision(OBJ_TYPE collisionTarget) = 0;

	vector<Collider*> getColliderVector();
	vector<Component*> getAllComponents()
	{
		return mComponents;
	}

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

	bool isValidLeft();
	bool isValidTop();
	bool isValidRight();
	bool isValidBottom();
	
	void setComponent(Component* component) 
	{
		mComponents.push_back(component);
	}

	Layer* getLayer() const
	{
		return mLayer;
	}

	Texture* getTexture() const 
	{
		return mTexture;
	}

	void changePos(PointF pos) 
	{
		mPos = pos;
	}

protected:
	Obj(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);

	const wstring mTag;
	PointF mPos;
	POINT mScale;
	Texture* mTexture;
	Layer* mLayer;
	vector<Component*> mComponents;
};


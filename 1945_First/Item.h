#pragma once

#include "Obj.h"

class ObjLayer;

class Item :
	public Obj
{
public:
	Item(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
	~Item();

	void update() override;
	void render(HDC backDC) override;
	void onCollision(OBJ_TYPE collisionTarget) override;

private:
	void applyItem(ObjLayer* layer);

	float mSpeed;
};


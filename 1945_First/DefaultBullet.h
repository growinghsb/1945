#pragma once
#include "Obj.h"

class Texture;
class Layer;

class DefaultBullet :
    public Obj
{
public:
    DefaultBullet(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
    ~DefaultBullet() = default;

    virtual void update();
    virtual void render(HDC backDC);

private:
    float mSpeed;
    int mOffencePower;
};


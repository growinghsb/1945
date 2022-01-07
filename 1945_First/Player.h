#pragma once

#include "Obj.h"

class Layer;

class Player :
    public Obj
{
public:
    Player(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
    ~Player() = default;

    virtual void update();
    virtual void render(HDC backDC);

private:
    void createBullet();

    int mLifePoint;
    float mSpeed;
};


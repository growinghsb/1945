#pragma once

#include "Obj.h"

class Layer;

class Player :
    public Obj
{
public:
    Player(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
    ~Player();

    virtual void update();
    virtual void render(HDC backDC);

    void decreaseLifePointCount() 
    {
        --mLifePointCount;
    }

    int getLifePointCount() 
    {
        return mLifePointCount;
    }

private:
    void createBullet();

    int mLifePointCount;
    float mSpeed;
};


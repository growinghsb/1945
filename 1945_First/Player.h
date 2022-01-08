#pragma once

#include "Obj.h"

class Layer;

class Player :
    public Obj
{
public:
    Player(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
    ~Player();

    void update() override;
    void render(HDC backDC) override;
    void onCollision(OBJ_TYPE collisionTarget) override;

    void decreaseLifePointCount() 
    {
        --mLifePointCount;
    }

    void increaseLifePointCount()
    {
        ++mLifePointCount;
        
        if (mLifePointCount > MAX_LIFE_COUNT) 
        {
            mLifePointCount = MAX_LIFE_COUNT;
        }
    }

    int getLifePointCount() 
    {
        return mLifePointCount;
    }

private:
    void collisionObstacle();

    enum { MAX_LIFE_COUNT = 5 };

    int mLifePointCount;
    float mSpeed;
};


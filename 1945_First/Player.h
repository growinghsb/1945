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

    int getLifePointCount() 
    {
        return mLifePointCount;
    }

private:
    void collisionObstacle();
    void createBullet();

    int mLifePointCount;
    float mSpeed;
};


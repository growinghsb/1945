#pragma once
#include "Obj.h"

class Texture;
class Layer;

class DefaultBullet :
    public Obj
{
public:
    DefaultBullet(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer, float speed, int offencePower, int level, float angle);
    ~DefaultBullet();

     void update() override;
     void render(HDC backDC) override;
     void onCollision(OBJ_TYPE collisionTarget) override;

     int getOffencePower() const
     {
         return mOffencePower;
     }

    void setOffencePowerUp(int offencePower) 
    {
        mOffencePower = offencePower;
    }

    void setBulletLevel(int level) 
    {
        mCurrentBulletLevel = level;
    }

    int getCurrentBulletLevel() const 
    {
        return mCurrentBulletLevel;
    }

    bool isMaxBulletLevel() 
    {
        return mCurrentBulletLevel >= MAX_BULLET_LEVEL;
    }

private:
    enum {MAX_BULLET_LEVEL = 4};

    float mSpeed;
    int mOffencePower;
    int mCurrentBulletLevel;
    float mAngle;
};


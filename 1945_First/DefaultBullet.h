#pragma once
#include "Obj.h"

class Texture;
class Layer;

class DefaultBullet :
    public Obj
{
public:
    DefaultBullet(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
    ~DefaultBullet();

     void update() override;
     void render(HDC backDC) override;
     void onCollision(OBJ_TYPE collisionTarget) override;

     int getOffencePower() 
     {
         return mOffencePower;
     }

    void offencePowerUp() 
    {
        mOffencePower += 2;
    }

private:
    float mSpeed;
    int mOffencePower;
};


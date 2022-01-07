#pragma once
#include "Obj.h"
class Obstacle :
    public Obj
{
public:
    Obstacle(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer, int hp, float speed);
    ~Obstacle();

    virtual void update();
    virtual void render(HDC backDC);

    void decreaseHP(int offencePower) 
    {
        mHP -= offencePower;
    }

    bool isDie() 
    {
        return mHP <= 0;
    }

private:
    int mHP;
    float mSpeed;
};


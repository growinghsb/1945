#pragma once

#include "Layer.h"

class Obj;
class Player;

class ObjLayer :
    public Layer
{
public:
    ObjLayer();
    ~ObjLayer();

    void init() override;
    void update() override;
    void render(HDC backDC) override;

    void addObj(OBJ_TYPE type, Obj* obj) 
    {
        mObjs[(UINT)type].push_back(obj);
    }

    Player* getPlayer() const
    {
        return (Player*)mObjs[(UINT)OBJ_TYPE::PLAYER].front();
    }

private:
    void createObstacle();
    void deleteBullet();

    list<Obj*> mObjs[(UINT)OBJ_TYPE::END];
};


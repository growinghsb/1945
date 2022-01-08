#pragma once
#include "Obj.h"

class Obj;

class Enemy :
	public Obj
{
public:
	Enemy(wstring tag, PointF pos, POINT scale, Texture* texture, Layer* layer);
	~Enemy();

	void update() override;
	void render(HDC backDC) override;
	void onCollision(OBJ_TYPE collisionTarget) override;

private:
	void defaultBullet(); // 양 끝 날개에서 직선 방향으로 나가는 총알
	void rudderBullet(); // 플레이어 방향으로 쏘는 방향탄
	void guidedBullet(); // 일정시간이 지나면 플레이어쪽으로 빠르게 접근하는 유도탄
	void nWayBullet(); // 부채꼴 모양의 탄환
	void circleBullet(); // 전방향으로 퍼지는 원형탄
	void fragmentationBullet(); // 처음엔 하나로 나와서 사방으로 퍼지는 분열탄

	enum {MAX_HP = 2000};

	float mSpeed;
	int mCurrentHP;
};


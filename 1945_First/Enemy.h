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
	void defaultBullet(); // �� �� �������� ���� �������� ������ �Ѿ�
	void rudderBullet(); // �÷��̾� �������� ��� ����ź
	void guidedBullet(); // �����ð��� ������ �÷��̾������� ������ �����ϴ� ����ź
	void nWayBullet(); // ��ä�� ����� źȯ
	void circleBullet(); // ���������� ������ ����ź
	void fragmentationBullet(); // ó���� �ϳ��� ���ͼ� ������� ������ �п�ź

	enum {MAX_HP = 2000};

	float mSpeed;
	int mCurrentHP;
};


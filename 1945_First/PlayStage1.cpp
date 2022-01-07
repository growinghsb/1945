#include "PlayStage1.h"
#include "ObjLayer.h"
#include "TimeManager.h"
#include "StageManager.h"
#include "Texture.h"
#include "CoreManager.h"
#include "Player.h"

extern bool excuteTimer;

PlayStage1::PlayStage1(int orderNum)
	: Stage(orderNum)
{
	mLayer.reserve(4);
}

PlayStage1::~PlayStage1()
{
	for (auto element : mLayer) 
	{
		delete element;
	}
	mLayer.clear();
}

void PlayStage1::enter()
{
	// ��׶��� ���̾�
	mLayer.push_back(new ObjLayer()); // ������Ʈ ���̾� ����
	// �����UI ���̾�

	// �÷��̾� ����
	Texture* texture = StageManager::getInstance()->getTexture();
	POINT res = texture->getResolution();

	float x = float((WINDOW.right - res.x) / 2);
	PointF pos = { x, 600 };

	Player* player  = new Player(L"player", pos, res, texture, mLayer[(UINT)LAYER_TYPE::OBJ]);

	StageManager::getInstance()->setPlayer(player);

	// ������ �÷��̾� ������Ʈ ���̾ �߰�
	ObjLayer* layer = (ObjLayer*)mLayer[(UINT)LAYER_TYPE::OBJ];
	layer->addObj(OBJ_TYPE::PLAYER, player);

	init();
}

void PlayStage1::init()
{
	for (auto element : mLayer)
	{
		element->init();
	}
}

void PlayStage1::update()
{
	for (auto element : mLayer)
	{
		element->update();
	}
}

void PlayStage1::render(HDC backDC)
{
	for (auto element : mLayer)
	{
		element->render(backDC);
	}
}

void PlayStage1::exit()
{
	excuteTimer = false;
	TimeManager::getInstance()->clear();

	ObjLayer* layer = (ObjLayer*)mLayer[(UINT)LAYER_TYPE::OBJ];
	StageManager::getInstance()->setPlayer(layer->getPlayer());
}

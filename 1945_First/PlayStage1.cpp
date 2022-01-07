#include "PlayStage1.h"
#include "ObjLayer.h"
#include "TimeManager.h"
#include "StageManager.h"
#include "Texture.h"
#include "CoreManager.h"
#include "Player.h"
#include "Collider.h"
#include "UILayer.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

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
	// 백그라운드 레이어
	mLayer.push_back(new ObjLayer());					 // 오브젝트 레이어
	mLayer.push_back(new UILayer(FIND_TEXTURE(L"life")));// 사용자UI 레이어

	// 플레이어 생성
	Texture* texture = StageManager::getInstance()->getPlayerTexture();
	POINT res = texture->getResolution();

	float x = float((WINDOW.right - res.x) / 2);
	PointF pos = { x, 600 };

	Player* player  = new Player(L"player", pos, res, texture, mLayer[(UINT)LAYER_TYPE::OBJ]);

	// 충돌체 컴포넌트 추가
	POINT colScale = { int(res.x * 0.5), int(res.y * 0.7) };
	PointF offset = { float(res.x - colScale.x) / 2, float(res.y - colScale.y) / 2 };
	player->setComponent(new Collider(COMPONENT_TYPE::COLLIDER, player, pos, offset, colScale));

	// 생성된 플레이어, 스테이지 매니저에 추가
	StageManager::getInstance()->setPlayer(player);

	// 생성된 플레이어, 오브젝트 레이어에 추가
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

	// 여기서 충돌매니저 업데이트 진행
	CollisionManager::getInstance()->update((ObjLayer*)mLayer[(UINT)LAYER_TYPE::OBJ]);
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
}

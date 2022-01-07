#include "EventManager.h"
#include "StageManager.h"
#include "Obj.h"
#include "ObjLayer.h"

EventManager::EventManager()
	: mEventQueue{}
{
	mEventQueue.reserve(128);
}

void EventManager::execute()
{
	for (const auto& element : mEventQueue) 
	{
		switch (element.mType)
		{
		case EVENT_TYPE::STAGE_CHANGE:
			changeStage((CHANGE_STAGE_TYPE)element.mLow);
			goto EXIT; // 스테이지 변경 작업 뒤에 일어난 이벤트는 무시, 바로 실행 종료
		case EVENT_TYPE::CREATE_OBJ:
			break;
		case EVENT_TYPE::DELETE_OBJ:
			deleteObj((OBJ_TYPE)element.mLow, (Obj*)element.mHigh);
			break;
		default:
			break;
		}
	}
EXIT:
	mEventQueue.clear();
}

void EventManager::changeStage(CHANGE_STAGE_TYPE type)
{
	// 여기서 스테이지 변경 작업 요청
	StageManager::getInstance()->changeStage(type);
}

void EventManager::deleteObj(OBJ_TYPE objType, Obj* obj)
{
	// 오브젝트 삭제 작업
	ObjLayer* layer = (ObjLayer*)obj->getLayer();
	layer->deleteObj(objType, obj);
}

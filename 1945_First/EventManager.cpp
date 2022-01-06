#include "EventManager.h"
#include "StageManager.h"

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

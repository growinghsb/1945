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
			goto EXIT; // �������� ���� �۾� �ڿ� �Ͼ �̺�Ʈ�� ����, �ٷ� ���� ����
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
	// ���⼭ �������� ���� �۾� ��û
	StageManager::getInstance()->changeStage(type);
}

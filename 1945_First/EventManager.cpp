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
			goto EXIT; // �������� ���� �۾� �ڿ� �Ͼ �̺�Ʈ�� ����, �ٷ� ���� ����
		case EVENT_TYPE::CREATE_OBJ:
			createObj((OBJ_TYPE)element.mLow, (Obj*)element.mHigh);
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
	// ���⼭ �������� ���� �۾� ��û
	StageManager::getInstance()->changeStage(type);
}

void EventManager::createObj(OBJ_TYPE objType, Obj* targetObj)
{
	// ������ ���� �۾�
	ObjLayer* layer = (ObjLayer*)targetObj->getLayer();
	layer->addObj(objType, targetObj);
}

void EventManager::deleteObj(OBJ_TYPE objType, Obj* targetObj)
{
	// ������Ʈ ���� �۾�
	ObjLayer* layer = (ObjLayer*)targetObj->getLayer();
	layer->deleteObj(objType, targetObj);
}

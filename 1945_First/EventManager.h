#pragma once

#include "Game.h"

class Obj;

class EventManager
{
public:
	SINGLE(EventManager)

	void execute();

	// �ܺο��� �������� ���� �̺�Ʈ�� �޾� ť�� �����ϴ� �Լ�
	void addChangeStage(EVENT_TYPE type, CHANGE_STAGE_TYPE changeType) 
	{
		mEventQueue.push_back(EventInfo{ type, (DWORD_PTR)changeType });
	}
	
	// ������ ������Ʈ�� ����� ������ Ÿ���� �޾� ť�� �����ϴ� �Լ�
	void addCreateObj(EVENT_TYPE type, OBJ_TYPE objType, Obj* targetObj) 
	{
		mEventQueue.push_back(EventInfo{ type, (DWORD_PTR)objType, (DWORD_PTR)targetObj });
	}

	// ������ ������Ʈ�� Ÿ�԰� ������Ʈ�� �޾� �̺�Ʈ ť�� �����ϴ� �Լ�
	void addDeleteObj(EVENT_TYPE type, OBJ_TYPE objType, Obj* targetObj)
	{
		for (const auto& element : mEventQueue) 
		{
			if (element.mType == type && element.mHigh == (DWORD_PTR)targetObj) 
			{
				return;
			}
		}
		mEventQueue.push_back(EventInfo{type, (DWORD_PTR)objType, (DWORD_PTR)targetObj });
	}

private:
	EventManager();
	~EventManager() = default;
	
	void changeStage(CHANGE_STAGE_TYPE type);
	void createObj(OBJ_TYPE objType, Obj* targetObj);
	void deleteObj(OBJ_TYPE objType, Obj* targetObj);

	vector<EventInfo> mEventQueue;
};


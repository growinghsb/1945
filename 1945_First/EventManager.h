#pragma once

#include "Game.h"

class Obj;

class EventManager
{
public:
	SINGLE(EventManager)

	void execute();

	// 외부에서 스테이지 변경 이벤트를 받아 큐에 저장하는 함수
	void addChangeStage(EVENT_TYPE type, CHANGE_STAGE_TYPE changeType) 
	{
		mEventQueue.push_back(EventInfo{ type, (DWORD_PTR)changeType });
	}
	
	// 저장할 오브젝트와 저장될 공간의 타입을 받아 큐에 저장하는 함수
	void addCreateObj(EVENT_TYPE type, OBJ_TYPE objType, Obj* targetObj) 
	{
		mEventQueue.push_back(EventInfo{ type, (DWORD_PTR)objType, (DWORD_PTR)targetObj });
	}

	// 삭제할 오브젝트의 타입과 오브젝트를 받아 이벤트 큐에 저장하는 함수
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


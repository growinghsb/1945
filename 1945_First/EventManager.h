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
	
	void addDeleteObj(EVENT_TYPE type, OBJ_TYPE objType, Obj* obj)
	{
		mEventQueue.push_back(EventInfo{type, (DWORD_PTR)objType, (DWORD_PTR)obj});
	}

	void addCreateObj(); // 나중에

private:
	EventManager();
	~EventManager() = default;
	
	void changeStage(CHANGE_STAGE_TYPE type);
	void createObj();
	void deleteObj(OBJ_TYPE objType, Obj* obj);

	vector<EventInfo> mEventQueue;
};


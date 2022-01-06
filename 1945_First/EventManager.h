#pragma once

#include "Game.h"

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
	
	// 아래 두 개는 추후에 진행
	void addCreateObj();
	void addDeleteObj();


private:
	EventManager();
	~EventManager() = default;
	
	void changeStage(CHANGE_STAGE_TYPE type);
	void createObj();
	void deleteObj();

	vector<EventInfo> mEventQueue;
};


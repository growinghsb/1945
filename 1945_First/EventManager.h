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
	
	void addDeleteObj(EVENT_TYPE type, OBJ_TYPE objType, Obj* obj)
	{
		mEventQueue.push_back(EventInfo{type, (DWORD_PTR)objType, (DWORD_PTR)obj});
	}

	void addCreateObj(); // ���߿�

private:
	EventManager();
	~EventManager() = default;
	
	void changeStage(CHANGE_STAGE_TYPE type);
	void createObj();
	void deleteObj(OBJ_TYPE objType, Obj* obj);

	vector<EventInfo> mEventQueue;
};


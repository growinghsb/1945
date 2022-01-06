#pragma once

#include "Game.h"

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
	
	// �Ʒ� �� ���� ���Ŀ� ����
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


#include "TimeManager.h"
#include "CoreManager.h"

static float ds = 0.f;
static int second = 0;

TimeManager::TimeManager()
	: mFrequency{}
	, mPrevCounter{}
	, mCurCounter{}
	, mDS(0.f)
	, mFPS(0)
	, mSecond(0)
{
	ds = 0.f;
	second = 0;
}

void TimeManager::init()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mPrevCounter);
}

void TimeManager::update(HWND hWnd)
{
	QueryPerformanceCounter(&mCurCounter);
	mDS = (float)(mCurCounter.QuadPart - mPrevCounter.QuadPart) / (float)mFrequency.QuadPart;

	ds += mDS;
	++mFPS;

	if (ds >= 1.f)
	{
		ds = ds - 1.f;
		mSecond += 1;
		second += 1;

		if (second > 59)
		{
			second = 0;
		}

		int minute = mSecond / 60;
		int hour = (mSecond / 60) / 60;

		enum { LENGTH = 128 };
		wchar_t text[LENGTH] = {};
		swprintf(text, LENGTH, L"FPS: %d DS: %f Time: %d시간 %d분 %d초", mFPS, mDS, hour, minute, second);
		SetWindowTextW(hWnd, text);

		mFPS = 0;
	}
	mPrevCounter = mCurCounter;
}

void TimeManager::clear()
{
	mFrequency = {};
	mPrevCounter = {};
	mCurCounter = {};
	mDS = 0.f;
	mFPS = 0;
	mSecond = 0;

	ds = 0.f;
	second = 0;

	enum { LENGTH = 8 };
	wchar_t text[LENGTH] = {};
	swprintf(text, LENGTH, L"1945");
	SetWindowTextW(CoreManager::getInstance()->getHWnd(), text);
}
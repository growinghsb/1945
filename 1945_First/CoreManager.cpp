#include "CoreManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "StageManager.h"

CoreManager* CoreManager::mInstance = nullptr;
bool CoreManager::mPlay = true;

bool excuteTimer = false;

CoreManager::CoreManager()
	: mHInstance(nullptr)
	, mHWnd(nullptr)
	, mHDC(nullptr)
	, mBackDC(nullptr)
	, mBackBitmap(nullptr)
	, mWindow{}
{
}

CoreManager::~CoreManager()
{
	ReleaseDC(mHWnd, mHDC);
	DeleteDC(mBackDC);
	DeleteObject(mBackBitmap);
}

bool CoreManager::init(HINSTANCE hInstance)
{
	srand((unsigned int)time(nullptr));

	mHInstance = hInstance;

	myRegisterClass();

	if (false == createWindow())
	{
		return false;
	}

	mBackDC = CreateCompatibleDC(mHDC);
	mBackBitmap = CreateCompatibleBitmap(mHDC, mWindow.right, mWindow.bottom);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackDC, mBackBitmap);
	DeleteObject(oldBitmap);

	ResourceManager::getInstance()->init();
	StageManager::getInstance()->init();

	return true;
}

void CoreManager::update()
{
	if (excuteTimer) 
	{
		TimeManager::getInstance()->update(mHWnd);
	}
	InputManager::getInstance()->update();
	StageManager::getInstance()->update();
}

void CoreManager::render(HDC backDC)
{
	// 오브젝트들이 그려질 백버퍼를 흰색 배경으로 깔아준다.
	FillRect(mBackDC, &mWindow, (HBRUSH)(COLOR_WINDOW + 1));

	StageManager::getInstance()->render(backDC);

	// 항상 백버퍼에 있는 화면을 메인 버퍼로 복사해줘야 더블버퍼링 되어 화면이 보여진다.
	BitBlt(mHDC, 0, 0, mWindow.right, mWindow.bottom, backDC, 0, 0, SRCCOPY);
}

int CoreManager::run()
{
	MSG msg = {};

	while (mPlay)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			update();
			render(mBackDC);

			// 랜더링 까지 끝난 뒤 이벤트를 처리한다.
			EventManager::getInstance()->execute();
		}
	}
	return (int)msg.wParam;
}

bool CoreManager::createWindow()
{
	mHWnd = CreateWindowW(L"1945", L"1945", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mHInstance, nullptr);

	if (nullptr == mHWnd)
	{
		return false;
	}

	mHDC = GetDC(mHWnd);

	mWindow = { 0, 0, 650, 770 };
	AdjustWindowRect(&mWindow, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(mHWnd, HWND_TOP, mWindow.left, 0, mWindow.right - mWindow.left, mWindow.bottom - mWindow.top, SWP_SHOWWINDOW);
	ShowWindow(mHWnd, SW_SHOW);

	GetClientRect(mHWnd, &mWindow); // 현재 윈도우 크기값 세팅

	return true;
}

ATOM CoreManager::myRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mHInstance;
	wcex.hIcon = LoadIcon(mHInstance, MAKEINTRESOURCE(IDI_MY1945FIRST));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_MY1945FIRST);
	wcex.lpszClassName = L"1945";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

LRESULT CoreManager::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		mPlay = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
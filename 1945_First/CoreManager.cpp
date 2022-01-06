#include "CoreManager.h"

CoreManager* CoreManager::mCoreManager = nullptr;
bool CoreManager::mPlay = true;

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

CoreManager* CoreManager::getInstance()
{
	if (nullptr == mCoreManager)
	{
		mCoreManager = new CoreManager;
	}
	return mCoreManager;
}

void CoreManager::deleteInstance()
{
	if (nullptr != mCoreManager)
	{
		delete mCoreManager;
		mCoreManager = nullptr;
	}
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

	return true;
}

void CoreManager::update()
{
}

void CoreManager::render(HDC backDC)
{
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
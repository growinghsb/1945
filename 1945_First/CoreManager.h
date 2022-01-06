#pragma once

#include "Game.h"

class CoreManager
{
public:
	static CoreManager* getInstance();
	

	static void deleteInstance();
	

	static LRESULT CALLBACK    wndProc(HWND, UINT, WPARAM, LPARAM);

	bool init(HINSTANCE hInstance);
	void update();
	void render(HDC backDC);
	int run();

private:
	CoreManager();
	~CoreManager();
	
	ATOM                myRegisterClass();
	bool                createWindow();

	static CoreManager* mCoreManager;
	static bool			mPlay;

	HINSTANCE mHInstance;
	HWND	  mHWnd;
	HDC		  mHDC;
	HDC		  mBackDC;
	HBITMAP	  mBackBitmap;
	RECT	  mWindow;
};


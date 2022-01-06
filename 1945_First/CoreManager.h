#pragma once

#include "Game.h"

class CoreManager
{
public:
	SINGLE(CoreManager);

	static LRESULT CALLBACK    wndProc(HWND, UINT, WPARAM, LPARAM);

	bool init(HINSTANCE hInstance);
	void update();
	void render(HDC backDC);
	int run();

	HDC getMainDC() const
	{
		return mHDC;
	}

	HWND getHWnd() const 
	{
		return mHWnd;
	}

	RECT getWindow() const 
	{
		return mWindow;
	}

private:
	CoreManager();
	~CoreManager();
	
	ATOM                myRegisterClass();
	bool                createWindow();

	static CoreManager* mInstance;
	static bool			mPlay;

	HINSTANCE mHInstance;
	HWND	  mHWnd;
	HDC		  mHDC;
	HDC		  mBackDC;
	HBITMAP	  mBackBitmap;
	RECT	  mWindow;
};


#include "Game.h"
#include "CoreManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(655);

	if (false == CoreManager::getInstance()->init(hInstance))
	{
		return false;
	}

	return CoreManager::getInstance()->run();
}

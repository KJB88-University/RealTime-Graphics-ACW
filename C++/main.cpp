
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

// ACW Include
#include "Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{

	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	printf("CONSOLE: Attached.\n");

	// Create and initialize Window
	Window* window;
	window = new Window();
	window->Init();

	// Run main loops
	window->Run();

	// Clean up and destroy
	window->OnDestroy();
	delete window;
	window = nullptr;

	// END
	return 0;
}
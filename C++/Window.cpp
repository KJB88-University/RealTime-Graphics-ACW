#include "Window.h"
//#include "BasicLogger.h" //debug logger, not needed for submission
#include "GraphicsManager.h"

#include "Keyboard.h"

Window::Window(void)
	: m_applicationName(nullptr), m_hinstance(nullptr), m_hwnd(nullptr), m_fullScreen(true), m_game(nullptr)
{

}

Window::~Window(void)
{
	delete m_game;
	m_game = nullptr;
}

void Window::Init(void)
{
	// Viewport width/height
	int vpWidth, vpHeight;
	vpWidth = 0;
	vpHeight = 0;
	
	// Frustrum Culling
	float nearClip, farClip;
	nearClip = 0.01f;
	farClip = 1000.0f;

	// Initialize the Windows API
	InitWindows(vpWidth, vpHeight, true);
//#if _DEBUG
//	BasicLogger::WriteToConsole("WINDOW: Initialized. \n");
//#endif

	// Create the game application
	m_game = new Game();
	m_game->Initialize(vpWidth, vpHeight, m_hwnd, nearClip, farClip);
}

void Window::OnDestroy()
{
	m_game->Destroy();

	EndWindows();
}

void Window::Run(void)
{
	MSG msg;

	// Init message structure
	ZeroMemory(&msg, sizeof(MSG));
//#if _DEBUG
//	BasicLogger::WriteToConsole("WINDOW: Running main loop...");
//#endif
	bool done = false;
	while (!done)
	{
		// Handle Windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Exit condition
		if (!Update() || msg.message == WM_QUIT)
		{
			done = true;
		}
	}
}

bool Window::Update(void)
{
	bool result;

	result = m_game->Update();
	m_game->Render();

	// Keep looping
	return result;
}

LRESULT CALLBACK Window::MessageHandler(HWND const hwnd, UINT const umsg, WPARAM const wparam, LPARAM const lparam)
{
	switch (umsg)
	{
		// Plug in InputManager
	case WM_KEYDOWN:
		//BasicLogger::WriteToConsole("INPUT: KeyDown ID: " + wparam);
		//m_input->UpdateKeyOnPress((unsigned int)wparam);
		return 0;

	case WM_KEYUP:
		//BasicLogger::WriteToConsole("INPUT: KeyUp ID: " + wparam);
		//m_input->UpdateKeyOnRelease((unsigned int)wparam);
		return 0;

	default:
		// Our application doesnt care about any other messages,
		// so pass through.
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

// Initialize Windows API so we can create a
// window and utilize Windows-based services
void Window::InitWindows(int& vpWidth, int& vpHeight, bool const fullScreen)
{
	WNDCLASSEX wc;
	//DEVMODE dmScreenSettings;
	int posX = 0;
	int posY = 0;

	m_fullScreen = fullScreen;

	// External ptr for object
	ApplicationHandle = this;

	// Get instance of the app
	m_hinstance = GetModuleHandle(NULL);

	// App name
	m_applicationName = L"RTG C++ ACW1";

	// Configure settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the Window class
	RegisterClassEx(&wc);

	vpWidth = GetSystemMetrics(SM_CXSCREEN);
	vpHeight = GetSystemMetrics(SM_CYSCREEN);

	/*
	// Setup Full screen
	// (Not required for ACW, but for robustness)
	if (m_fullScreen)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)vpWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)vpHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	}
	// Setup windowed
	else
	{
	*/
		vpWidth = 1080;
		vpHeight = 960;

		// Centre the window
		posX = (GetSystemMetrics(SM_CXSCREEN) - vpWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - vpHeight) / 2;
	//}

	// Create the window and plug in settings
	m_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, m_applicationName, m_applicationName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		posX, posY, vpWidth, vpHeight, nullptr, nullptr, m_hinstance, nullptr);

	// Pop window and make primary
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide cursor
	//ShowCursor(false);

	return;

}

void Window::EndWindows(void)
{
	//ShowCursor(true);

	// Account for possible full screen
	if (m_fullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove window
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove application instance
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release pointer
	ApplicationHandle = NULL;

}

LRESULT CALLBACK WndProc(HWND const hwnd, UINT const umsg, WPARAM const wparam, LPARAM const lparam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (umsg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
		break;

		// Fall-through detection of key events
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(umsg, wparam, lparam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

		// Passthrough
	default:
		return ApplicationHandle->MessageHandler(hwnd, umsg, wparam, lparam);
	}
}
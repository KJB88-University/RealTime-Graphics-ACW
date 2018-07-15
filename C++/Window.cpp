//#include "Window.h"
//#include "BasicLogger.h"
//#include "GraphicsManager.h"
//
//Window::Window(void)
//	: m_graphics(nullptr)
//{
//
//}
//
//Window::~Window(void)
//{
//
//}
//
//void Window::Init(void)
//{
//	// Viewport width/height
//	int vpWidth, vpHeight;
//	vpWidth = 0;
//	vpHeight = 0;
//
//	// Initialize the Windows API
//	InitWindows(vpWidth, vpHeight);
//	BasicLogger::WriteToConsole("WINDOW: Initialized. \n");
//
//	//m_graphics = new GraphicsManager();
//	//m_graphics->Initialize(vpWidth, vpHeight, m_hwnd);
//	//BasicLogger::WriteToConsole("WINDOW: Graphics Manager initialized.\n");
//
//	BasicLogger::WriteToConsole("WINDOW: Managers initialized.\n");
//}
//
//void Window::OnDestroy()
//{
//	//delete m_graphics;
//	//m_graphics = nullptr;
//
//	EndWindows();
//}
//
//void Window::Run(void)
//{
//	MSG msg;
//
//	// Init message structure
//	ZeroMemory(&msg, sizeof(MSG));
//
//	printf("WINDOW: Running main loop...");
//	// Loop until exit command given
//	bool done = false;
//	while (!done)
//	{
//		// Handle Windows messages
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//
//		// Exit command given
//		if (msg.message == WM_QUIT)
//		{
//			done = true;
//		}
//		
//		else
//		{
//			if (!Update())
//			{
//				done = true;
//			}
//		}
//		
//	}
//}
//
//bool Window::Update(void)
//{
//	/*
//	// Respond to input
//	if (m_input->CheckKey(VK_ESCAPE))
//	{
//		// Stop looping
//		return false;
//	}
//
//	m_scene->Update(m_time);
//	m_scene->Render(m_graphics);
//	*/
//
//	// Keep looping
//	return true;
//}
//
//LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
//{
//	switch (umsg)
//	{
//		// Plug in InputManager
//	case WM_KEYDOWN:
//		BasicLogger::WriteToConsole("INPUT: KeyDown ID: " + wparam);
//		//m_input->UpdateKeyOnPress((unsigned int)wparam);
//		return 0;
//
//	case WM_KEYUP:
//		BasicLogger::WriteToConsole("INPUT: KeyUp ID: " + wparam);
//		//m_input->UpdateKeyOnRelease((unsigned int)wparam);
//		return 0;
//
//	default:
//		// Our application doesnt care about any other messages,
//		// so pass through.
//		return DefWindowProc(hwnd, umsg, wparam, lparam);
//	}
//}
//
//// Initialize Windows API so we can create a
//// window and utilize Windows-based services
//void Window::InitWindows(int& vpWidth, int& vpHeight)
//{
//	WNDCLASSEX wc;
//	DEVMODE dmScreenSettings;
//	int posX, posY;
//
//	// External ptr for object
//	ApplicationHandle = this;
//
//	// Get instance of the app
//	m_hinstance = GetModuleHandle(NULL);
//
//	// App name
//	m_applicationName = L"RTG C++ ACW1";
//
//	// Configure settings
//	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//	wc.lpfnWndProc = WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = m_hinstance;
//	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
//	wc.hIconSm = wc.hIcon;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = m_applicationName;
//	wc.cbSize = sizeof(WNDCLASSEX);
//
//	// Register the Window class
//	RegisterClassEx(&wc);
//
//	vpWidth = GetSystemMetrics(SM_CXSCREEN);
//	vpHeight = GetSystemMetrics(SM_CYSCREEN);
//
//	// Setup Full screen
//	// (Not required for ACW, but for robustness)
//	if (FULL_SCREEN)
//	{
//		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
//		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
//		dmScreenSettings.dmPelsWidth = (unsigned long)vpWidth;
//		dmScreenSettings.dmPelsHeight = (unsigned long)vpHeight;
//		dmScreenSettings.dmBitsPerPel = 32;
//		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
//
//	}
//	// Setup windowed
//	else
//	{
//		vpWidth = 1080;
//		vpHeight = 960;
//
//		// Centre the window
//		posX = (GetSystemMetrics(SM_CXSCREEN) - vpWidth) / 2;
//		posY = (GetSystemMetrics(SM_CYSCREEN) - vpHeight) / 2;
//	}
//
//	// Create the window and plug in settings
//	m_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, m_applicationName, m_applicationName,
//		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
//		posX, posY, vpWidth, vpHeight, nullptr, nullptr, m_hinstance, nullptr);
//
//	// Pop window and make primary
//	ShowWindow(m_hwnd, SW_SHOW);
//	SetForegroundWindow(m_hwnd);
//	SetFocus(m_hwnd);
//
//	// Hide cursor
//	//ShowCursor(false);
//
//	return;
//
//}
//
//void Window::EndWindows(void)
//{
//	//ShowCursor(true);
//
//	// Account for possible full screen
//	if (FULL_SCREEN)
//	{
//		ChangeDisplaySettings(NULL, 0);
//	}
//
//	// Remove window
//	DestroyWindow(m_hwnd);
//	m_hwnd = NULL;
//
//	// Remove application instance
//	UnregisterClass(m_applicationName, m_hinstance);
//	m_hinstance = NULL;
//
//	// Release pointer
//	ApplicationHandle = NULL;
//
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
//{
//	PAINTSTRUCT paintStruct;
//	HDC hDC;
//
//	switch (umsg)
//	{
//	case WM_PAINT:
//		hDC = BeginPaint(hwnd, &paintStruct);
//		EndPaint(hwnd, &paintStruct);
//		break;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		return 0;
//
//		// Passthrough
//	default:
//		return ApplicationHandle->MessageHandler(hwnd, umsg, wparam, lparam);
//	}
//}
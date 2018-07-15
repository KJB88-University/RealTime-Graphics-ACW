//#pragma once
//#include "Windows.h"
//#include "GraphicsManager.h"
//
//class Window
//{
//public:
//
//	Window(void);
//	~Window(void);
//
//	// Main behaviours
//	void Init(void);
//	void OnDestroy(void);
//	void Run(void);
//
//	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
//
//private:
//
//	bool Update(void);
//	void InitWindows(int&, int&);
//	void EndWindows(void);
//
//	LPCWSTR m_applicationName;
//	HINSTANCE m_hinstance;
//	HWND m_hwnd;
//
//	GraphicsManager* m_graphics;
//};
//
//static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//static Window* ApplicationHandle = 0;
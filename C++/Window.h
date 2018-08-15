#pragma once
#include "Windows.h"

// ACW Includes
#include "GraphicsManager.h"
#include "Game.h"

class Window
{
public:

	Window(void);
	~Window(void);

	void Init(void);
	void OnDestroy(void);
	void Run(void);

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:

	bool Update(void);
	void InitWindows(int& vpWidth, int& vpHeight, bool fullScreen);
	void EndWindows(void);

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	bool m_fullScreen;

	Game* m_game;

	Window(const Window& other)=delete;
	Window& Window::operator=(const Window& other)=delete;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Window* ApplicationHandle = 0;
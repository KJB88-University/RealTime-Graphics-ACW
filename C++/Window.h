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
	void InitWindows(int&, int&);
	void EndWindows(void);

	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Game* m_game;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static Window* ApplicationHandle = 0;
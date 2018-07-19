#pragma once
#include "Windows.h"

// ACW Includes
#include "Tiny.h" // DEBUG
#include "Platform.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "TimeManager.h"

class Game
{

public:
	Game(void);
	~Game(void);

	void Initialize(int vpWidth, int vpHeight, HWND hwnd);
	void Destroy(void);
	void Update(void);
	void Render(void);

private:

	// Objects
	Tiny* m_tiny;
	Platform* m_platform;

	Camera* m_mainCamera;

	// Managers
	TimeManager* m_time;
	GraphicsManager* m_gfx;
};
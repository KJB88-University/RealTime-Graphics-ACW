#pragma once
#include "Windows.h"

// DXTK Includes
#include "Keyboard.h"

// ACW Includes
// Managers
#include "GraphicsManager.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "TimeManager.h"

// Objects
#include "Tiny.h" // DEBUG
#include "Platform.h"


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

	// Modifiers
	bool m_wireFrameMode;

	// Objects
	Tiny* m_tiny;
	Platform* m_platform;

	// Main Camera
	Camera* m_mainCamera;

	// Managers
	TimeManager* m_time;
	GraphicsManager* m_gfx;
	InputManager* m_input;
	CameraManager* m_camMgr;

	// Input States
	DirectX::Keyboard::State m_kbState;
};
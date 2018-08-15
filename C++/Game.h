#pragma once
#include "Windows.h"

// DXTK Includes
#include "Keyboard.h"

// AntTweakBar
#include "AntTweakBar.h"

// ACW Includes
// Managers
#include "GraphicsManager.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "TimeManager.h"

// Objects
#include "Platform.h"
#include "Dome.h"
#include "Dragonfly.h"
#include "Twig.h"


class Game
{

public:
	Game(void);
	~Game(void);

	void Initialize(int vpWidth, int vpHeight, HWND hwnd, float nearClip, float farClip);
	void Destroy(void);
	bool Update(void);
	void Render(void);
	
	void ResetGame(void);

	// DEBUG
	//void PostProcess(void);
private:

	// Modifiers
	bool m_wireFrameMode;
	bool m_statDisplay;

	// Objects
	Platform* m_platform;
	Dome* m_dome;
	Dragonfly* m_dragonfly;
	Twig* m_twig;

	// Main Camera
	Camera* m_mainCamera;

	// Managers
	TimeManager* m_time;
	GraphicsManager* m_gfx;
	InputManager* m_input;
	CameraManager* m_camMgr;

	// ATB
	TwBar* m_antTweakBar;
	float m_timeModifier;
	int m_currentCamera;
	uint32_t m_fps;

	// Input States
	DirectX::Keyboard::State m_kbState;
};
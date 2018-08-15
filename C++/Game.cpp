// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// ACW includes
#include "Game.h"
//#include "BasicLogger.h" // Debug logger - not needed for submission
#include "Shader.h"

Game::Game(void)
	:m_wireFrameMode(false), m_statDisplay(false), m_platform(nullptr), m_dome(nullptr), m_dragonfly(nullptr), m_twig(nullptr), m_mainCamera(nullptr),
	m_time(nullptr), m_gfx(nullptr), m_input(nullptr), m_camMgr(nullptr), 
	m_antTweakBar(nullptr), m_timeModifier(0), m_currentCamera(0), m_fps(0)
{

}

Game::~Game(void)
{
	// DESTROY GAME OBJECTS
	// Main Camera
	delete m_mainCamera;
	m_mainCamera = nullptr;

	// Platform
	delete m_platform;
	m_platform = nullptr;

	// Dome
	delete m_dome;
	m_dome = nullptr;

	// Dragonfly
	delete m_dragonfly;
	m_dragonfly = nullptr;

	// Twig
	delete m_twig;
	m_twig = nullptr;

	// DESTROY MANAGERS
	// Time
	delete m_time;
	m_time = nullptr;

	// Camera
	delete m_camMgr;
	m_camMgr = nullptr;

	// Input
	delete m_input;
	m_input = nullptr;

	// AntTweakBar
	TwTerminate();

	// Graphics
	delete m_gfx;
	m_gfx = nullptr;
}

void Game::Initialize(int const vpWidth, int const vpHeight, HWND const hwnd, float const nearClip, float const farClip)
{
	// Graphics Manager
	m_gfx = new GraphicsManager();
	m_gfx->Initialize(hwnd);
//#if _DEBUG
//	BasicLogger::WriteToConsole("GAME: Graphics Manager initialized.\n");
//#endif

	// Time Manager
	m_time = new TimeManager();
	m_time->Initialize();
//#if _DEBUG
//	BasicLogger::WriteToConsole("GAME: Time Manager initialized.\n");
//#endif

	// Input Manager
	m_input = new InputManager();
	m_input->Initialize();
//#if _DEBUG
//	BasicLogger::WriteToConsole("GAME: Input Manager initialized.\n");
//#endif

	// Platform (Ground)
	m_platform = new Platform(Vector3(0.0f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 15.0f, 50.0f));
	m_platform->Initialize(m_gfx);
	//BasicLogger::WriteToConsole("GAME: Platform initialized.\n");

	// Dome (Hemisphere)
	m_dome = new Dome(Vector3(0.0f, -5.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.75f, 50.75f, 50.75f));
	m_dome->Initialize(m_gfx);
	//BasicLogger::WriteToConsole("GAME: Dome initialized.\n");

	// Dragonfly
	m_dragonfly = new Dragonfly(Vector3(0.0f, 2.25f, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
	m_dragonfly->Initialize(m_gfx);
	//BasicLogger::WriteToConsole("GAME: Dragonfly initialized.\n");

	// Twig
	m_twig = new Twig(Vector3(0.0f, 0.25f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(3.0f, 20.0f, 3.0f));
	m_twig->Initialize(m_gfx);
	//BasicLogger::WriteToConsole("GAME: Twig initialized.\n");

	// Camera Manager
	// (The camera manager initializes the first camera to the position given (first argument))
	m_camMgr = new CameraManager();
	m_camMgr->Initialize(Vector3(0.0f, -7.5f, -60.0f), Vector3(0.0f, 0.0f, -1.0f), vpWidth, vpHeight, nearClip, farClip); // First Cam
	m_camMgr->AddCamera(Vector3(4.0f, -2.5f, -5.5f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 2.25f, -5.0f)); // Second Cam
	m_camMgr->AddCamera(Vector3(2.5f, -2.25f, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), true, m_dragonfly); // Third Cam
	m_camMgr->AddCamera(Vector3(3.5f, -2.5f, -0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f)); // Fourth Cam
//#if _DEBUG
//	BasicLogger::WriteToConsole("GAME: Camera Manager initialized.\n");
//#endif

	// Main Camera
	m_mainCamera = m_camMgr->GetMainCamera();
	//BasicLogger::WriteToConsole("GAME: Main Camera initialized.\n");

	// AntTweakBar
	TwInit(TW_DIRECT3D11, m_gfx->GetDevice());
	TwWindowSize(vpWidth, vpHeight);
	m_antTweakBar = TwNewBar("Real-Time Graphics");
	TwAddVarRW(m_antTweakBar, "Time Mod:", TW_TYPE_FLOAT, &m_timeModifier, "");
	TwAddVarRW(m_antTweakBar, "Current Cam:", TW_TYPE_INT8, &m_currentCamera, "");
	TwAddVarRW(m_antTweakBar, "FPS:", TW_TYPE_UINT32, &m_fps, "");

//#if _DEBUG
//	BasicLogger::WriteToConsole("GAME: Scene objects loaded.\n");
//#endif
}

void Game::Destroy(void)
{
	m_gfx->Destroy();
}

bool Game::Update(void)
{	

	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::Escape))
	{
		return false;
	}

	// RESET
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::R))
	{
		ResetGame();
	}

	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::S))
	{
		m_statDisplay = !m_statDisplay;
	}

	// TIME MANIPULATION
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::T))
	{
		if (m_input->IsKeyHeld(DirectX::Keyboard::Keys::LeftShift))
		{
			m_time->IncreaseModifier();
		}
		else
		{
			m_time->DecreaseModifier();
		}
	}

	// CAMERA SWAPPING
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F1))
	{
		m_mainCamera = m_camMgr->JumpToCamera(0);
	}
	else if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F2))
	{
		// DEBUG CAM
		m_mainCamera = m_camMgr->JumpToCamera(1);
	}
	else if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F3))
	{
		// Third cam
		m_mainCamera = m_camMgr->JumpToCamera(2);
	}
	else if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F4))
	{
		// Fourth cam
		m_mainCamera = m_camMgr->JumpToCamera(3);
	}
	
	// WIREFRAME MODE ENABLE
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F5))
	{
		m_wireFrameMode = !m_wireFrameMode;
	}
	
	// ANIMATION TOGGLE
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F11))
	{
		m_dragonfly->ToggleAnimation();
	}

	// Update Objects
	m_mainCamera->Update(m_input, m_time);
	m_dragonfly->Update(m_time);

	// Update Managers
	m_time->Update();
	m_input->UpdateStates();

	// Update ATB values
	m_timeModifier = m_time->GetCurrentModifier();
	m_currentCamera = m_camMgr->GetCurrentCameraID();
	m_fps = m_time->GetFramesPerSecond();

	return true;
}

void Game::Render(void)
{
	// Clear Screen
	m_gfx->ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);

	// Setup the Camera view
	m_mainCamera->Render(m_gfx);

	// Draw objects
	// STATIC OBJECTS
	m_platform->Render( m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	m_dome->Render(m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	m_twig->Render(m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);

	// DYNAMIC OBJECTS
	m_dragonfly->Render(m_gfx, m_time, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);

	if (m_statDisplay)
	{
		// Draw AntTweakBar
		TwDraw();
	}

	// Present buffer
	m_gfx->Present();

}

void Game::ResetGame(void)
{
	// Reset cameras
	//m_camMgr->Reset();

	m_time->Reset();

	// Reset only object with state
	m_dragonfly->Reset();
}
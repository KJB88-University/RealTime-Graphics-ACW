// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// ACW includes
#include "Game.h"
#include "BasicLogger.h"
#include "Shader.h"

Game::Game(void)
	:m_wireFrameMode(false)
{

}

Game::~Game(void)
{

}

void Game::Initialize(int vpWidth, int vpHeight, HWND hwnd, float nearClip, float farClip)
{
	// Graphics Manager
	m_gfx = new GraphicsManager();
	m_gfx->Initialize(vpWidth, vpHeight, hwnd);
	BasicLogger::WriteToConsole("GAME: Graphics Manager initialized.\n");

	// Time Manager
	m_time = new TimeManager();
	m_time->Initialize();
	BasicLogger::WriteToConsole("GAME: Time Manager initialized.\n");

	// Input Manager
	m_input = new InputManager();
	m_input->Initialize();
	BasicLogger::WriteToConsole("GAME: Input Manager initialized.\n");

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
	BasicLogger::WriteToConsole("GAME: Camera Manager initialized.\n");

	// Main Camera
	m_mainCamera = m_camMgr->GetMainCamera();
	//BasicLogger::WriteToConsole("GAME: Main Camera initialized.\n");

	BasicLogger::WriteToConsole("GAME: Scene objects loaded.\n");
}

void Game::Destroy(void)
{
	// DESTROY GAME OBJECTS
	// Main Camera
	m_mainCamera->Destroy();
	delete m_mainCamera;
	m_mainCamera = nullptr;

	// Platform
	m_platform->Destroy();
	delete m_platform;
	m_platform = nullptr;

	// Dome
	m_dome->Destroy();
	delete m_dome;
	m_dome = nullptr;

	// Dragonfly
	m_dragonfly->Destroy();
	delete m_dragonfly;
	m_dragonfly = nullptr;

	// Twig
	m_twig->Destroy();
	delete m_twig;
	m_twig = nullptr;

	// DESTROY MANAGERS
	// Time
	m_time->Destroy();
	delete m_time;
	m_time = nullptr;

	// Camera
	m_camMgr->Destroy();
	delete m_camMgr;
	m_camMgr = nullptr;

	// Input
	m_input->Destroy();
	delete m_input;
	m_input = nullptr;

	// Graphics
	m_gfx->Destroy();
	delete m_gfx;
	m_gfx = nullptr;
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
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F6))
	{
		m_dragonfly->ToggleAnimation();
	}

	// Update Objects
	m_mainCamera->Update(m_input, m_time);
	m_dragonfly->Update(m_time);

	// Update Managers
	m_time->Update();
	m_input->UpdateStates();

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
	m_platform->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	m_dome->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	m_twig->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);

	// DYNAMIC OBJECTS
	m_dragonfly->Render(m_gfx, m_time, *m_gfx->GetWorldMatrix(), m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);

	// Present buffer
	m_gfx->Present();

}

void Game::ResetGame(void)
{
	// Reset cameras
	m_camMgr->Reset();

	// Reset only object with state
	m_dragonfly->Reset();
}
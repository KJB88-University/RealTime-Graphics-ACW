// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// ACW includes
#include "Game.h"
#include "BasicLogger.h"

Game::Game(void)
{

}

Game::~Game(void)
{

}

void Game::Initialize(int vpWidth, int vpHeight, HWND hwnd)
{
	float nearClip, farClip;
	nearClip = 0.01f;
	farClip = 1000.0f;

	// MANAGERS
	// Graphics Manager
	m_gfx = new GraphicsManager();
	m_gfx->Initialize(vpWidth, vpHeight, hwnd);
	BasicLogger::WriteToConsole("GAME: Graphics Manager initialized.\n");

	// Camera Manager
	m_camMgr = new CameraManager();
	m_camMgr->Initialize(Vector3(0.0f, 0.0f, -10.0f), vpWidth, vpHeight, nearClip, farClip);
	BasicLogger::WriteToConsole("GAME: Camera Manager initialized.\n");

	// Time Manager
	m_time = new TimeManager();
	m_time->Initialize();
	BasicLogger::WriteToConsole("GAME: Time Manager initialized.\n");

	// Input Manager
	m_input = new InputManager();
	m_input->Initialize();
	BasicLogger::WriteToConsole("GAME: Input Manager initialized.\n");

	// GAME OBJECTS
	// Main Camera
	//m_mainCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
	//m_mainCamera->Initialize(Vector3(0.0f, 0.0f, -10.0f), vpWidth, vpHeight, 0.01f, 1000.0f);
	m_mainCamera = m_camMgr->GetMainCamera();
	BasicLogger::WriteToConsole("GAME: Main Camera initialized.\n");

	// DEBUG Tiny
	m_tiny = new Tiny();
	m_tiny->Initialize(m_gfx, L"tiny.sdkmesh");
	BasicLogger::WriteToConsole("GAME: Tiny initialized.\n");

	// Platform (Ground)
	m_platform = new Platform(Vector3(0.0f, 0.0f, -10.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
	m_platform->Initialize(m_gfx);
	BasicLogger::WriteToConsole("GAME: Platform initialized.\n");
}

void Game::Destroy(void)
{
	m_tiny->Destroy();
	delete m_tiny;
	m_tiny = nullptr;

	m_mainCamera->Destroy();
	delete m_mainCamera;
	m_mainCamera = nullptr;

	m_time->Destroy();
	delete m_time;
	m_time = nullptr;

	m_input->Destroy();
	delete m_input;
	m_input = nullptr;

	m_gfx->Destroy();
	delete m_gfx;
	m_gfx = nullptr;
}

void Game::Update(void)

{	// Update frame time
	m_time->Update();

	// Get new input state
	m_kbState = m_input->GetKeyboardState();

	if (m_kbState.F1)
	{
		m_camMgr->JumpToCamera(0);
		m_mainCamera = m_camMgr->GetMainCamera();
	}
	else if (m_kbState.F2)
	{
		m_camMgr->JumpToCamera(1);
		m_mainCamera = m_camMgr->GetMainCamera();
	}
	else if (m_kbState.F3)
	{
		// Third cam
	}
	else if (m_kbState.F4)
	{
		// Fourth cam
	}

	// Update Objects
	m_mainCamera->Update(m_input, m_time);
}

void Game::Render(void)
{
	// Clear Screen
	m_gfx->ClearScreen(0.5f, 0.5f, 0.5f, 1.0f);

	m_mainCamera->Render(m_gfx);

	// DO DRAWING
	m_platform->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix());

	//m_tiny->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix());

	// Present buffer
	m_gfx->Present();
}
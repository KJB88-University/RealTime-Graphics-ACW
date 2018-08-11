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
{
	m_wireFrameMode = false;
}

Game::~Game(void)
{

}

//void Game::PostProcess()
//{

//}

void Game::Initialize(int vpWidth, int vpHeight, HWND hwnd, float nearClip, float farClip)
{
	// MANAGERS
	// Graphics Manager
	m_gfx = new GraphicsManager();
	m_gfx->Initialize(vpWidth, vpHeight, hwnd);
	BasicLogger::WriteToConsole("GAME: Graphics Manager initialized.\n");

	//Shader* shader = new Shader();
	//shader->Initialize(m_gfx, L"BloomCombine.cso", L"BloomCombine.cso");

	// Camera Manager
	m_camMgr = new CameraManager();
	m_camMgr->Initialize(Vector3(0.0f, 0.0f, -1.0f), vpWidth, vpHeight, nearClip, farClip);
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
	//m_tiny = new Tiny();
	//m_tiny->Initialize(m_gfx);
	//BasicLogger::WriteToConsole("GAME: Tiny initialized.\n");
	
	// Platform (Ground)
	m_platform = new Platform(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.0f, 4.0f, 50.0f));
	m_platform->Initialize(m_gfx);
	BasicLogger::WriteToConsole("GAME: Platform initialized.\n");

	// Dome (Hemisphere)
	m_dome = new Dome(Vector3(0.0f, -5.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(50.75f, 50.75f, 50.75f));
	m_dome->Initialize(m_gfx);
	BasicLogger::WriteToConsole("GAME: Dome initialized.\n");

	// Dragonfly
	m_dragonfly = new Dragonfly(Vector3(0.0f, 2.0f, -5.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
	m_dragonfly->Initialize(m_gfx);
	BasicLogger::WriteToConsole("GAME: Dragonfly initialized.\n");
}

void Game::Destroy(void)
{
	// DESTROY GAME OBJECTS
	// DEBUG Tiny
	m_tiny->Destroy();
	delete m_tiny;
	m_tiny = nullptr;

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

	// DESTROY MANAGERS
	// Time
	m_time->Destroy();
	delete m_time;
	m_time = nullptr;

	// Input
	m_input->Destroy();
	delete m_input;
	m_input = nullptr;

	// Graphics
	m_gfx->Destroy();
	delete m_gfx;
	m_gfx = nullptr;
}

void Game::Update(void)
{	
	// CAMERA SWAPPING
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F1))
	{
		m_camMgr->JumpToCamera(0);
		m_mainCamera = m_camMgr->GetMainCamera();
	}
	else if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F2))
	{
		// DEBUG CAM
		m_camMgr->JumpToCamera(1);
		m_mainCamera = m_camMgr->GetMainCamera();
	}
	else if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F3))
	{
		// Third cam
	}
	else if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F4))
	{
		// Fourth cam
	}
	
	// WIREFRAME MODE ENABLE
	if (m_input->IsKeyDown(DirectX::Keyboard::Keys::F5))
	{
		m_wireFrameMode = !m_wireFrameMode;
	}
	
	// Update Objects
	m_mainCamera->Update(m_input, m_time);

	m_dragonfly->Update(m_time);

	// Update frame time
	m_time->Update();
	m_input->UpdateStates();
}

void Game::Render(void)
{
	// Clear Screen
	m_gfx->ClearScreen(0.5f, 0.5f, 0.5f, 1.0f);

	// Render the view via the camera
	m_mainCamera->Render(m_gfx);

	// Draw objects
	// START
	
	m_platform->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	m_dome->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	m_dragonfly->Render(m_gfx, m_time, *m_gfx->GetWorldMatrix(), m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);
	//m_tiny->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix(), m_wireFrameMode);

	//END

	// Present buffer
	m_gfx->Present();

}
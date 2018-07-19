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
	// MANAGERS
	// Graphics
	m_gfx = new GraphicsManager();
	m_gfx->Initialize(vpWidth, vpHeight, hwnd);
	BasicLogger::WriteToConsole("GAME: Graphics Manager initialized.\n");

	// Camera
	m_mainCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
	m_mainCamera->Initialize(vpWidth, vpHeight, 0.01f, 1000.0f);
	BasicLogger::WriteToConsole("GAME: Main Camera initialized.\n");

	// Time
	m_time = new TimeManager();
	m_time->Initialize();
	BasicLogger::WriteToConsole("GAME: Time Manager initialized.\n");

	// GAME OBJECTS

	// Debug Tiny
	m_tiny = new Tiny();
	m_tiny->Initialize(m_gfx->GetDevice(), L"tiny.sdkmesh", *m_gfx->GetFXFactory());
	BasicLogger::WriteToConsole("GAME: Tiny initialized.\n");

	// Platform (Ground)
	m_platform = new Platform();
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

	m_gfx->Destroy();
	delete m_gfx;
	m_gfx = nullptr;
}

void Game::Update(void)
{
	m_time->Update();
}

void Game::Render(void)
{
	// Clear Screen
	m_gfx->ClearScreen(0.5f, 0.5f, 0.5f, 1.0f);

	// DO DRAWING
	m_platform->Render(m_gfx, m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix());
	//m_tiny->Render(m_gfx->GetDeviceContext(), m_gfx->GetCommonStates(), m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix());
	// Present buffer
	m_gfx->Present();
}
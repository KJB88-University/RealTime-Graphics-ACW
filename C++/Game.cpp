// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

// ACW includes
#include "Game.h"


Game::Game(void)
{

}

Game::~Game(void)
{

}

void Game::Initialize(GraphicsManager* gm)
{
	m_tiny = new Tiny();
	m_tiny->Initialize(gm->GetDevice(), L"tiny.sdkmesh", *gm->GetFXFactory());

	m_mainCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
	m_mainCamera->Initialize(800, 600, 0.01f, 1000.0f);
}

void Game::Destroy(void)
{

}

void Game::Update(void)
{

}

void Game::Render(GraphicsManager* gm)
{
	// Clear Screen
	gm->ClearScreen(0.5f, 0.5f, 0.5f, 1.0f);

	// DO DRAWING
	m_tiny->Render(gm->GetDeviceContext(), gm->GetCommonStates(), m_mainCamera->GetProjMatrix(), m_mainCamera->GetViewMatrix());

	// Present buffer
	gm->Present();
}
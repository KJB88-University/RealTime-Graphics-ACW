#include "GraphicsManager.h"

using namespace DirectX::SimpleMath;

GraphicsManager::GraphicsManager(void)
	: m_gfx(nullptr), m_world(nullptr)
{

}

GraphicsManager::~GraphicsManager(void)
{
	delete m_gfx;
	m_gfx = nullptr;

	delete m_world;
	m_world = nullptr;
}

void GraphicsManager::Initialize(HWND const hwnd)
{
	// Initialize DXTK Module
	m_gfx = new DXTKModule();
	m_gfx->Initialize(hwnd);
}

void GraphicsManager::Destroy(void)
{
	m_gfx->Destroy();
}

ID3D11Device* GraphicsManager::GetDevice() const
{
	return m_gfx->GetDevice();
}

ID3D11DeviceContext* GraphicsManager::GetDeviceContext() const
{
	return m_gfx->GetDeviceContext();
}

// Return a ptr to the Common States
DirectX::CommonStates* GraphicsManager::GetCommonStates(void) const
{
	return m_gfx->GetCommonStates();
}

// Return a ptr to the FX Factory
DirectX::IEffectFactory* GraphicsManager::GetFXFactory(void) const
{
	return m_gfx->GetFXFactory();
}

// Return a ptr to the Basic Effect
DirectX::BasicEffect* GraphicsManager::GetBasicEffect(void) const
{
	return m_gfx->GetBasicEffect();
}

//Matrix* GraphicsManager::GetProjectionMatrix(void) const
//{
//	return m_projection;
//}
//
Matrix* GraphicsManager::GetWorldMatrix(void) const
{
	return m_world;
}

void GraphicsManager::ClearScreen(float const r, float const g, float const b, float const a) const
{
	m_gfx->ClearScreen(r, g, b, a);
}

void GraphicsManager::Present(void) const
{
	m_gfx->Present();
}

#include "GraphicsManager.h"

using namespace DirectX::SimpleMath;

GraphicsManager::GraphicsManager(void)
	: m_gfx(nullptr)
{

}

GraphicsManager::~GraphicsManager(void)
{

}

void GraphicsManager::Initialize(int vpWidth, int vpHeight, HWND hwnd)
{

	// Initialize DXTK Module
	m_gfx = new DXTKModule();
	m_gfx->Initialize(hwnd);

}

void GraphicsManager::Destroy(void)
{
	m_gfx->Destroy();
	delete m_gfx;
	m_gfx = nullptr;
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

Matrix* GraphicsManager::GetProjectionMatrix(void)
{
	return &m_projection;
}

Matrix* GraphicsManager::GetWorldMatrix(void)
{
	return &m_world;
}

void GraphicsManager::ClearScreen(float r, float g, float b, float a)
{
	m_gfx->ClearScreen(r, g, b, a);
}

void GraphicsManager::Present(void)
{
	m_gfx->Present();
}

//#include "GraphicsManager.h"
//
//// Code adapted from RasterTek tutorials (www.rastertek.com)
//// DirectX11 - Series 2 - Tutorial 02.
//// Website last updated [03/01/2016].
//// Visited on [02/01/2018].
//// Adapted by: Kevin Barr
//
//GraphicsManager::GraphicsManager(void)
//	: m_d3d(nullptr)
//{
//
//}
//
//GraphicsManager::~GraphicsManager(void)
//{
//
//}
//
//void GraphicsManager::Initialize(int vpWidth, int vpHeight, HWND hwnd)
//{
//
//	// Initialize DXTK Module
//	m_gfx = new DXTKModule();
//	m_gfx->Initialize(vpWidth, vpHeight,
//		VSYNC_ENABLED,
//		hwnd,
//		FULL_SCREEN,
//		SCREEN_DEPTH, SCREEN_NEAR);
//
//}
//
//void GraphicsManager::OnDestroy(void)
//{
//	m_gfx->Destroy();
//	delete m_d3d;
//	m_d3d = nullptr;
//}
//
//ID3D11Device* GraphicsManager::GetDevice() const
//{
//	return m_d3d->GetDevice();
//}
//
//ID3D11DeviceContext* GraphicsManager::GetContext() const
//{
//	return m_d3d->GetDeviceContext();
//}
//
//void GraphicsManager::ClearScreen(float r, float g, float b, float a)
//{
//	m_gfx->ClearRender(r, g, b, a);
//}
//
//void GraphicsManager::DisplayFrame(void)
//{
//	m_gfx->DisplayFrame();
//}

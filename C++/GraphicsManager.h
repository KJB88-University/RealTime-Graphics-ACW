//#pragma once
//#include "DXTKModule.h"
//
//// Code adapted from RasterTek tutorials (www.rastertek.com)
//// DirectX11 - Series 2 - Tutorial 02.
//// Website last updated [03/01/2016].
//// Visited on [02/01/2018].
//// Adapted by: Kevin Barr
//
//const bool FULL_SCREEN = false;
//const bool VSYNC_ENABLED = true;
//const float SCREEN_DEPTH = 1000.0f;
//const float SCREEN_NEAR = 0.1f;
//
//class GraphicsManager
//{
//public:
//
//
//	GraphicsManager(void);
//	~GraphicsManager(void);
//
//	void Initialize(int, int, HWND);
//	void OnDestroy(void);
//
//	void ClearScreen(float r, float g, float b, float a);
//	void DisplayFrame(void);
//
//	// Return pointers to device and context
//	ID3D11Device* GetDevice(void) const;
//	ID3D11DeviceContext* GetContext(void) const;
//
//private:
//
//	DXTKModule* m_d3d;
//};
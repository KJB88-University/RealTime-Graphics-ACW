#pragma once
#include "DXTKModule.h"

const bool FULL_SCREEN = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsManager
{
public:


	GraphicsManager(void);
	~GraphicsManager(void);

	void Initialize(int vpWidth, int vpHeight, HWND hwnd);
	void Destroy(void);

	void ClearScreen(float r, float g, float b, float a);
	void Present(void);

	// Return pointers to device and context
	ID3D11Device* GetDevice(void) const;
	ID3D11DeviceContext* GetDeviceContext(void) const;

	// Return a ptr to the Common States
	DirectX::CommonStates* GetCommonStates(void) const;

	// Return a ptr to the FX Factory
	DirectX::IEffectFactory* GetFXFactory(void) const;

	// Return a ptr to the Basic Effect
	DirectX::BasicEffect* GetBasicEffect(void) const;

private:

	DXTKModule* m_gfx;
};
#pragma once
#include "DXTKModule.h"
#include <d3d11.h>
#include <SimpleMath.h>

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

	// Matrix Getters
	DirectX::SimpleMath::Matrix* GetProjectionMatrix(void);
	DirectX::SimpleMath::Matrix* GetWorldMatrix(void);

private:

	DXTKModule* m_gfx;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_projection;
};
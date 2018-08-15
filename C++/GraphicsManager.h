#pragma once
#include "DXTKModule.h"
#include <d3d11.h>
#include <SimpleMath.h>
#include "CullMode.h"
class GraphicsManager
{
public:

	GraphicsManager(void);
	~GraphicsManager(void);


	void Initialize(HWND hwnd);
	void Destroy(void);

	void ClearScreen(float r, float g, float b, float a) const;
	void Present(void) const;

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
	//DirectX::SimpleMath::Matrix* GetProjectionMatrix(void) const;
	DirectX::SimpleMath::Matrix* GetWorldMatrix(void) const;

private:

	DXTKModule* m_gfx;

	DirectX::SimpleMath::Matrix* m_world;
	//DirectX::SimpleMath::Matrix* m_projection;

	GraphicsManager(const GraphicsManager& other)=delete;
	GraphicsManager& GraphicsManager::operator=(const GraphicsManager& other)=delete;
};
#pragma once

// STD Includes
#include <memory>

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <CommonStates.h>
#include <Effects.h>

// ACW Includes
#include "CullMode.h"

class DXTKModule
{

public:
	DXTKModule(void);
	~DXTKModule(void);

	// Initialize resources
	void Initialize(HWND hwnd);

	// Destroy resources
	void Destroy(void);

	// Return a ptr to the D3D11 Device
	ID3D11Device* GetDevice(void) const;

	// Return a ptr to the D3D11 Device Context
	ID3D11DeviceContext* GetDeviceContext(void) const;

	// Return a ptr to the Common States
	DirectX::CommonStates* GetCommonStates(void) const;

	// Return a ptr to the FX Factory
	DirectX::IEffectFactory* GetFXFactory(void) const;

	// Return a ptr to the Basic Effect
	DirectX::BasicEffect* GetBasicEffect(void) const;

	// Change culling mode
	void SetCullMode(CULLMODE mode);

	void ClearScreen(float r, float g, float b, float a) const;

	void Present(void) const;

private:

	// Initialize non-DXTK resources
	void InitializeD3DResources(HWND hwnd);

	// Initialize DXTK-specific resources
	void InitializeDXTKResources(void);

	// D3D Resources
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencil;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;

	// DXTK Resources
	std::unique_ptr<DirectX::CommonStates> m_commonStates;
	std::unique_ptr<DirectX::IEffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	ID3D11InputLayout* m_batchLayout;
};
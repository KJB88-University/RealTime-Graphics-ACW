
// DXTK Includes
#include <VertexTypes.h>

// ACW Includes
#include "DXTKModule.h"
#include "BasicLogger.h"

DXTKModule::DXTKModule(void)
	:m_featureLevel(D3D_FEATURE_LEVEL_11_0), m_driverType(D3D_DRIVER_TYPE_HARDWARE)
{

}

DXTKModule::~DXTKModule(void)
{

}

void DXTKModule::Initialize(HWND hwnd)
{
	InitializeD3DResources(hwnd);
	InitializeDXTKResources();
}

void DXTKModule::Destroy(void)
{
	if (m_deviceContext)
	{
		m_deviceContext->ClearState();
	}

	if (m_batchLayout)
	{
		m_batchLayout->Release();
	}

	if (m_depthStencilView)
	{
		m_depthStencilView->Release();
	}

	if (m_depthStencil)
	{
		m_depthStencil->Release();
	}

	if (m_renderTargetView)
	{
		m_renderTargetView->Release();
	}

	if (m_swapChain)
	{
		m_swapChain->Release();
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
	}

	if (m_device)
	{
		m_device->Release();
	}
}

ID3D11Device* DXTKModule::GetDevice(void) const
{
	return m_device;
}

ID3D11DeviceContext* DXTKModule::GetDeviceContext(void) const
{
	return m_deviceContext;
}

const DirectX::CommonStates* DXTKModule::GetCommonStates(void) const
{
	return m_commonStates.get();
}

const DirectX::IEffectFactory* DXTKModule::GetFXFactory(void) const
{
	return m_fxFactory.get();
}

const DirectX::BasicEffect* DXTKModule::GetBasicEffect(void) const
{
	return m_batchEffect.get();
}

void DXTKModule::InitializeD3DResources(HWND hwnd)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(hwnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(nullptr, m_driverType, nullptr, createDeviceFlags, &m_featureLevel, 1,
		D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, &m_featureLevel, &m_deviceContext);

	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("D3D: Failed to create device and swapchain.\n");
	}

	// Ptr to back buffer
	ID3D11Texture2D* backBuffer = nullptr;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("D3D: Failed to create back buffer.\n");
	}
	// Create a render target view
	hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->Release();
	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("D3D: Failed to create render target view.\n");
	}

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = m_device->CreateTexture2D(&descDepth, nullptr, &m_depthStencil);
	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("D3D: Failed to create depth stencil.\n");
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_device->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);
	if (FAILED(hr))
	{
		BasicLogger::WriteToConsole("D3D: Failed to create depth stencil view.\n");
	}

	// Bind/make active views
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &vp);
}

void DXTKModule::InitializeDXTKResources(void)
{
	HRESULT hr;

	m_commonStates.reset(new DirectX::CommonStates(m_device));
	m_fxFactory.reset(new DirectX::EffectFactory(m_device));

	m_batchEffect.reset(new DirectX::BasicEffect(m_device));
	m_batchEffect->SetVertexColorEnabled(true);

	{
		void const* shaderByteCode;
		size_t byteCodeLength;

		m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		hr = m_device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
			DirectX::VertexPositionColor::InputElementCount,
			shaderByteCode, byteCodeLength,
			&m_batchLayout);
		if (FAILED(hr))
		{
			BasicLogger::WriteToConsole("DXTK: Failed to load shaders.\n");
		}
	}
}

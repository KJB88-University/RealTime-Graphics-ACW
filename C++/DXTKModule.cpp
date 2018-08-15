// DXTK Includes
#include <VertexTypes.h>
#include <SimpleMath.h>

// ACW Includes
#include "DXTKModule.h"
#include "BasicLogger.h"
#include "CullMode.h"

using namespace DirectX::SimpleMath;

DXTKModule::DXTKModule(void)
	: m_device(nullptr), m_deviceContext(nullptr), m_swapChain(nullptr), m_renderTargetView(nullptr), 
	m_depthStencil(nullptr), m_depthStencilView(nullptr), 
	m_driverType(D3D_DRIVER_TYPE_HARDWARE), m_featureLevel(D3D_FEATURE_LEVEL_11_0), m_batchLayout(nullptr)
{

}

DXTKModule::~DXTKModule(void)
{
	delete m_batchLayout;
	m_batchLayout = nullptr;

	delete m_depthStencilView;
	m_depthStencilView = nullptr;

	delete m_depthStencil;
	m_depthStencil = nullptr;

	delete m_renderTargetView;
	m_renderTargetView = nullptr;

	delete m_swapChain;
	m_swapChain = nullptr;

	delete m_deviceContext;
	m_deviceContext = nullptr;

	delete m_device;
	m_device = nullptr;
}

void DXTKModule::Initialize(HWND const hwnd)
{
	InitializeD3DResources(hwnd);
	InitializeDXTKResources();
}

void DXTKModule::Destroy(void)
{
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

ID3D11Device* const DXTKModule::GetDevice(void) const
{
	return m_device;
}

ID3D11DeviceContext* const DXTKModule::GetDeviceContext(void) const
{
	return m_deviceContext;
}

DirectX::CommonStates* DXTKModule::GetCommonStates(void) const
{
	return m_commonStates.get();
}

DirectX::IEffectFactory* DXTKModule::GetFXFactory(void) const
{
	return m_fxFactory.get();
}

DirectX::BasicEffect* DXTKModule::GetBasicEffect(void) const
{
	return m_basicEffect.get();
}

void DXTKModule::InitializeD3DResources(HWND const hwnd)
{
	HRESULT hr;

	RECT rc;
	GetClientRect(hwnd, &rc);
	const UINT width = rc.right - rc.left;
	const UINT height = rc.bottom - rc.top;

	D3D_FEATURE_LEVEL const featureLevel = D3D_FEATURE_LEVEL_11_0;

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

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, nullptr, &m_deviceContext);

	// Ptr to back buffer
	ID3D11Texture2D* backBuffer = nullptr;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

	// Create a render target view
	hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
	backBuffer->Release();

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

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_device->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);

	// Bind/make active views
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &vp);
}

void DXTKModule::InitializeDXTKResources(void)
{
	HRESULT hr;

	// (Make Unique workaround)
	// Reset the current unique_ptr and initialize it to a new ptr to the CommonStates obj
	m_commonStates.reset(new DirectX::CommonStates(m_device));

	// (Make Unique workaround)
	// Reset the current unique_ptr and initialize it to a new ptr to the EffectFactory obj
	m_fxFactory.reset(new DirectX::EffectFactory(m_device));

	m_basicEffect.reset(new DirectX::BasicEffect(m_device));
	m_basicEffect->SetVertexColorEnabled(true);

	{
		void const* shaderByteCode;
		size_t byteCodeLength;

		m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		hr = m_device->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			shaderByteCode, byteCodeLength,
			&m_batchLayout);
	}
}

void DXTKModule::ClearScreen(float const r, float const g, float const b, float const a) const
{
	float colors[4];
	colors[0] = r;
	colors[1] = g;
	colors[2] = b;
	colors[3] = a;

	// Clear the back buffer
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, colors);

	// Clear the depth buffer to 1.0 (max depth)
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DXTKModule::Present(void) const
{
	m_swapChain->Present(0, 0);
}
// DXTK Includes
#include <VertexTypes.h>
#include <SimpleMath.h>

// ACW Includes
#include "DXTKModule.h"
#include "BasicLogger.h"
#include "CullMode.h"

using namespace DirectX::SimpleMath;

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
	BasicLogger::WriteToConsole("D3D: Resources loaded.\n");

	InitializeDXTKResources();
	BasicLogger::WriteToConsole("DXTK: Resources loaded.\n");
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

void DXTKModule::InitializeD3DResources(HWND hwnd)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(hwnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	/*
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
*/

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

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

	// (Make Unique workaround)
	// Reset the current unique_ptr and initialize it to a new ptr to the CommonStates obj
	m_commonStates.reset(new DirectX::CommonStates(m_device));

	// (Make Unique workaround)
	// Reset the current unique_ptr and initialize it to a new ptr to the EffectFactory obj
	m_fxFactory.reset(new DirectX::EffectFactory(m_device));

	m_basicEffect.reset(new DirectX::BasicEffect(m_device));
	m_basicEffect->SetVertexColorEnabled(true);
	//m_basicEffect->SetLightEnabled(0, true);

	//DirectX::SimpleMath::Vector4 light { 0.0f, 0.0f, 0.0f, 0.0f };
	//m_basicEffect->SetLightDirection(0, light);

	//light = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	//m_basicEffect->SetAmbientLightColor(light);

	{
		void const* shaderByteCode;
		size_t byteCodeLength;

		m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

		hr = m_device->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			shaderByteCode, byteCodeLength,
			&m_batchLayout);
		if (FAILED(hr))
		{
			BasicLogger::WriteToConsole("DXTK: Failed to load shaders.\n");
		}
	}
}

void DXTKModule::SetCullMode(CULLMODE mode)
{
	// Vars
	D3D11_RASTERIZER_DESC rd;
	ID3D11RasterizerState* rs;

	// Get Rasterizer State
	m_deviceContext->RSGetState(&rs);

	// Pull out the descripto for the state
	rs->GetDesc(&rd);

	// Decide how our culling works
	switch (mode)
	{
	case CULLBACK:
		rd.CullMode = D3D11_CULL_BACK;
		break;
	case CULLFRONT:
		rd.CullMode = D3D11_CULL_FRONT;
		break;
	case CULLNONE:
		rd.CullMode = D3D11_CULL_NONE;
		break;

	default:
		break;
	}

	// Create a new state from the descriptor
	m_device->CreateRasterizerState(&rd, &rs);

	// Set the state to active
	m_deviceContext->RSSetState(rs);
}

void DXTKModule::ClearScreen(float r, float g, float b, float a) const
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
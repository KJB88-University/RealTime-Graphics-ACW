#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <memory>
#include <Model.h>

class Tiny
{

public:

	Tiny(void);
	~Tiny(void);

	void Initialize(ID3D11Device* device, const wchar_t* fileName, DirectX::IEffectFactory& fxFactory);
	void Destroy(void);
	void Update(void);
	void Render(ID3D11DeviceContext* context, DirectX::CommonStates* g_States);

private:

	std::unique_ptr<DirectX::Model> m_tiny;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;
};
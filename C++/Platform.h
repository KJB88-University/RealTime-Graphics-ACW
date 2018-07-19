#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

// ACW Includes
#include "GraphicsManager.h"

class Platform
{

public:

	Platform(void);
	~Platform(void);

	void Initialize(GraphicsManager* gm);
	void Destroy(void);
	void Update(void);
	void Render(GraphicsManager* gm, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view);

private:

	// Transform
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;

	std::unique_ptr<DirectX::GeometricPrimitive> m_platform;
	ID3D11ShaderResourceView* m_texture;
};
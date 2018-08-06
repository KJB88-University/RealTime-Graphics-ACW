#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

// ACW Includes
#include "GameObject.h"

class Platform : GameObject
{

public:

	Platform(void);
	Platform(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
	Platform(const Platform& other);
	~Platform(void);

	virtual void Initialize(GraphicsManager* gm) override;
	virtual void Destroy(void) override;
	void Update(TimeManager* time) ;
	void Render(GraphicsManager* gm, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view, bool wireFrame);

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_platform;
	ID3D11ShaderResourceView* m_texture;
};
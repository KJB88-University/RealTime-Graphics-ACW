#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

// ACW Includes
#include "GameObject.h"

class Platform : public GameObject
{

public:

	Platform(void);
	Platform(DirectX::SimpleMath::Vector3& const position, DirectX::SimpleMath::Vector3& const rotation, DirectX::SimpleMath::Vector3& const scale);
	~Platform(void);

	virtual void Initialize(GraphicsManager* const gm) override;
	virtual void Destroy(void) override;
	//void Update(TimeManager* time) ;
	void Render(const DirectX::SimpleMath::Matrix& projection, const DirectX::SimpleMath::Matrix& view, bool const wireFrame);

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_platform;
	ID3D11ShaderResourceView* m_texture;

	Platform(const Platform& other)=delete;
};
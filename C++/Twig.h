#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

// ACW Includes
#include "GameObject.h"

class Twig : GameObject
{
public:
	Twig(void);
	Twig(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
	Twig(const Twig& other);
	~Twig(void);

	virtual void Initialize(GraphicsManager* gfx) override;
	virtual void Destroy(void) override;

	void Update(TimeManager* time);
	void Render(GraphicsManager* gfx, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view,  bool wireFrame);

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_twig;
};
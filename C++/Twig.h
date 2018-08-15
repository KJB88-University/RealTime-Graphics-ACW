#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

// ACW Includes
#include "GameObject.h"

class Twig : public GameObject
{
public:
	Twig(void);
	Twig(DirectX::SimpleMath::Vector3& const position, DirectX::SimpleMath::Vector3& const rotation, DirectX::SimpleMath::Vector3& const scale);
	~Twig(void);

	virtual void Initialize(GraphicsManager* const gfx) override;
	virtual void Destroy(void) override;

	//void Update(TimeManager* time);
	void Render(const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Matrix& view,  bool wireFrame);

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_twig;

	Twig(const Twig& other)=delete;
};
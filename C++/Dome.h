#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <GeometricPrimitive.h>

// ACW Includes
#include "GraphicsManager.h"
#include "TimeManager.h"
#include "GameObject.h"

class Dome : public GameObject
{
public:

	Dome(void);
	Dome(DirectX::SimpleMath::Vector3& const position, DirectX::SimpleMath::Vector3& const rotation, DirectX::SimpleMath::Vector3& const scale);

	~Dome(void);

	virtual void Initialize(GraphicsManager* gm) override;
	virtual void Destroy(void) override;

	//void Update(TimeManager* time);
	void Render(const DirectX::SimpleMath::Matrix& projection, const DirectX::SimpleMath::Matrix& view, bool wireFrame);

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_dome;

	Dome(const Dome& other)=delete;
};
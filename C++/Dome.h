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

class Dome : GameObject
{
public:

	Dome(void);
	Dome(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
	Dome(const Dome& other);
	~Dome(void);

	virtual void Initialize(GraphicsManager* gm) override;
	virtual void Destroy(void) override;
	void Update(TimeManager* time);
	void Render(GraphicsManager* gm, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view, bool wireFrame);

private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_dome;
};
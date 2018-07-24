#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "GraphicsManager.h"
#include "TimeManager.h"

class Dome
{
public:

	Dome(void);
	~Dome(void);

	void Initialize(GraphicsManager* gfx);
	void Destroy(void);
	void Update(TimeManager* time);
	void Render(GraphicsManager* gfx);

private:

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;
};
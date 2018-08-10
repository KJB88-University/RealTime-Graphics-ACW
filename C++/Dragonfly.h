#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <Model.h>

// ACW Includes
#include "GameObject.h"
#include "DragonflyLegs.h"
#include "DragonflyWings.h"

class Dragonfly : GameObject
{

public:

	Dragonfly(void);
	Dragonfly(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
	Dragonfly(const Dragonfly& other);
	~Dragonfly(void);

	virtual void Initialize(GraphicsManager* gfx) override;
	virtual void Destroy(void) override;

	void Update(TimeManager* time);
	void Render(GraphicsManager* gfx, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view, bool wireFrame);

private:

	DirectX::SimpleMath::Matrix m_world;

	std::unique_ptr<DirectX::Model> m_body;
	std::unique_ptr<DirectX::Model> m_leftWing;
	std::unique_ptr<DirectX::Model> m_rightWing;
	std::unique_ptr<DirectX::Model> m_legs;
};
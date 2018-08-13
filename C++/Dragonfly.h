#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <Model.h>

// ACW Includes
#include "GameObject.h"

class Dragonfly : public GameObject
{

public:

	Dragonfly(void);
	Dragonfly(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
	Dragonfly(const Dragonfly& other);
	~Dragonfly(void);

	virtual void Initialize(GraphicsManager* gfx) override;
	virtual void Destroy(void) override;

	void Update(TimeManager* time);
	void Render(GraphicsManager* gfx, TimeManager* time, DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view, bool wireFrame);

	void ToggleAnimation(void);

private:

	bool playAnimation = false;
	bool upperLimit = false;

	std::unique_ptr<DirectX::Model> m_body;
	std::unique_ptr<DirectX::Model> m_leftWing;
	std::unique_ptr<DirectX::Model> m_rightWing;
	std::unique_ptr<DirectX::Model> m_frontLegs;
	std::unique_ptr<DirectX::Model> m_midLegs;
	std::unique_ptr<DirectX::Model> m_backLegs;
};
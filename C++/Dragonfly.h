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
	Dragonfly(DirectX::SimpleMath::Vector3& const position, DirectX::SimpleMath::Vector3& const rotation, DirectX::SimpleMath::Vector3& const scale);
	~Dragonfly(void);

	virtual void Initialize(GraphicsManager* gfx) override;
	virtual void Destroy(void) override;
	virtual void Reset(void) override;

	void Update(const TimeManager* const time);
	void Render(const GraphicsManager* const gfx, const TimeManager* const time, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Matrix& view, bool wireFrame) const;

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

	Dragonfly(const Dragonfly& other) = delete;
	Dragonfly& Dragonfly::operator=(Dragonfly& other) = delete;
};
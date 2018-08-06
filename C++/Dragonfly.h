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
	void Render(GraphicsManager* gfx, Matrix* world, Matrix* proj, Matrix* view, bool wireFrame);

private:

	std::unique_ptr<DirectX::Model> m_body;
	DragonflyWings* m_wings;
	DragonflyLegs* m_legs;
};
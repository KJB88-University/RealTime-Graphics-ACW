#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <Model.h>
#include <SimpleMath.h>

// ACW Includes
#include "GameObject.h"
#include "GraphicsManager.h"

class Tiny : GameObject
{

public:

	Tiny(void);
	~Tiny(void);

	virtual void Initialize(GraphicsManager* gfx) override;
	virtual void Destroy(void) override;
	void Update(TimeManager* time);
	void Render(GraphicsManager* gfx, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view, bool wireFrame);

private:

	std::unique_ptr<DirectX::Model> m_tiny;
};
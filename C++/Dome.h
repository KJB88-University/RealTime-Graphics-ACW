#pragma once

// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "GraphicsManager.h"
#include "TimeManager.h"
#include "GameObject.h"

class Dome : GameObject
{
public:

	Dome(void);
	~Dome(void);

	virtual void Initialize(GraphicsManager* gm) override;
	virtual void Destroy(void) override;
	virtual void Update(TimeManager* time) override;
	virtual void Render(GraphicsManager* gm, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view, bool wireFrame) override;

private:

};
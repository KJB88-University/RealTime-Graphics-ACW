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

	void Initialize(GraphicsManager* gfx, const wchar_t* fileName);
	virtual void Destroy(void) override;
	virtual void Update(TimeManager* time) override;
	virtual void Render(GraphicsManager* gfx, DirectX::SimpleMath::Matrix projection, DirectX::SimpleMath::Matrix view, bool wireFrame) override;

private:

	std::unique_ptr<DirectX::Model> m_tiny;
};
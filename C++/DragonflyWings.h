#pragma once
// D3D Includes
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>
#include <Model.h>

// ACW Includes
#include "GameObject.h"
class DragonflyWings : GameObject
{

public:

	DragonflyWings(LPWSTR fileName, LPWSTR fileName2);
	DragonflyWings(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
	DragonflyWings(const DragonflyWings& other);
	~DragonflyWings(void);

	virtual void Initialize(GraphicsManager* gfx) override;
	virtual void Destroy(void) override;
	virtual Transform* GetTransform(void) override;

	void Update(TimeManager* time, Transform* transform);
	void Render(GraphicsManager* gfx, DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view, bool wireFrame);

private:

	LPWSTR m_fileName;
	std::unique_ptr<DirectX::Model> m_left;
	std::unique_ptr<DirectX::Model> m_right;
};
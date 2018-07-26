#pragma once
#include "GraphicsManager.h"
#include "TimeManager.h"
#include "Transform.h"

class GameObject
{

public:

	GameObject(void);
	GameObject(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 rotation,
		DirectX::SimpleMath::Vector3 scale);

	virtual ~GameObject(void);

	virtual void Initialize(GraphicsManager* gm);
	virtual void Destroy(void) = 0;
	virtual void Update(TimeManager* time);
	virtual void Render(GraphicsManager* gm, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view);

	virtual Transform* GetTransform(void);

protected:

	Transform* m_transform;
};
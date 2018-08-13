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
	GameObject(const GameObject& other);
	virtual ~GameObject(void);

	virtual void Initialize(GraphicsManager* gfx) = 0;
	virtual void Destroy(void) = 0;
	virtual void Reset(void);

	virtual Transform* GetTransform(void);

protected:

	Transform* m_transform;
};
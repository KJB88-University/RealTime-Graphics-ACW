#pragma once
#include "GraphicsManager.h"
#include "TimeManager.h"
#include "Transform.h"

class GameObject
{

public:

	GameObject(void);
	GameObject(
		DirectX::SimpleMath::Vector3& const position,
		DirectX::SimpleMath::Vector3& const rotation,
		DirectX::SimpleMath::Vector3& const scale);
	GameObject(const GameObject& other);
	virtual ~GameObject(void);

	virtual void Initialize(GraphicsManager* const gfx) = 0;
	virtual void Destroy(void) = 0;
	virtual void Reset(void);

	virtual Transform* GetTransform(void) const;

private:
	Transform* m_transform;
	GameObject& GameObject::operator=(const GameObject& other)=delete;
};
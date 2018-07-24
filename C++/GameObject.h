#pragma once
#include "GraphicsManager.h"
#include "TimeManager.h"
#include "Transform.h"
class GameObject
{

public:

	GameObject(void);
	virtual ~GameObject(void);

	virtual void Initialize(GraphicsManager* gm) = 0;
	virtual void Destroy(void) = 0;
	virtual void Update(TimeManager* time) = 0;
	virtual void Render(GraphicsManager* gm) = 0;

	virtual Transform* GetTransform(void);

protected:

	Transform* m_transform;
};
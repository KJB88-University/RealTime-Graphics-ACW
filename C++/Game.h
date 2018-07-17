#pragma once

// ACW Includes
#include "Tiny.h" // DEBUG
#include "GraphicsManager.h"
#include "Camera.h"

class Game
{

public:
	Game(void);
	~Game(void);

	void Initialize(GraphicsManager* gm);
	void Destroy(void);
	void Update(void);
	void Render(GraphicsManager* gm);

private:

	Tiny* m_tiny;
	Camera* m_mainCamera;
};
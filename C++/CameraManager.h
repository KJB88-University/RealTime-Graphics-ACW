#pragma once

// STL Includes
#include <vector>

// ACW Includes
#include "Camera.h"
#include "GraphicsManager.h"


class CameraManager
{
public:

	CameraManager(void);
	~CameraManager(void);

	void Initialize(GraphicsManager* gfx);
	void Destroy(void);
	void Update(void);
	void Render(void);

private:

	Camera* m_mainCamera;

	std::vector<Camera*> m_cameras;
	int m_currentCameraIndex;
};
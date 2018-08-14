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

	void Initialize(DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 lookAt, int vpWidth, int vpHeight, float nearClip, float farClip);
	void Destroy(void);
	void Update(InputManager* input);

	void NextCamera(void);
	void PrevCamera(void);
	Camera* JumpToCamera(int index);

	void AddCamera(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 lookAt, bool followCam = false, GameObject* followObject = nullptr);
	Camera* GetMainCamera(void);
	void Reset(void);

private:

	int m_vpHeight;
	int m_vpWidth;
	float m_nearClip;
	float m_farClip;

	std::vector<Camera*> m_cameras;
	int m_currentCameraIndex;
};
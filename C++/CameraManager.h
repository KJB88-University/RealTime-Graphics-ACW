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

	void Initialize(DirectX::SimpleMath::Vector3& const pos, DirectX::SimpleMath::Vector3& const lookAt, int const vpWidth, int const vpHeight, float const nearClip, float const farClip);
	void Destroy(void);
	//void Update(InputManager* input);

	void NextCamera(void);
	void PrevCamera(void);
	Camera* JumpToCamera(int const index);

	void AddCamera(DirectX::SimpleMath::Vector3& const position, DirectX::SimpleMath::Vector3& const rotation, DirectX::SimpleMath::Vector3& const lookAt, bool followCam = false, GameObject* followObject = nullptr);
	Camera* GetMainCamera(void) const;
	int GetCurrentCameraID(void) const;
	//void Reset(void);

private:

	int m_vpHeight;
	int m_vpWidth;
	float m_nearClip;
	float m_farClip;

	std::vector<Camera*> m_cameras;
	int m_currentCameraIndex;
};
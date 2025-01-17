// D3D Include
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "CameraManager.h"

using namespace DirectX::SimpleMath;
using namespace std;

CameraManager::CameraManager(void)
	: m_currentCameraIndex(0), m_vpWidth(0), m_vpHeight(0), m_nearClip(0), m_farClip(0)
{
	m_cameras = vector<Camera*>();
}

CameraManager::~CameraManager(void)
{

}

void CameraManager::Initialize(Vector3 pos, Vector3 lookAt, int vpWidth, int vpHeight, float nearClip, float farClip)
{
	// Update CM info about clipping plane and viewport
	m_vpWidth = vpWidth;
	m_vpHeight = vpHeight;
	m_nearClip = nearClip;
	m_farClip = farClip;

	// Set up initial camera
	Camera* newCam = new Camera(pos, Vector3(0.0f, 0.0f, 0.0f));
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	m_cameras.push_back(newCam);
}

void CameraManager::AddCamera(Vector3 position, Vector3 rotation, Vector3 lookAt, bool followCam, GameObject* followObject)
{
	Camera* newCam = new Camera(position, rotation);
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	if (followCam)
	{
		newCam->ToggleFollowCam(followObject);
	}
	m_cameras.push_back(newCam);
}

int CameraManager::GetCurrentCameraID(void)
{
	return m_currentCameraIndex;
}

void CameraManager::NextCamera(void)
{
	// Increment
	if (m_currentCameraIndex < m_cameras.size())
	{
		m_currentCameraIndex++;
	}
	// Wrap around
	else if (m_currentCameraIndex == (m_cameras.size() - 1))
	{
		m_currentCameraIndex = 0;
	}
}

void CameraManager::PrevCamera(void)
{
	// Decrement
	if (m_currentCameraIndex > 0)
	{
		m_currentCameraIndex--;
	}
	// Wrap around
	else if (m_currentCameraIndex == 0)
	{
		m_currentCameraIndex = (m_cameras.size() - 1);
	}
}

Camera* CameraManager::JumpToCamera(int index)
{
	if (index >= 0 && index < m_cameras.size())
	{
		m_currentCameraIndex = index;
		return GetMainCamera();
	}
}

void CameraManager::Destroy(void)
{
	// Cleanup
	for (int i = 0; i < m_cameras.size(); ++i)
	{
		m_cameras[i]->Destroy();
		m_cameras[i] = nullptr;
	}
}

Camera* CameraManager::GetMainCamera(void)
{
	return m_cameras[m_currentCameraIndex];
}

void CameraManager::Update(InputManager* input)
{

}

void CameraManager::Reset(void)
{
	for (int i = 0; i < m_cameras.size(); ++i)
	{
		m_cameras[i]->Reset();
	}

	m_currentCameraIndex = 0;
}
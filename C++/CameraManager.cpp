// D3D Include
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "CameraManager.h"

using namespace DirectX::SimpleMath;
using namespace std;

CameraManager::CameraManager(void)
	: m_vpHeight(0), m_vpWidth(0), m_nearClip(0), m_farClip(0), m_currentCameraIndex(0)
{
	m_cameras = vector<Camera*>();
}

CameraManager::~CameraManager(void)
{

}

void CameraManager::Initialize(Vector3& const pos, Vector3& const lookAt, int const vpWidth, int const vpHeight, float const nearClip, float const farClip)
{
	// Update CM info about clipping plane and viewport
	m_vpWidth = vpWidth;
	m_vpHeight = vpHeight;
	m_nearClip = nearClip;
	m_farClip = farClip;

	// Set up initial camera
	Camera* const newCam = new Camera(pos, Vector3(0.0f, 0.0f, 0.0f));
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	m_cameras.push_back(newCam);
}

void CameraManager::AddCamera(Vector3& const position, Vector3& const rotation, Vector3& const lookAt, bool followCam, GameObject* const followObject)
{
	Camera* const newCam = new Camera(position, rotation);
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	if (followCam)
	{
		newCam->ToggleFollowCam(followObject);
	}
	m_cameras.push_back(newCam);
}

int CameraManager::GetCurrentCameraID(void) const
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

Camera* CameraManager::JumpToCamera(int const index)
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
		delete m_cameras[i];
		m_cameras[i] = nullptr;
	}
}

Camera* CameraManager::GetMainCamera(void) const
{
	return m_cameras[m_currentCameraIndex];
}

//void CameraManager::Reset(void)
//{
//	for (int i = 0; i < m_cameras.size(); ++i)
//	{
//		m_cameras[i]->Reset();
//	}
//
//	m_currentCameraIndex = 0;
//}
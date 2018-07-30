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

void CameraManager::Initialize(Vector3 lookAt, int vpWidth, int vpHeight, float nearClip, float farClip)
{
	// Update CM info about clipping plane and viewport
	m_vpWidth = vpWidth;
	m_vpHeight = vpHeight;
	m_nearClip = nearClip;
	m_farClip = farClip;

	// Set up initial camera
	Camera* newCam = new Camera();
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	m_cameras.push_back(newCam);

	newCam = new Camera(Vector3(10.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	m_cameras.push_back(newCam);
}

void CameraManager::AddCamera(Vector3 position, Vector3 rotation, Vector3 lookAt)
{
	Camera* newCam = new Camera(position, rotation);
	newCam->Initialize(lookAt, m_vpWidth, m_vpHeight, m_nearClip, m_farClip);
	m_cameras.push_back(newCam);
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

void CameraManager::JumpToCamera(int index)
{
	if (index >= 0 && index < m_cameras.size())
	{
		m_currentCameraIndex = index;
	}
}

void CameraManager::Destroy(void)
{
	// Cleanup
}

Camera* CameraManager::GetMainCamera(void)
{
	return m_cameras[m_currentCameraIndex];
}

void CameraManager::Update(InputManager* input)
{

}
// D3D Include
#include <d3d11.h>

// DXTK Includes
#include <SimpleMath.h>

// ACW Includes
#include "CameraManager.h"

using namespace DirectX::SimpleMath;

CameraManager::CameraManager(void)
{

}

CameraManager::~CameraManager(void)
{

}

void CameraManager::Initialize(GraphicsManager* gfx)
{
	// Setup cameras and add to vector
	Camera* newCam = new Camera();
}

void CameraManager::Destroy(void)
{
	// Cleanup
}

void CameraManager::Update(void)
{
	// Update camera positions
}

void CameraManager::Render(void)
{
	// Render the view
}
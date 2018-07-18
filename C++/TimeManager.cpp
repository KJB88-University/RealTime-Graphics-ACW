// D3D Include
#include <d3d11.h>

// DXTK Include
#include <SimpleMath.h>

// ACW Include
#include "TimeManager.h"
#include "BasicLogger.h"

TimeManager::TimeManager(void)
{

}

TimeManager::~TimeManager(void)
{

}

void TimeManager::Initialize(void)
{

}

void TimeManager::Destroy(void)
{

}

void TimeManager::Update(void)
{
	static uint64_t dwTimeStart = 0;
	static uint64_t dwTimeLast = 0;
	uint64_t dwTimeCur = GetTickCount64();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	float t = (dwTimeCur - dwTimeStart) / 1000.0f;
	float dt = (dwTimeCur - dwTimeLast) / 1000.0f;
	dwTimeLast = dwTimeCur;
}

float TimeManager::GetDeltaTime(void)
{
	return m_deltaTime;
}

float TimeManager::GetTotalElapsedTime(void)
{
	return m_elapsedTime;
}
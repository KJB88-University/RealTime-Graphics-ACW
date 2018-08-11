// D3D Include
#include <d3d11.h>

// DXTK Include
#include <SimpleMath.h>

// ACW Include
#include "TimeManager.h"
#include "BasicLogger.h"

using namespace DirectX;

TimeManager::TimeManager(void)
{

}

TimeManager::~TimeManager(void)
{

}

void TimeManager::Initialize(void)
{
	m_timer = StepTimer();
}

void TimeManager::Destroy(void)
{

}

void TimeManager::Update(void)
{
	// Update StepTimer
	m_timer.Tick([&]()
	{
		m_deltaTime = StepTimer::TicksToSeconds(m_timer.GetElapsedTicks());
		m_elapsedTime = m_timer.GetElapsedSeconds();
	});


	//uint64_t dwTimeStart = 0;
	//uint64_t dwTimeLast = 0;
	//uint64_t dwTimeCur = GetTickCount64();
	//if (dwTimeStart == 0)
	//	dwTimeStart = dwTimeCur;
	//float t = (dwTimeCur - dwTimeStart) / 1000.0f;
	//float dt = (dwTimeCur - dwTimeLast) / 1000.0f;
	//dwTimeLast = dwTimeCur;
}

float TimeManager::GetDeltaTime(void)
{
	return m_deltaTime;
}

//float TimeManager::GetFramesPerSecond(void)
//{
//	return m_timer.GetFramesPerSecond();
//}
//
float TimeManager::GetTotalElapsedTime(void)
{
	return m_timer.GetTotalSeconds();
}

/*
float TimeManager::GetTotalElapsedTime(void)
{
	return m_elapsedTime;
}
*/
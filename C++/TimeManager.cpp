// D3D Include
#include <d3d11.h>

// DXTK Include
#include <SimpleMath.h>

// ACW Include
#include "TimeManager.h"
#include "BasicLogger.h"

using namespace DirectX;

TimeManager::TimeManager(void)
	: m_currentModifier(2)
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
		m_elapsedTime = m_timer.GetTotalSeconds();
		m_fps = m_timer.GetFramesPerSecond();
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

void TimeManager::IncreaseModifier(void)
{
	if (m_currentModifier < (m_modifierValues.size() - 1))
	{
		m_currentModifier++;
	}
}

void TimeManager::DecreaseModifier(void)
{
	if (m_currentModifier > 0.0f)
	{
		m_currentModifier--;
	}
}

float TimeManager::GetCurrentModifier(void)
{
	return m_modifierValues[m_currentModifier];
}

float TimeManager::GetDeltaTime(void)
{
 	return m_deltaTime * m_modifierValues[m_currentModifier];
}

uint32_t TimeManager::GetFramesPerSecond(void)
{
	return m_fps;
}

float TimeManager::GetTotalElapsedTime(void)
{
	return m_elapsedTime * m_modifierValues[m_currentModifier];
}

void TimeManager::Reset(void)
{
	m_currentModifier = 2;
}
#pragma once
#include "StepTimer.h"
#include <vector>

class TimeManager
{

public:

	TimeManager(void);
	~TimeManager(void);

	void Initialize(void);
	void Destroy(void);
	void Update(void);

	// Returns the time since the last frame update
	float GetDeltaTime(void);

	// Returns the total running time in seconds
	float GetTotalElapsedTime(void);

	void IncreaseModifier(void);
	void DecreaseModifier(void);

	//// Returns the frames per second
	//float GetFramesPerSecond(void);

private:

	DirectX::StepTimer m_timer;

	const std::vector<float> m_modifierValues
	{
		0.01f,
		0.1f,
		1.0f,
		2.0f,
		5.0f
	};
	float m_currentModifier = 2;

	// Time since last frame
	float m_deltaTime;

	// Total time Game has been running
	float m_elapsedTime;

};
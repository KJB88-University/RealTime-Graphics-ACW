#pragma once
#include "StepTimer.h"

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

	// Returns the frames per second
	float GetFramesPerSecond(void);
private:

	DirectX::StepTimer m_timer;

	// Time since last frame
	//float m_deltaTime;

	// Total time Game has been running
	//float m_elapsedTime;

};
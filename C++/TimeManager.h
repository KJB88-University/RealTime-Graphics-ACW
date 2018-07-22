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

	float GetDeltaTime(void);
	float GetTotalElapsedTime(void);

private:

	// Time since last frame
	float m_deltaTime;

	// Time program was started
	float m_startTime;

	// Total time Game has been running
	float m_elapsedTime;

};
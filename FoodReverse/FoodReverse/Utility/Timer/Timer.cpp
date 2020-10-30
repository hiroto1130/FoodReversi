#include "Timer.h"

int Timer::GetSecondsElapsedTime()
{
	std::chrono::system_clock::time_point now;
	now = std::chrono::system_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
	static_cast<int>(elapsed);
	return elapsed;
}

void Timer::TimerReset()
{
	start = std::chrono::system_clock::now();
	old_time = 0;
}

int Timer::GetMillisecondsElapsedTime()
{
	std::chrono::system_clock::time_point now;
	now = std::chrono::system_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
	static_cast<int>(elapsed);
	return elapsed;
}

void Timer::TimerStart()
{
	start = std::chrono::system_clock::now();
}

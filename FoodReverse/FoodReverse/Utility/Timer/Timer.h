#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:

	Timer() { TimerStart(); }

	int GetMillisecondsElapsedTime();
	int GetSecondsElapsedTime();
	void TimerReset();
	int old_time = 0;

private:

	void TimerStart();
	std::chrono::system_clock::time_point start;

};

#endif

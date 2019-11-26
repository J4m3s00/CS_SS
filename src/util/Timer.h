#pragma once

class Timer
{
public:
	Timer();
	float Reset();
	float GetDuration();
private:
	std::chrono::steady_clock::time_point last;
};
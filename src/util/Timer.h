#pragma once

class Timer
{
public:
	Timer();
	float Reset();
private:
	std::chrono::steady_clock::time_point last;
};
#pragma once

#include <chrono>
class Timer
{
public:
	Timer()
	{
		mLast = std::chrono::steady_clock::now();
	}
	float Mark()
	{
		mOld = mLast;
		mLast = std::chrono::steady_clock::now();

		return std::chrono::duration<float>(mLast - mOld).count();
	}
	float Peek()
	{
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - mLast).count();
	}

private:
	std::chrono::steady_clock::time_point mLast;
	std::chrono::steady_clock::time_point mOld;
};

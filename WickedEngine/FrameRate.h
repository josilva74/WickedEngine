#pragma once
#include "WickedEngine.h"
#include "Timer.h"

class Timer;

static class FrameRate
{
protected:
	static Timer timer;
	static double dt;
public:
	static void Initialize();

	static void Frame();

	static double FPS();
};

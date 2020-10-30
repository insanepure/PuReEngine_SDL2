#pragma once
#ifdef __linux__
//LINUX
#include <SDL2/SDL.h>
#elif _WIN32
//Windows
#include <SDL.h>
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif

namespace PuRe
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void Update();
		int updates;
		float timeMultiplicator;
	private:
		unsigned int timeStepMs;
		unsigned int timeLastMs;
		unsigned int timeCurrentMs;
		unsigned int timeDeltaMs;
		unsigned int timeAccumulatedMs;
	};
}
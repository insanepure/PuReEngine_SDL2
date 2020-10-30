#pragma once

#include "EngineDescription.h"
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"
#include "Scene.h"
#include <time.h>

namespace PuRe
{
	class Engine
	{
	public:
		Engine(EngineDescription& description);
		void Run(Scene* scene);
	private:
		bool quit;
		Window* window;
		Graphics* graphics;
		Timer* timer;
		EngineDescription* description;
	};
}

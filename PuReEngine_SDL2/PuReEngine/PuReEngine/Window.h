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
#include "WindowDescription.h"
#include <iostream>
namespace PuRe
{
	class Window
	{
	public:
		Window(WindowDescription& description);
		~Window();
		SDL_Window* getWindow();
		bool checkQuit();
		SDL_Event* getEvent();
		void SwapWindow();
		bool checkResize();
		unsigned short width,height;

	private:
		SDL_Window* sdlWindow;
		SDL_GLContext glcontext;
		SDL_Event sdlEvent;

	};
}
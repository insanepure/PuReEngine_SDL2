#pragma once
#define GLM_FORCE_RADIANS

#ifdef __linux__
//LINUX
#include <GL/glew.h>
#include <SDL2/SDL.h>
#elif _WIN32
//Windows
#define _CRT_SECURE_NO_DEPRECATE //Nervt sonst mit Warnings
#include <glew.h>
#include <SDL.h>
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif


namespace PuRe
{
	class Graphics
	{
	private:
		SDL_Window* sdlWindow;
		bool isfullscreen;
		unsigned short windowWidth;
		unsigned short windowHeight;
		float ViewPortWidth;
		float ViewPortHeight;
	public:
		Graphics(SDL_Window* sdlWindow,unsigned short width,unsigned short height);
		~Graphics();
		void ResizeViewport(unsigned short width,unsigned short height);
		void toogleFS();
		void Clear();
		unsigned short getWindowWidth();
		unsigned short getWindowHeight();
		float getViewPortWidth();
		float getViewPortHeight();

	};
}
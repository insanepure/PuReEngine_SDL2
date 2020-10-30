
#pragma once
#define GLM_FORCE_RADIANS

#ifdef __linux__
//LINUX
#include <GL/glew.h>
#elif _WIN32
//Windows
#define _CRT_SECURE_NO_DEPRECATE //Nervt sonst mit Warnings
#include <glew.h>
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif
#include <fstream>
#include "Defines.h"
#include "Texture.h"
namespace PuRe
{
	class FrameBuffer
	{
	private:
		GLuint gFBO;
		PuRe_Texture* Texture;
	public:
		FrameBuffer(PuRe_Texture* Texture);
		void Bind();
		void UnBind();
		~FrameBuffer();

	};
}
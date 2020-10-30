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
const uint32 FOURCC_DXT1 = 0x31545844; //(MAKEFOURCC('D','X','T','1'))
const uint32 FOURCC_DXT3 = 0x33545844; //(MAKEFOURCC('D','X','T','3'))
const uint32 FOURCC_DXT5 = 0x35545844; //(MAKEFOURCC('D','X','T','5'))
namespace PuRe
{
	class Texture
	{
	private:
		GLuint TextureID;
		uint16 Height;
		uint16 Width;
	public:
		Texture();
		GLuint GetID();
		void Empty(float Width,float Height);
		void LoadDDS(const char* path);
		void Bind();
		void UnBind();
		uint16 GetHeight();
		uint16 GetWidth();
		~Texture();

	};
}
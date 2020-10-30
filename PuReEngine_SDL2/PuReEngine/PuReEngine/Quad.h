#pragma once
#define GLM_FORCE_RADIANS
#ifdef __linux__
//LINUX
#include <GL/glew.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#elif _WIN32
//Windows
#define _CRT_SECURE_NO_DEPRECATE //Nervt sonst mit Warnings
#include <glew.h>
#include <../../glm/glm.hpp>
#include <../../glm/gtc/type_ptr.hpp>
#include <../../glm/gtc/matrix_transform.hpp>
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif
#include "Rect.h"
#include "Material.h"
#include "Defines.h"
namespace PuRe
{
	class Quad
	{
	private:
		GLuint gVBO;
		GLuint gIBO;
		GLuint gUVBO;
	public:
		Quad();
		void Draw(Rect DRect,bool flip,float32 Width,float32 Height,PuRe_Material* Mat);
		~Quad();

	};
}
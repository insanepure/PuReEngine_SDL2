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
#include "Defines.h"
#include "Quad.h"
#include "Texture.h"
#include "Vector3.h"
#include "Rect.h"
#include "Material.h"
namespace PuRe
{
	class Sprite
	{
	private:
		PuRe_Quad* Quad;
		PuRe_Texture* Texture;
	public:
		Sprite(PuRe_Quad* Quad,PuRe_Texture* Texture);
		~Sprite();
		void Draw(PuRe_Vector3 Position,PuRe_Vector3 Scale,PuRe_Vector3 Origin,float32 Angle,PuRe_Vector3 Color,Rect DRect,bool flip,PuRe_Material* Material);

	};
}
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

#include <iostream>
#include <fstream>
#include <string>

#include "Defines.h"
#include "Vector2.h"
#include "Matrix.h"
namespace PuRe
{
	class Material
	{
	private:
		glm::mat4 Model;
        glm::mat4 View;
        glm::mat4 Projection;
		glm::vec4 Color;
		float32 Time;
		PuRe_Vector2 Resolution;

		//Shader Variables
		GLint VertexUV;
		GLint VertexPosition;
		GLint ResolutionID;
		GLint TimeID;
		GLint TextureID;
		GLint ColorID;
		GLuint ProjectionID;
		GLuint ViewID;
		GLuint ModelID;

		//Shader
		GLuint programID;
		GLuint vertexID;
		GLuint fragmentID;
		
		GLuint loadShader(const char* path,GLenum shaderType);

		void ShaderLog(GLuint shader);
		void ProgramLog(GLuint program);
	public:
		Material(  const char* vertex_path,const char* fragment_path );

        void setModel(glm::mat4 Model);
        void setView(glm::mat4 View);
        void setProjection(glm::mat4 Projection);
		void setTime(float32 Time);
		void setColor(glm::vec4 Color);
		void setResolution(PuRe_Vector2 Resolution);

		void Update();
		void BindUV();
		void BindPosition();
		void Bind();
		void UnBind();
		~Material();

	};
}
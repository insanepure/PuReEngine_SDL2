#include "Graphics.h"

namespace PuRe
{

	Graphics::Graphics(SDL_Window* sdlWindow,unsigned short width,unsigned short height)
	{
		this->sdlWindow = sdlWindow;
		//Initialisiere OpenGL
		glewInit();
		//Setze die Clearfarbe
		glClearColor (0.0f, 0.4f, 1.0f, 1.0f);
		//Lade die Shader
		glEnable( GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glLoadIdentity();  // Reset the modelview matrix 
		this->ResizeViewport(width,height);
	}

	Graphics::~Graphics()
	{
		//Lösche Alles
	}

	void Graphics::Clear()
	{

		//Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	unsigned short Graphics::getWindowWidth()
	{
		return this->windowWidth;
	}
	unsigned short Graphics::getWindowHeight()
	{
		return this->windowHeight;
	}
	float Graphics::getViewPortWidth()
	{
		return this->ViewPortWidth;
	}
	float Graphics::getViewPortHeight()
	{
		return this->ViewPortHeight;
	}
	void Graphics::ResizeViewport(unsigned short width,unsigned short height)
	{
		glViewport( 0, 0, ( GLint )width, ( GLint )height );

		this->ViewPortWidth = width;
		this->ViewPortHeight = height;
		this->windowWidth = width;
		this->windowHeight = height;
		//in Cam class implementieren


	}
	void Graphics::toogleFS()
	{
		//Falls er Fullscreen ist
		if(this->isfullscreen)
		{
			//Setze Fullscreen
			SDL_SetWindowFullscreen(this->sdlWindow,0);
			this->isfullscreen = false;
		}
		else //Falls er nicht im Fullscreen ist
		{
			//Gehe in den Fullscreen
			SDL_SetWindowFullscreen(this->sdlWindow,SDL_WINDOW_FULLSCREEN_DESKTOP);
			this->isfullscreen = true;
		}
	}

}

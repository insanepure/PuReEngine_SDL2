#include "Window.h"

namespace PuRe
{
	Window::Window(WindowDescription& description)
	{
		//Erzeuge SDL
		if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_VIDEO | SDL_INIT_AUDIO ))
			printf( "SDL konnte nicht initialisiert werden! SDL_Error: %s\n", SDL_GetError() );
		//Shader Attribute
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		//Erstelle das Fenster
		this->sdlWindow = SDL_CreateWindow(description.Title,description.X,description.Y,description.Width,description.Height,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);     
		if( sdlWindow == NULL )
			printf( "Fenster konnte nicht erzeugt werden! SDL_Error: %s\n", SDL_GetError() );
		//Erzeugt OpenGL Context
		this->glcontext = SDL_GL_CreateContext(sdlWindow);
		if( !this->glcontext )
			printf( "OpenGL konnte nicht erzeugt werden! SDL_Error: %s\n", SDL_GetError() );
		//Definiere Höhe und Breite
		this->width = description.Width;
		this->height = description.Height;
		//Lade Icon
		SDL_Surface *image = SDL_LoadBMP(description.IconPath);
		if( !image )
			printf( "Icon konnte nicht geladen werden! SDL_Error: %s\n", SDL_GetError() );
		else
			SDL_SetWindowIcon(this->sdlWindow, image); 
		SDL_FreeSurface(image);

	}

	Window::~Window()
	{
		//Free das Fenster (Da C kein delete)
		SDL_GL_DeleteContext(this->glcontext);  
		SDL_DestroyWindow(this->sdlWindow);
		SDL_Quit();
	}
	bool Window::checkResize()
	{
		int width = 0;
		int height = 0;
		SDL_GetWindowSize(this->sdlWindow,&width,&height);
		if(this->width != width||this->height != height)
		{
			this->width = width;
			this->height = height;
			return true;
		}
		return false;
	}

	bool Window::checkQuit()
	{
		while(SDL_PollEvent(&this->sdlEvent))
        {
            if(this->sdlEvent.type == SDL_QUIT)
            {
				return true;
            }
        }
		return false;
	}

	SDL_Event* Window::getEvent()
	{
		return &sdlEvent;
	}
	void Window::SwapWindow()
	{
		SDL_GL_SetSwapInterval( 1 );
		SDL_GL_SwapWindow( this->sdlWindow );
	}
	SDL_Window* Window::getWindow()
	{
		return sdlWindow;
	}
}
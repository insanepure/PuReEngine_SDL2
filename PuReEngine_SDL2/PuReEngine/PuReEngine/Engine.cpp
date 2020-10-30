#include "Engine.h"

namespace PuRe
{
	Engine::Engine(EngineDescription& description)
	{
		this->quit = false;
		this->description = &description;
		this->window = new Window(this->description->Window);
		this->timer = new Timer();
		this->graphics = new Graphics(this->window->getWindow(),description.Window.Width,description.Window.Height);
	}
	void Engine::Run(Scene* scene)
	{
		srand((int)time(NULL));
		scene->Initialize(this->graphics);
		while(!this->quit)
		{
			this->quit = window->checkQuit();
			this->timer->Update();
			if(this->window->checkResize())
				this->graphics->ResizeViewport(this->window->width,this->window->height);
			if(!scene->Update(this->timer->timeMultiplicator,this->graphics))
				quit = true;
			this->graphics->Clear();
			scene->Render(this->graphics);
			this->window->SwapWindow();
		}
		scene->Exit();
		delete this->graphics;
		delete this->window;
	}
}

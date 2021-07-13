#include "Corepch.h"
#include "Application.h"
#include "Graphics/Window/GLWindow.h"
namespace Application
{
	App* App::INSTANCE = nullptr;
	App::App()
	{}
	App::~App ()
	{}
	bool App::init ()
	{
		config.logger = IO::logger::getInstance ();
		config.dispatcher = std::make_shared<EventDispatcher> ();
		std::shared_ptr<Graphics::GLWindow> window = std::make_shared<Graphics::GLWindow> 
			(Graphics::GLWindow("GalSim 2020", config.dispatcher, 1920, 1080));
		if ( !window->init () )
			return false;
		config.window = std::shared_ptr<Graphics::IWindow> (window);
		config.viewport = std::shared_ptr<Graphics::IOpenglContext> (window);
		config.running = true;
		return true;
	}
	void App::run ()
	{
		while ( config.running )
		{
			update ();
			render ();
		}
	}
	void App::update ()
	{
		config.window->pollEvents ();
	}
	void App::render ()
	{
		
	}
}
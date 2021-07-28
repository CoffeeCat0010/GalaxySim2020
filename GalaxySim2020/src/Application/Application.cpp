#include "Corepch.h"
#include "Application.h"
#include "Graphics/GraphicsLayer.h"
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
		config.running = true;
		config.dispatcher->subscribe(onCloseEvent, EventDispatcher::Priority::CRITICAL);
		G_Layer = std::make_unique<Graphics::GraphicsLayer>(config.dispatcher);
		G_Layer->onAttach();
		return true;
	}
	bool App::cleanUp ()
	{
		G_Layer->onDetatch();
		return true;
	}
	
}
#pragma once
#include "Corepch.h"
#include "Graphics/Window/Window.h"
#include "Graphics/Window/OpenglContext.h"
#include "Event/BaseClasses/EventDispatcher.h"
namespace Application
{
	struct Configuration
	{
		bool running;
		int32_t fps_max = 60;
		IO::logger* logger;
		std::shared_ptr<Graphics::IWindow> window;
		std::shared_ptr<Graphics::IOpenglContext> viewport;
		std::shared_ptr<EventDispatcher> dispatcher;

		//Todo: add Opencl context
		// screen dimensions
		// open dir
		// file name

	};
	class App
	{
	private:
		Configuration config;
	public:
		static App* INSTANCE;
	public:
		~App ();
		App* getInstance ()
		{
			if ( INSTANCE == nullptr ) INSTANCE = new App ();
			return INSTANCE;
		}
		bool init ();
		void run ();
	private:
		App ();
		void update ();
		void render ();
	};
}


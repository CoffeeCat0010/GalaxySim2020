#pragma once
#include "Corepch.h"
#include "Graphics/Window/Window.h"
#include "Graphics/GraphicsLayer.h"
#include "Graphics/Window/OpenglContext.h"
#include "Event/EventDispatcher.h"
namespace Application
{
	struct Configuration
	{
		std::atomic<bool> running;
		IO::logger* logger;
		std::shared_ptr<EventDispatcher> dispatcher;

		//Todo: add Opencl context
		// screen dimensions
		// open dir
		// file name

	};
	class App
	{
	private:
		typedef std::shared_ptr<std::function<void (Application::Event* e)>> sharedCallbackPtr;
		typedef std::function<void (Application::Event* e)> callback;
		Configuration config;
		std::unique_ptr<Graphics::GraphicsLayer> G_Layer;
	public:
		static App* INSTANCE;
	public:
		~App ();
		static App* getInstance ()
		{
			if ( INSTANCE == nullptr ) INSTANCE = new App ();
			return INSTANCE;
		}
		inline const Configuration& getConfig() {return config;}
		bool init ();
		bool cleanUp();
		inline bool isRunning() {return config.running;}
	private:
		App ();
		sharedCallbackPtr onCloseEvent = std::make_shared<callback> ([=](Event* e)
			{
				if ( e->getEventType () == EventType::close ){
					config.running = false;
					e->handle();
				}
			});
	};
}


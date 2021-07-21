#pragma once
#include "Corepch.h"
#include "Layers/Layer.h"
#include "Event/BaseClasses/EventHandlers.h"
#include "Event/BaseClasses/EventBroadcaster.h"
#include "Graphics/Window/Window.h"
#include "Graphics/Window/OpenglContext.h"

namespace Graphics{
	class GraphicsLayer: public Application::Layer, public Application::EventHandler,
		public std::enable_shared_from_this<GraphicsLayer>
	{
	private:
		std::shared_ptr<IWindow> m_window;
		std::shared_ptr<IOpenglContext> m_OGLcontext;
		std::shared_ptr<Application::EventBroadcaster> m_eventSystem;
		std::atomic<bool> isOpen = false;
		std::thread m_thread;
		

	public:
		GraphicsLayer (std::shared_ptr<Application::EventBroadcaster> evtSystem);
		GraphicsLayer (std::shared_ptr<Application::EventBroadcaster> evtSystem, std::shared_ptr<IWindow> window,
									 std::shared_ptr<IOpenglContext> OGLcontext);
		void onAttach() override;
		void onDetatch() override;
		void onEvent(Application::Event* e) override;
		void init() override;
	private:
		void run ();
	};
}


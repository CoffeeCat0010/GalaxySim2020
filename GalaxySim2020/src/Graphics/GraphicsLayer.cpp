#include "GraphicsLayer.h"
#include "Graphics/Window/GLWindow.h"
#include "Graphics/Renderers/BatchRenderer.h"
namespace Graphics{
	GraphicsLayer::GraphicsLayer (std::shared_ptr<Application::EventBroadcaster> evtSystem)
		:m_eventSystem(evtSystem)
	{}
	GraphicsLayer::GraphicsLayer (std::shared_ptr<Application::EventBroadcaster> evtSystem, std::shared_ptr<IWindow> window, std::shared_ptr<IOpenglContext> OGLcontext)
		:m_eventSystem(evtSystem), m_window(window), m_OGLcontext(OGLcontext)
	{}

	void GraphicsLayer::onAttach ()
	{
		m_eventSystem->subscribe (std::weak_ptr<GraphicsLayer> (shared_from_this()));
		isOpen = true;
		m_thread = std::thread (&GraphicsLayer::run, this);
	}
	
	void GraphicsLayer::onDetatch ()
	{
		isOpen = false;
		m_eventSystem->unsubscribe (std::weak_ptr<GraphicsLayer> (shared_from_this ()));
		m_thread.join ();
	}
	
	void GraphicsLayer::onEvent (Application::Event * e)
	{}
	
	void GraphicsLayer::init ()
	{
		if(m_window && m_OGLcontext)
		{ 
			m_window->init ();
			m_OGLcontext->init ();
		}
		else
		{
			GLWindow window("GalSim", 1920, 1080, false);
			std::shared_ptr<GLWindow> oglWindow = std::make_shared<GLWindow> (GLWindow ("GalSim", 1920, 1080, false));
			m_window = std::shared_ptr<IWindow> (oglWindow);
			m_OGLcontext = std::shared_ptr<IOpenglContext>(oglWindow);
			oglWindow->init ();


		}
	}
	void GraphicsLayer::run ()
	{
		while ( isOpen )
		{

			m_OGLcontext->paint ();
		}
	}
}

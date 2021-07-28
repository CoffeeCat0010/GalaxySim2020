#include "GraphicsLayer.h"
#include "Graphics/Window/GLWindow.h"
#include "Graphics/Renderers/BatchRenderer.h"
namespace Graphics{
	GraphicsLayer::GraphicsLayer (std::shared_ptr<Application::EventDispatcher> evtSystem)
		:m_eventSystem(evtSystem)
	{}
	GraphicsLayer::GraphicsLayer (std::shared_ptr<Application::EventDispatcher> evtSystem, std::shared_ptr<IWindow> window, std::shared_ptr<IOpenglContext> OGLcontext)
		:m_eventSystem(evtSystem), m_window(window), m_OGLcontext(OGLcontext)
	{}

	void GraphicsLayer::onAttach ()
	{
		m_eventSystem->subscribe (onEvent);
		isOpen = true;
		m_thread = std::thread (run);
	}
	
	void GraphicsLayer::onDetatch ()
	{
		isOpen = false;
		m_eventSystem->unsubscribe (onEvent);
		m_thread.join ();
	}
	
	bool GraphicsLayer::init ()
	{
		if(m_window && m_OGLcontext)
		{ 
			m_window->init ();
			m_OGLcontext->init ();
		}
		else
		{
			std::shared_ptr <GLWindow> window = std::make_shared<GLWindow >("GalSim",m_eventSystem, 1920, 1080, false);
			m_window = std::shared_ptr<IWindow> (window);
			m_OGLcontext = std::shared_ptr<IOpenglContext>(window);
			window->init ();
		}

		
		m_OGLcontext->makeOGLContextCurrent ();

		std::string source = IO::sourceToCStr ("src/Graphics/GLSL/myshader.frag");
		Graphics::Shader fragShader (source, Graphics::FRAG);

		source = IO::sourceToCStr ("src/Graphics/GLSL/myshader.vert");
		Graphics::Shader vertShader (source, Graphics::VERT);

		m_program = std::make_unique<Graphics::ShaderProgram>();
		m_program->addShader (&vertShader);
		m_program->addShader (&fragShader);
		m_program->prepareProgram ();



		m_renderer = std::make_unique<BatchRenderer>(*m_program);
		LOG_INFO (std::to_string (m_renderer->getMaxTextureUnits ()));
		return true;
		//TODO: add initialization check
	}

}

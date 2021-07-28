#pragma once
#include "Corepch.h"
#include "Layers/Layer.h"
#include "Graphics/Graphics.h"
#include "Event/BaseClasses/EventHandlers.h"
#include "Event/BaseClasses/EventBroadcaster.h"
#include "Graphics/Window/Window.h"
#include "Graphics/Window/OpenglContext.h"
#include "IO/Logger.h"
#include "IO/GL_Logger.h"
#include "IO/GSIO.h" 
#include "IO/DataFileType/StarFileMT.h"
#include "Generation/Galaxy.h"
#include "Math/MVec.h"

namespace Graphics{
	class GraphicsLayer: public Application::Layer,
		public std::enable_shared_from_this<GraphicsLayer>
	{

		#define NUM_OF_STARS 1024 //49152 // 1024
		//49152
		#define NUM_TIME_STEPS 5000 //5000
		//10000
	private:
		typedef std::shared_ptr<Application::Event> sharedEvtPtr;
		typedef std::shared_ptr<std::function<void (sharedEvtPtr e)>> sharedCallbackPtr;
		typedef std::function<void (sharedEvtPtr e)> callback;
		std::shared_ptr<IWindow> m_window;
		std::shared_ptr<IOpenglContext> m_OGLcontext;
		std::shared_ptr<Application::EventDispatcher> m_eventSystem;
		std::unique_ptr<BatchRenderer> m_renderer;
		std::unique_ptr<ShaderProgram> m_program;
		std::atomic<bool> isOpen = false;
		std::thread m_thread;
		

	public:
		GraphicsLayer (std::shared_ptr<Application::EventDispatcher> evtSystem);
		GraphicsLayer (std::shared_ptr<Application::EventDispatcher> evtSystem, std::shared_ptr<IWindow> window,
									 std::shared_ptr<IOpenglContext> OGLcontext);
		void onAttach() override;
		void onDetatch() override;
		bool init() override;
		sharedCallbackPtr onEvent = std::make_shared <callback> ([=](sharedEvtPtr e)
		{
			
		});
	//private:
		std::function<void ()> run = [=]()
		{
			init();
			m_OGLcontext->makeOGLContextCurrent();
			std::shared_ptr<IO::StarFileMT> rFile (
				(IO::StarFileMT::readFile ("./Simulations/testFile.STAR", IO::StarFileMT::fileVersion::LEGACY)));
			Application::Vec3f* test = new Application::Vec3f[NUM_OF_STARS];
			Graphics::Star* gStars = new Graphics::Star[NUM_OF_STARS];
			for ( int i = 0; i < NUM_OF_STARS; i++ )
			{
				gStars[i] = Graphics::Star (m_renderer->getShaderProgramID(), glm::vec3 (0, 0, 0), 30.f);
			};
			double lastTime = glfwGetTime ();
			double dt = 0;
			int gTimeStep = 0;
			/* Loop until the user closes the window */
			while ( !m_window->shouldClose() && gTimeStep < NUM_TIME_STEPS )
			{
				double now = glfwGetTime ();
				dt = now - lastTime;
				//std::cout << dt << std::endl;
					/* Render here */
				if ( dt >= 1.0f / 60.0f )
				{

					m_OGLcontext->makeOGLContextCurrent ();
					lastTime = now;
					glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					//rFile->readTimeStep((glm::vec3*)test, NUM_OF_STARS);

					std::vector<Application::Vec3f> vec (rFile->getTimeStep ());
					for ( int j = 0; j < NUM_OF_STARS; j++ )
					{
						gStars[j].setPos ((glm::vec3&)vec[j]);
						m_renderer->addMesh (gStars[j]);
					}
					m_renderer->render ();
					/* Swap front and back buffers */
					m_OGLcontext->paint();

					/* Poll for and process events */
					m_window->pollEvents ();
					dt = 0;
					gTimeStep++;
				}
			}
		};
	};
}


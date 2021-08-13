#include "OpenGlWidget.h"
namespace Graphics{
	CustomOpenGlWidget::CustomOpenGlWidget (std::string simPath, QWidget *parent)
		:isPaused(true), m_simPath(simPath), QOpenGLWidget (parent), IOpenglContext(1280, 720)
	{
		setupUi(this);
	}
	
	CustomOpenGlWidget::~CustomOpenGlWidget ()
	{
	}
	
	void CustomOpenGlWidget::initializeGL ()
	{
		GLenum glewError = glewInit ();
		if ( glewError != GLEW_OK )
		{
			LOG_FATAL ("GLEW failed to intialize!");
		}
		std::string source = IO::sourceToCStr ("src/Graphics/GLSL/pointShader.frag");
		Graphics::Shader fragShader (source, Graphics::FRAG);

		source = IO::sourceToCStr ("src/Graphics/GLSL/pointShader.vert");
		Graphics::Shader vertShader (source, Graphics::VERT);

		m_program = std::make_unique<Graphics::ShaderProgram> ();
		m_program->addShader (&vertShader);
		m_program->addShader (&fragShader);
		m_program->prepareProgram ();



		m_renderer = std::make_unique<BatchPointRenderer> (*m_program, size().width()/size().height());
		rFile = std::shared_ptr<IO::StarFileMT>(IO::StarFileMT::readFile (m_simPath));//, IO::StarFileMT::LEGACY));//,
																																				//IO::StarFileMT::fileVersion::LEGACY));
		timer.start();
	}
	void CustomOpenGlWidget::paintGL ()
	{
		if (gTimeStep < NUM_TIME_STEPS )
		{
				/* Render here */
//				std::cout << isPaused <<std::endl;
			if ( (timer.nsecsElapsed()/1E-9) >= 1.0f / 60.0f )
			{
				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				if(!isPaused || m_lastTimeStep.empty()){
					m_lastTimeStep = (rFile->getTimeStep ());
					for ( int j = 0; j < NUM_OF_STARS; j++ )
					{
						m_renderer->addPoint ((glm::vec3&)m_lastTimeStep[j]);
					}
				}
				else
				{
					for ( int j = 0; j < NUM_OF_STARS; j++ )
					{
						m_renderer->addPoint ((glm::vec3& )m_lastTimeStep[j]);
					}
				}
				m_renderer->render ();
				update();
				gTimeStep++;
				timer.restart();
			}
		}
	}
	void CustomOpenGlWidget::resizeGL (int w, int h)
	{
		m_renderer->setAspectratio((float)w/h);
	}
	bool CustomOpenGlWidget::init ()
	{
		return false;
	}
	void CustomOpenGlWidget::makeOGLContextCurrent ()
	{
		makeCurrent();
	}
	void CustomOpenGlWidget::paint ()
	{}

//	void CustomOpenGlWidget::paintGL ()
//	{
//		if ( gTimeStep < NUM_TIME_STEPS )
//		{
//			/* Render here */
////				std::cout << isPaused <<std::endl;
//			if ( (timer.nsecsElapsed () / 1E-9) >= 1.0f / 60.0f )
//			{
//				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//				//rFile->readTimeStep((glm::vec3*)test, NUM_OF_STARS);
//				if ( !isPaused || m_lastTimeStep.empty () )
//				{
//					m_lastTimeStep = (rFile->getTimeStep ());
//					for ( int j = 0; j < NUM_OF_STARS; j++ )
//					{
//						gStars[j].setPos ((glm::vec3&)m_lastTimeStep[j]);
//						m_renderer->addMesh (gStars[j]);
//					}
//				}
//				else
//				{
//					for ( int j = 0; j < NUM_OF_STARS; j++ )
//					{
//						m_renderer->addMesh (gStars[j]);
//					}
//				}
//				m_renderer->render ();
//				update ();
//				gTimeStep++;
//				timer.restart ();
//			}
//		}
//	}
}
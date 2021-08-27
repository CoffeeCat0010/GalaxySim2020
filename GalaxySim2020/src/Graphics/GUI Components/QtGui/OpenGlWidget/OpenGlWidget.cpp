#include "OpenGlWidget.h"
namespace QUI{
	CustomOpenGlWidget::CustomOpenGlWidget (std::string simPath, QWidget *parent)
		:isPaused(true), m_simPath(simPath), QOpenGLWidget (parent), IOpenglContext(1280, 720),
		m_numTimeSteps(0), m_numStars(0)
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



		m_renderer = std::make_unique<Graphics::BatchPointRenderer> (*m_program, size().width()/size().height());
		rFile = std::shared_ptr<IO::StarFileMT>(IO::StarFileMT::readFile (m_simPath));
																																				
		m_numStars = rFile->getNumStars();
		m_numTimeSteps = rFile->getNumTimeSteps();
		timer.start();
	}
	void CustomOpenGlWidget::paintGL ()
	{
		if (gTimeStep < m_numTimeSteps )
		{
				/* Render here */
			if ( (timer.nsecsElapsed()/1E-9) >= 1.0f / 60.0f )
			{
				glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				if(!isPaused || m_lastTimeStep.empty()){
				//tempary solution to slow producer problem
					do{
					m_lastTimeStep = (rFile->getTimeStep ());
					}while(m_lastTimeStep.empty());
					for ( int j = 0; j < m_numStars; j++ )
					{
						m_renderer->addPoint ((glm::vec3&)m_lastTimeStep[j]);
					}
					gTimeStep++;
				}
				else
				{
					for ( int j = 0; j < m_numStars; j++ )
					{
						m_renderer->addPoint ((glm::vec3& )m_lastTimeStep[j]);
					}
				}
				m_renderer->render ();
				update();
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

}
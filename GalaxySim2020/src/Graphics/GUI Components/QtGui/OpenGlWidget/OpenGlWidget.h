#pragma once
#include "Corepch.h"
#include <QOpenGLWidget>
#include <QElapsedTimer>
#include "ui_OpenGlWidget.h"
#include "Graphics/Renderers/BatchPointRenderer.h"
#include "Graphics/Shaders/ShaderProgram.h"
#include "Graphics/Shaders/Shader.h"
#include "Event/EventDispatcher.h"
#include "IO/DataFileType/StarFileMT.h"
#include "IO/GSIO.h"
#include "Utility/Math/MVec.h"
#include "Graphics/Shapes/Star.h"
#include "Graphics/Window/OpenglContext.h"


namespace QUI{
	class CustomOpenGlWidget : public QOpenGLWidget, public Ui::OpenGlWidget, public Graphics::IOpenglContext
	{
		#define NUM_OF_STARS 49152//8192 // 1024
		//49152
		#define NUM_TIME_STEPS 10000//2500 //5000
		//10000
		Q_OBJECT
	private:
		typedef std::shared_ptr<Application::Event> sharedEvtPtr;
		typedef std::shared_ptr<std::function<void (sharedEvtPtr e)>> sharedCallbackPtr;
		typedef std::function<void (sharedEvtPtr e)> callback;

		std::unique_ptr<Graphics::BatchPointRenderer> m_renderer;
		std::unique_ptr<Graphics::ShaderProgram> m_program;
		std::shared_ptr<Application::EventDispatcher> m_eventSystem;
		std::shared_ptr<IO::StarFileMT> rFile;
		
		std::string m_simPath;
		QElapsedTimer timer;
		std::vector<Util::Vec3f> m_lastTimeStep;
		
		int gTimeStep = 0;
		uint64_t m_numTimeSteps;
		uint64_t m_numStars;
		bool isPaused;
	public:
		CustomOpenGlWidget (std::string simPath, QWidget *parent = Q_NULLPTR);
		~CustomOpenGlWidget ();
		inline void pause() {isPaused = true;}
		inline void play () { isPaused = false; }

	protected:
		virtual void initializeGL () override;
		virtual void paintGL () override;
		virtual void resizeGL(int w, int h) override;

		// Inherited via IOpenglContext
		virtual bool init () override;
		virtual void makeOGLContextCurrent () override;
		virtual void paint () override;
	};
}

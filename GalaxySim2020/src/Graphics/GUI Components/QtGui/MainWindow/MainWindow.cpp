#include "MainWindow.h"
#include <QSizePolicy>
#include "Event/ApplicationEvents.h"
namespace Graphics{
	MainWindow::MainWindow(std::weak_ptr<Application::EventDispatcher> dispatcher, QWidget* parent)
		: m_dispatcher(dispatcher), QMainWindow(parent), IWindow(1280, 720),
		IOpenglContext(1280, 720)
	{
		setupUi(this);
	}

	MainWindow::~MainWindow()
	{
	}

	void MainWindow::pollEvents ()
	{}

	void MainWindow::close ()
	{}
	bool MainWindow::init ()
	{
		GLenum glewError = glewInit ();
		if ( glewError != GLEW_OK )
		{
			LOG_FATAL ("GLEW failed to intialize!");
			
			return false;
		}
		return true;

	}

	void MainWindow::paint ()
	{
		//OGL_Viewport->update();
	}
	void MainWindow::closeEvent (QCloseEvent *event)
	{
		// event must be accepted first otherwise there might be a circular event loop
		event->accept();
		if(!m_dispatcher.expired())
			m_dispatcher.lock()->dispatch(std::make_shared<Application::AppCloseEvent>());
	}
	
	void MainWindow::onPlaySimulationTriggered ()
	{
		if (m_ogl_widget != nullptr){
			m_ogl_widget->play();
			QCoreApplication::sendEvent(m_ogl_widget, new QPaintEvent(m_ogl_widget->rect()));
		}
	}
	void MainWindow::onPauseSimulationTriggered ()	
	{
		if ( m_ogl_widget != nullptr )
		{
			m_ogl_widget->pause ();
			QCoreApplication::sendEvent (m_ogl_widget, new QPaintEvent (m_ogl_widget->rect ()));
		}
	}
	
	void MainWindow::onLoadSimulationTriggered ()
	{
		std::string pathToSim = QFileDialog::getOpenFileName (this, "Open Simulation", "C:/Users/justi/Simulations").toStdString ();
		m_ogl_widget = new CustomOpenGlWidget(pathToSim, splitter->widget(1));
		QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(splitter->widget(1)->layout());
		splitter->setSizes({240, 1040});
		layout->addWidget(m_ogl_widget);
		m_ogl_widget->show();
	}


}
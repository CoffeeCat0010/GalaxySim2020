#include "MainWindow.h"
#include <QSizePolicy>
#include "Event/ApplicationEvents.h"
namespace Graphics
{
	MainWindow::MainWindow (std::weak_ptr<Application::EventDispatcher> dispatcher, QWidget* parent)
		: m_dispatcher (dispatcher), m_platforms (Compute::Platform::getPlatforms ()), m_currPlatformIndex (0), m_currDeviceIndex (), QMainWindow (parent), IWindow (1280, 720),
		IOpenglContext (1280, 720)
	{
		setupUi (this);
		for ( int i = 0; i < m_platforms.size (); ++i )
			Platform_select->addItem (m_platforms[i].getPlatformName ().c_str ());
		m_selectedDeviceType = strToDeviceMap.find (Device_Type_Select->currentText ())->second;

	}

	MainWindow::~MainWindow ()
	{}

	void MainWindow::pollEvents ()
	{}

	void MainWindow::close ()
	{}
	bool MainWindow::init ()
	{
		return false;
	}

	void MainWindow::paint ()
	{
		//OGL_Viewport->update();
	}
	void MainWindow::closeEvent (QCloseEvent* event)
	{
		// event must be accepted first otherwise there might be a circular event loop
		event->accept ();
		if ( !m_dispatcher.expired () )
			m_dispatcher.lock ()->dispatch (std::make_shared<Application::AppCloseEvent> ());
	}
	void MainWindow::updateContext ()
	{
		Device_Select->clear ();
		m_clContext = std::make_shared<Compute::Context> (m_platforms[m_currPlatformIndex], strToDeviceMap.find (Device_Type_Select->currentText ())->second);

		m_availableDevices = m_clContext->getDevices ();
		if ( m_availableDevices.size () > 0 )
		{
			for ( int i = 0; i < m_availableDevices.size (); ++i )
				Device_Select->addItem (m_availableDevices[i]->getDeviceName ().c_str ());
			Device_Select->setCurrentIndex (0);
			onDeviceSelected (0);
		}
		emit contextUpdated(m_clContext);
	}

	void MainWindow::onPlaySimulationTriggered ()
	{
		if ( m_ogl_widget != nullptr )
		{
			m_ogl_widget->play ();
			QCoreApplication::sendEvent (m_ogl_widget, new QPaintEvent (m_ogl_widget->rect ()));
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
		std::string pathToSim = QFileDialog::getOpenFileName (this, "Open Simulation", "./Simulations").toStdString ();
		m_ogl_widget = new CustomOpenGlWidget (pathToSim, splitter->widget (1));
		QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(splitter->widget (1)->layout ());
		splitter->setSizes ({ 240, 1040 });
		layout->addWidget (m_ogl_widget);
		m_ogl_widget->show ();
	}
	void MainWindow::onPlatformSelected (int index)
	{
		m_currPlatformIndex = index;
		updateContext ();
	}

	void MainWindow::onDeviceTypeSelected (QString type)
	{
		updateContext ();
	}

	void MainWindow::onDeviceSelected (int index)
	{
		Device_Properties->clear ();
		if ( index != -1 )
		{
			std::shared_ptr<Compute::Device> selected = m_availableDevices[index];
			std::string str = "Device: " + selected->getDeviceName () + " \nVendor: " + selected->getDeviceVendor () +
				"\nDevice Version: " + selected->getDeviceVersion () + "\nCompute Units: " +
				std::to_string (selected->getNumComputeUnits ()) + "\nMax Work Dimension: " +
				std::to_string (selected->getWorkItemDiminsion ()) + "\nMax Work Item Sizes: ";
			for ( int i = 0; i < selected->getWorkItemSizes ().size (); ++i )
				str += std::to_string (selected->getWorkItemSizes ()[i]) + " ";

			Device_Properties->append (str.c_str ());
			emit deviceUpdated(selected);
		}
	}
	void MainWindow::onCreateSimulationTriggered ()
	{
		p_simWidget = QPointer<SimulationWidget>(new SimulationWidget(m_clContext, m_availableDevices[m_currDeviceIndex], this));
		connect (this, &MainWindow::contextUpdated, p_simWidget, &SimulationWidget::onContextUpdated);
		connect (this, &MainWindow::deviceUpdated, p_simWidget, &SimulationWidget::onDeviceUpdated);
		Config_Tabs->addTab(p_simWidget, "Simulation");
	}
}
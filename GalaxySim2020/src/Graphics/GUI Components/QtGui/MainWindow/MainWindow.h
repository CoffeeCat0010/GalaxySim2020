#pragma once
#include "Corepch.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include "QTGenerated/uic/ui_MainWindow.h"
#include "Graphics/Window/OpenglContext.h"
#include "Graphics/Window/Window.h"
#include "Graphics/GUI Components/QtGui/OpenGlWidget/OpenGlWidget.h"
#include "Compute/CLprim/ComputeContext.h"
#include "Compute/CLprim/ComputePlatform.h"
#include "Graphics/GUI Components/QtGui/SimulationWidget/SimulationWidget.h"
#include "CL/cl.hpp"

namespace Graphics{
	class MainWindow : public QMainWindow, public Ui::MainWindow, public IWindow, public IOpenglContext
	{
		Q_OBJECT
	private:
		std::weak_ptr<Application::EventDispatcher> m_dispatcher;
		std::vector<Compute::Platform> m_platforms;
		uint32_t m_currPlatformIndex;
		CustomOpenGlWidget* m_ogl_widget;
		std::shared_ptr<Compute::Context> m_clContext;
		Compute::DeviceType m_selectedDeviceType;
		std::vector<std::shared_ptr<Compute::Device>> m_availableDevices;
		uint32_t m_currDeviceIndex;
		const std::map<QString, Compute::DeviceType> strToDeviceMap = { {"GPU", Compute::DeviceType::Device_GPU},
																																				 {"CPU", Compute::DeviceType::Device_CPU},
																																				 {"Accelerator", Compute::DeviceType::Device_Accelerator },
																																				 {"Default", Compute::DeviceType::Device_Default },
																																				 {"All", Compute::DeviceType::Device_All } };;

		QPointer<SimulationWidget> p_simWidget;
	public:
		MainWindow(std::weak_ptr<Application::EventDispatcher> dispatcher, QWidget *parent = Q_NULLPTR );
		~MainWindow();

		// Inherited via IWindow
		virtual void pollEvents () override;
		virtual void close () override;

		// Inherited via IOpenglContext
		virtual bool init () override;
		virtual void makeOGLContextCurrent () override {};
		virtual void paint () override;
		
	 signals:
		void contextUpdated (std::shared_ptr<Compute::Context> con);
	 signals:
		void deviceUpdated (std::shared_ptr<Compute::Device> device);

	
	protected:
		virtual void MainWindow::closeEvent(QCloseEvent * event) override;

		void updateContext();
	private slots:
		void onPlaySimulationTriggered ();
		void onLoadSimulationTriggered ();
		void onPauseSimulationTriggered ();
		void onPlatformSelected (int index);
		void onDeviceTypeSelected(QString type);
		void onDeviceSelected (int index);
		void onCreateSimulationTriggered();
	};
}

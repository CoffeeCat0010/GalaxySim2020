#pragma once
#include "Corepch.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include "QTGenerated/uic/ui_MainWindow.h"
#include "Graphics/Window/OpenglContext.h"
#include "Graphics/Window/Window.h"
#include "Graphics/GUI Components/QtGui/OpenGlWidget/OpenGlWidget.h"

namespace Graphics{
	class MainWindow : public QMainWindow, public Ui::MainWindow, public IWindow, public IOpenglContext
	{
		Q_OBJECT
	private:
		std::weak_ptr<Application::EventDispatcher> m_dispatcher;
		CustomOpenGlWidget* m_ogl_widget;
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
		//Inherited via QWidget
		/*std::string getFilePathFromDialog () {
			fileDialog = new QFileDialog()
		}*/
	protected:
		virtual void MainWindow::closeEvent(QCloseEvent * event) override;
	private slots:
		void onPlaySimulationTriggered ();
		void onLoadSimulationTriggered ();
		void onPauseSimulationTriggered ();
	};
}

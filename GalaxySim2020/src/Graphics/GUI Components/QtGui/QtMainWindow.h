#pragma once
#include <GL/glew.h>
#include <QMainWindow>
#include <QtGui>
#include "Graphics/Window/Window.h"
#include "Graphics/Window/OpenglContext.h"
#include "ui_QtMainWindow.h"

namespace QUI
{
	class QtMainWindow : public Ui_QtMainWindow, public Graphics::IWindow, public Graphics::IOpenglContext
	{
		Q_OBJECT

	public:
		QtMainWindow (QWidget* parent = Q_NULLPTR);
		~QtMainWindow ();
		void pollEvents () override;
		inline void makeOGLContextCurrent () override {	OGL_Viewport->makeCurrent (); }
		void paint () override;


	private:
		Ui::QtMainWindow ui;
	};
}

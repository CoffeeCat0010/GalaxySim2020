#include "QtMainWindow.h"
namespace QUI{
	QtMainWindow::QtMainWindow(QWidget *parent)
		: QMainWindow(parent)
	{
		ui.setupUi(this);
	}

	QtMainWindow::~QtMainWindow()
	{
	}
	void QtMainWindow::pollEvents ()
	{}
	void QtMainWindow::paint ()
	{}
}
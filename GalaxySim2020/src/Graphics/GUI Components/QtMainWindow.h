#pragma once

#include <QMainWindow>
#include "ui_QtMainWindow.h"

class QtMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QtMainWindow(QWidget *parent = Q_NULLPTR);
	~QtMainWindow();

private:
	Ui::QtMainWindow ui;
};

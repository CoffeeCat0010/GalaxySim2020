/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPlay_Simulation;
    QAction *actionLoad_Simulation;
    QAction *actionSave_Simulation_Configuration;
    QAction *actionCreate_Simulation;
    QAction *actionPause_simulation;
    QWidget *centralWidget;
    QSplitter *splitter;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *Config_Tabs;
    QWidget *OpenCL_tab;
    QFrame *line;
    QGroupBox *groupBox;
    QComboBox *Device_Select;
    QTextEdit *Device_Properties;
    QGroupBox *groupBox_2;
    QComboBox *Device_Type_Select;
    QGroupBox *groupBox_3;
    QComboBox *Platform_select;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *OpenGL_Layout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSimulation;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionPlay_Simulation = new QAction(MainWindow);
        actionPlay_Simulation->setObjectName(QString::fromUtf8("actionPlay_Simulation"));
        actionLoad_Simulation = new QAction(MainWindow);
        actionLoad_Simulation->setObjectName(QString::fromUtf8("actionLoad_Simulation"));
        actionSave_Simulation_Configuration = new QAction(MainWindow);
        actionSave_Simulation_Configuration->setObjectName(QString::fromUtf8("actionSave_Simulation_Configuration"));
        actionCreate_Simulation = new QAction(MainWindow);
        actionCreate_Simulation->setObjectName(QString::fromUtf8("actionCreate_Simulation"));
        actionPause_simulation = new QAction(MainWindow);
        actionPause_simulation->setObjectName(QString::fromUtf8("actionPause_simulation"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(0, 0, 1281, 671));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(true);
        horizontalLayoutWidget = new QWidget(splitter);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Config_Tabs = new QTabWidget(horizontalLayoutWidget);
        Config_Tabs->setObjectName(QString::fromUtf8("Config_Tabs"));
        OpenCL_tab = new QWidget();
        OpenCL_tab->setObjectName(QString::fromUtf8("OpenCL_tab"));
        line = new QFrame(OpenCL_tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 20, 241, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox = new QGroupBox(OpenCL_tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 170, 231, 141));
        Device_Select = new QComboBox(groupBox);
        Device_Select->setObjectName(QString::fromUtf8("Device_Select"));
        Device_Select->setGeometry(QRect(0, 20, 231, 22));
        Device_Properties = new QTextEdit(groupBox);
        Device_Properties->setObjectName(QString::fromUtf8("Device_Properties"));
        Device_Properties->setGeometry(QRect(0, 50, 231, 71));
        Device_Properties->setReadOnly(true);
        groupBox_2 = new QGroupBox(OpenCL_tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 110, 231, 51));
        Device_Type_Select = new QComboBox(groupBox_2);
        Device_Type_Select->addItem(QString());
        Device_Type_Select->addItem(QString());
        Device_Type_Select->addItem(QString());
        Device_Type_Select->addItem(QString());
        Device_Type_Select->addItem(QString());
        Device_Type_Select->setObjectName(QString::fromUtf8("Device_Type_Select"));
        Device_Type_Select->setGeometry(QRect(0, 20, 231, 22));
        groupBox_3 = new QGroupBox(OpenCL_tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 30, 231, 71));
        Platform_select = new QComboBox(groupBox_3);
        Platform_select->setObjectName(QString::fromUtf8("Platform_select"));
        Platform_select->setGeometry(QRect(0, 20, 231, 22));
        Config_Tabs->addTab(OpenCL_tab, QString());

        horizontalLayout->addWidget(Config_Tabs);

        splitter->addWidget(horizontalLayoutWidget);
        horizontalLayoutWidget_2 = new QWidget(splitter);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        OpenGL_Layout = new QHBoxLayout(horizontalLayoutWidget_2);
        OpenGL_Layout->setSpacing(6);
        OpenGL_Layout->setContentsMargins(11, 11, 11, 11);
        OpenGL_Layout->setObjectName(QString::fromUtf8("OpenGL_Layout"));
        OpenGL_Layout->setSizeConstraint(QLayout::SetMaximumSize);
        OpenGL_Layout->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(horizontalLayoutWidget_2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSimulation = new QMenu(menuBar);
        menuSimulation->setObjectName(QString::fromUtf8("menuSimulation"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSimulation->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionLoad_Simulation);
        menuFile->addAction(actionSave_Simulation_Configuration);
        menuSimulation->addAction(actionPlay_Simulation);
        menuSimulation->addAction(actionPause_simulation);
        menuSimulation->addAction(actionCreate_Simulation);

        retranslateUi(MainWindow);
        QObject::connect(actionPlay_Simulation, SIGNAL(triggered()), MainWindow, SLOT(onPlaySimulationTriggered()));
        QObject::connect(actionLoad_Simulation, SIGNAL(triggered()), MainWindow, SLOT(onLoadSimulationTriggered()));
        QObject::connect(actionPause_simulation, SIGNAL(triggered()), MainWindow, SLOT(onPauseSimulationTriggered()));
        QObject::connect(Device_Type_Select, SIGNAL(currentIndexChanged(QString)), MainWindow, SLOT(onDeviceTypeSelected(QString)));
        QObject::connect(Platform_select, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(onPlatformSelected(int)));
        QObject::connect(Device_Select, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(onDeviceSelected(int)));
        QObject::connect(actionCreate_Simulation, SIGNAL(triggered()), MainWindow, SLOT(onCreateSimulationTriggered()));

        Config_Tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionPlay_Simulation->setText(QCoreApplication::translate("MainWindow", "Play ", nullptr));
        actionLoad_Simulation->setText(QCoreApplication::translate("MainWindow", "Load Simulation", nullptr));
        actionSave_Simulation_Configuration->setText(QCoreApplication::translate("MainWindow", "Save Simulation Configuration", nullptr));
        actionCreate_Simulation->setText(QCoreApplication::translate("MainWindow", "Create ", nullptr));
        actionPause_simulation->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Selected OpenCL Device", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "OpenCL Device Type", nullptr));
        Device_Type_Select->setItemText(0, QCoreApplication::translate("MainWindow", "GPU", nullptr));
        Device_Type_Select->setItemText(1, QCoreApplication::translate("MainWindow", "CPU", nullptr));
        Device_Type_Select->setItemText(2, QCoreApplication::translate("MainWindow", "Accelerator", nullptr));
        Device_Type_Select->setItemText(3, QCoreApplication::translate("MainWindow", "Default", nullptr));
        Device_Type_Select->setItemText(4, QCoreApplication::translate("MainWindow", "All", nullptr));

        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        Config_Tabs->setTabText(Config_Tabs->indexOf(OpenCL_tab), QCoreApplication::translate("MainWindow", "OpenCL", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSimulation->setTitle(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

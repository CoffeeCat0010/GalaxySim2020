/********************************************************************************
** Form generated from reading UI file 'SimulationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONWIDGET_H
#define UI_SIMULATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src\Graphics\GUI Components\QtGui\SimulationWidget\SubWidgets\GravObjView.h"

QT_BEGIN_NAMESPACE

class Ui_SimulationWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *line;
    QFormLayout *scrollLayout;
    QLabel *timeStepsInputLabel;
    QLineEdit *timeStepsLine;
    QPushButton *SaveAsButton;
    QLineEdit *FilePath;
    QPushButton *RunSimulation;
    QUI::GravObjView *p_propertiesView;
    QListView *p_gravObjView;

    void setupUi(QWidget *SimulationWidget)
    {
        if (SimulationWidget->objectName().isEmpty())
            SimulationWidget->setObjectName(QString::fromUtf8("SimulationWidget"));
        SimulationWidget->resize(397, 390);
        SimulationWidget->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout_2 = new QVBoxLayout(SimulationWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(SimulationWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 377, 370));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        scrollLayout = new QFormLayout();
        scrollLayout->setSpacing(6);
        scrollLayout->setObjectName(QString::fromUtf8("scrollLayout"));
        timeStepsInputLabel = new QLabel(scrollAreaWidgetContents);
        timeStepsInputLabel->setObjectName(QString::fromUtf8("timeStepsInputLabel"));

        scrollLayout->setWidget(3, QFormLayout::LabelRole, timeStepsInputLabel);

        timeStepsLine = new QLineEdit(scrollAreaWidgetContents);
        timeStepsLine->setObjectName(QString::fromUtf8("timeStepsLine"));
        timeStepsLine->setToolTipDuration(-1);

        scrollLayout->setWidget(3, QFormLayout::FieldRole, timeStepsLine);

        SaveAsButton = new QPushButton(scrollAreaWidgetContents);
        SaveAsButton->setObjectName(QString::fromUtf8("SaveAsButton"));

        scrollLayout->setWidget(4, QFormLayout::LabelRole, SaveAsButton);

        FilePath = new QLineEdit(scrollAreaWidgetContents);
        FilePath->setObjectName(QString::fromUtf8("FilePath"));

        scrollLayout->setWidget(4, QFormLayout::FieldRole, FilePath);

        RunSimulation = new QPushButton(scrollAreaWidgetContents);
        RunSimulation->setObjectName(QString::fromUtf8("RunSimulation"));

        scrollLayout->setWidget(5, QFormLayout::SpanningRole, RunSimulation);

        p_propertiesView = new QUI::GravObjView(scrollAreaWidgetContents);
        p_propertiesView->setObjectName(QString::fromUtf8("p_propertiesView"));

        scrollLayout->setWidget(2, QFormLayout::SpanningRole, p_propertiesView);

        p_gravObjView = new QListView(scrollAreaWidgetContents);
        p_gravObjView->setObjectName(QString::fromUtf8("p_gravObjView"));

        scrollLayout->setWidget(1, QFormLayout::SpanningRole, p_gravObjView);


        verticalLayout->addLayout(scrollLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(SimulationWidget);
        QObject::connect(RunSimulation, SIGNAL(clicked()), SimulationWidget, SLOT(onRunSimulationClicked()));
        QObject::connect(SaveAsButton, SIGNAL(clicked()), SimulationWidget, SLOT(onSaveAsClicked()));

        QMetaObject::connectSlotsByName(SimulationWidget);
    } // setupUi

    void retranslateUi(QWidget *SimulationWidget)
    {
        SimulationWidget->setWindowTitle(QCoreApplication::translate("SimulationWidget", "SimulationWidget", nullptr));
        timeStepsInputLabel->setText(QCoreApplication::translate("SimulationWidget", "Number of Time Steps:", nullptr));
#if QT_CONFIG(tooltip)
        timeStepsLine->setToolTip(QCoreApplication::translate("SimulationWidget", "Number of Time steps", nullptr));
#endif // QT_CONFIG(tooltip)
        SaveAsButton->setText(QCoreApplication::translate("SimulationWidget", "Save As...", nullptr));
        RunSimulation->setText(QCoreApplication::translate("SimulationWidget", "Run Simulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationWidget: public Ui_SimulationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONWIDGET_H

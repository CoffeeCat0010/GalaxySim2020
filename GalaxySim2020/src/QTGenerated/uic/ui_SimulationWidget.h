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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationWidget
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *formLayoutWidget;
    QFormLayout *scrollLayout;
    QPushButton *SaveAsButton;
    QLineEdit *FilePath;
    QPushButton *RunSimulation;
    QLineEdit *timeStepsLine;
    QLabel *label;

    void setupUi(QWidget *SimulationWidget)
    {
        if (SimulationWidget->objectName().isEmpty())
            SimulationWidget->setObjectName(QString::fromUtf8("SimulationWidget"));
        SimulationWidget->resize(400, 300);
        scrollArea = new QScrollArea(SimulationWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 321, 291));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 319, 289));
        formLayoutWidget = new QWidget(scrollAreaWidgetContents);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 311, 281));
        scrollLayout = new QFormLayout(formLayoutWidget);
        scrollLayout->setSpacing(6);
        scrollLayout->setContentsMargins(11, 11, 11, 11);
        scrollLayout->setObjectName(QString::fromUtf8("scrollLayout"));
        scrollLayout->setContentsMargins(0, 0, 0, 0);
        SaveAsButton = new QPushButton(formLayoutWidget);
        SaveAsButton->setObjectName(QString::fromUtf8("SaveAsButton"));

        scrollLayout->setWidget(1, QFormLayout::LabelRole, SaveAsButton);

        FilePath = new QLineEdit(formLayoutWidget);
        FilePath->setObjectName(QString::fromUtf8("FilePath"));

        scrollLayout->setWidget(1, QFormLayout::FieldRole, FilePath);

        RunSimulation = new QPushButton(formLayoutWidget);
        RunSimulation->setObjectName(QString::fromUtf8("RunSimulation"));

        scrollLayout->setWidget(2, QFormLayout::SpanningRole, RunSimulation);

        timeStepsLine = new QLineEdit(formLayoutWidget);
        timeStepsLine->setObjectName(QString::fromUtf8("timeStepsLine"));

        scrollLayout->setWidget(0, QFormLayout::FieldRole, timeStepsLine);

        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        scrollLayout->setWidget(0, QFormLayout::LabelRole, label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(SimulationWidget);
        QObject::connect(RunSimulation, SIGNAL(clicked()), SimulationWidget, SLOT(onRunSimulationClicked()));
        QObject::connect(SaveAsButton, SIGNAL(clicked()), SimulationWidget, SLOT(onSaveAsClicked()));

        QMetaObject::connectSlotsByName(SimulationWidget);
    } // setupUi

    void retranslateUi(QWidget *SimulationWidget)
    {
        SimulationWidget->setWindowTitle(QCoreApplication::translate("SimulationWidget", "SimulationWidget", nullptr));
        SaveAsButton->setText(QCoreApplication::translate("SimulationWidget", "Save As...", nullptr));
        RunSimulation->setText(QCoreApplication::translate("SimulationWidget", "Run Simulation", nullptr));
        label->setText(QCoreApplication::translate("SimulationWidget", "Number of Time Steps:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationWidget: public Ui_SimulationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONWIDGET_H

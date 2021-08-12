/********************************************************************************
** Form generated from reading UI file 'SimulationProgress.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONPROGRESS_H
#define UI_SIMULATIONPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationProgress
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;
    QLabel *ProgressInfoLabel;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *SimulationProgress)
    {
        if (SimulationProgress->objectName().isEmpty())
            SimulationProgress->setObjectName(QString::fromUtf8("SimulationProgress"));
        SimulationProgress->resize(400, 300);
        verticalLayout = new QVBoxLayout(SimulationProgress);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(SimulationProgress);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        verticalLayout_2->addWidget(progressBar);

        ProgressInfoLabel = new QLabel(groupBox);
        ProgressInfoLabel->setObjectName(QString::fromUtf8("ProgressInfoLabel"));
        ProgressInfoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(ProgressInfoLabel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        verticalLayout->addWidget(groupBox);


        retranslateUi(SimulationProgress);

        QMetaObject::connectSlotsByName(SimulationProgress);
    } // setupUi

    void retranslateUi(QWidget *SimulationProgress)
    {
        SimulationProgress->setWindowTitle(QCoreApplication::translate("SimulationProgress", "SimulationProgress", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SimulationProgress", "Simulation Progress", nullptr));
        ProgressInfoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SimulationProgress: public Ui_SimulationProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONPROGRESS_H

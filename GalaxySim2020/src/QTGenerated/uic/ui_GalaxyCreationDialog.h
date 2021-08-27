/********************************************************************************
** Form generated from reading UI file 'GalaxyCreationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALAXYCREATIONDIALOG_H
#define UI_GALAXYCREATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GalaxyCreationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *p_posAndRotGrp;
    QGridLayout *gridLayout_2;
    QLineEdit *p_zPosLEdit;
    QLineEdit *p_yPosLEdit;
    QLabel *p_yPosLabel;
    QLineEdit *p_xPosLEdit;
    QLabel *p_xRotLabel;
    QLabel *p_zPosLabel;
    QLabel *p_zRotLabel;
    QLabel *p_yRotLabel;
    QLabel *p_xPosLabel;
    QDoubleSpinBox *p_xRotDSBox;
    QDoubleSpinBox *p_yRotDSBox;
    QDoubleSpinBox *p_zRotDSBox;
    QGroupBox *p_GalSettingsGrp;
    QGridLayout *gridLayout_3;
    QLineEdit *p_galDiameterLEdit;
    QComboBox *p_centMassCombo;
    QLabel *p_galDiameterLabel;
    QLabel *p_massOfCentLabel;
    QLabel *p_centMassLabel;
    QLineEdit *p_massOfCentMassLEdit;
    QGroupBox *p_starSettingsGrp;
    QGridLayout *gridLayout_4;
    QLineEdit *p_numStarLEdit;
    QLabel *p_numStarsLabel;
    QDoubleSpinBox *p_starMassDSBox;
    QLabel *p_starMassLabel;
    QDialogButtonBox *p_buttonBox;
    QLabel *p_warnLabel;

    void setupUi(QDialog *GalaxyCreationDialog)
    {
        if (GalaxyCreationDialog->objectName().isEmpty())
            GalaxyCreationDialog->setObjectName(QString::fromUtf8("GalaxyCreationDialog"));
        GalaxyCreationDialog->resize(545, 315);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GalaxyCreationDialog->sizePolicy().hasHeightForWidth());
        GalaxyCreationDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(GalaxyCreationDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        p_posAndRotGrp = new QGroupBox(GalaxyCreationDialog);
        p_posAndRotGrp->setObjectName(QString::fromUtf8("p_posAndRotGrp"));
        gridLayout_2 = new QGridLayout(p_posAndRotGrp);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        p_zPosLEdit = new QLineEdit(p_posAndRotGrp);
        p_zPosLEdit->setObjectName(QString::fromUtf8("p_zPosLEdit"));

        gridLayout_2->addWidget(p_zPosLEdit, 2, 1, 1, 1);

        p_yPosLEdit = new QLineEdit(p_posAndRotGrp);
        p_yPosLEdit->setObjectName(QString::fromUtf8("p_yPosLEdit"));

        gridLayout_2->addWidget(p_yPosLEdit, 1, 1, 1, 1);

        p_yPosLabel = new QLabel(p_posAndRotGrp);
        p_yPosLabel->setObjectName(QString::fromUtf8("p_yPosLabel"));

        gridLayout_2->addWidget(p_yPosLabel, 1, 0, 1, 1);

        p_xPosLEdit = new QLineEdit(p_posAndRotGrp);
        p_xPosLEdit->setObjectName(QString::fromUtf8("p_xPosLEdit"));

        gridLayout_2->addWidget(p_xPosLEdit, 0, 1, 1, 1);

        p_xRotLabel = new QLabel(p_posAndRotGrp);
        p_xRotLabel->setObjectName(QString::fromUtf8("p_xRotLabel"));

        gridLayout_2->addWidget(p_xRotLabel, 0, 2, 1, 1);

        p_zPosLabel = new QLabel(p_posAndRotGrp);
        p_zPosLabel->setObjectName(QString::fromUtf8("p_zPosLabel"));

        gridLayout_2->addWidget(p_zPosLabel, 2, 0, 1, 1);

        p_zRotLabel = new QLabel(p_posAndRotGrp);
        p_zRotLabel->setObjectName(QString::fromUtf8("p_zRotLabel"));

        gridLayout_2->addWidget(p_zRotLabel, 2, 2, 1, 1);

        p_yRotLabel = new QLabel(p_posAndRotGrp);
        p_yRotLabel->setObjectName(QString::fromUtf8("p_yRotLabel"));

        gridLayout_2->addWidget(p_yRotLabel, 1, 2, 1, 1);

        p_xPosLabel = new QLabel(p_posAndRotGrp);
        p_xPosLabel->setObjectName(QString::fromUtf8("p_xPosLabel"));

        gridLayout_2->addWidget(p_xPosLabel, 0, 0, 1, 1);

        p_xRotDSBox = new QDoubleSpinBox(p_posAndRotGrp);
        p_xRotDSBox->setObjectName(QString::fromUtf8("p_xRotDSBox"));
        p_xRotDSBox->setMinimum(-179.990000000000009);
        p_xRotDSBox->setMaximum(179.990000000000009);

        gridLayout_2->addWidget(p_xRotDSBox, 0, 3, 1, 1);

        p_yRotDSBox = new QDoubleSpinBox(p_posAndRotGrp);
        p_yRotDSBox->setObjectName(QString::fromUtf8("p_yRotDSBox"));
        p_yRotDSBox->setMinimum(-179.990000000000009);
        p_yRotDSBox->setMaximum(179.990000000000009);

        gridLayout_2->addWidget(p_yRotDSBox, 1, 3, 1, 1);

        p_zRotDSBox = new QDoubleSpinBox(p_posAndRotGrp);
        p_zRotDSBox->setObjectName(QString::fromUtf8("p_zRotDSBox"));
        p_zRotDSBox->setMinimum(-179.990000000000009);
        p_zRotDSBox->setMaximum(179.990000000000009);

        gridLayout_2->addWidget(p_zRotDSBox, 2, 3, 1, 1);


        verticalLayout->addWidget(p_posAndRotGrp);

        p_GalSettingsGrp = new QGroupBox(GalaxyCreationDialog);
        p_GalSettingsGrp->setObjectName(QString::fromUtf8("p_GalSettingsGrp"));
        gridLayout_3 = new QGridLayout(p_GalSettingsGrp);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        p_galDiameterLEdit = new QLineEdit(p_GalSettingsGrp);
        p_galDiameterLEdit->setObjectName(QString::fromUtf8("p_galDiameterLEdit"));

        gridLayout_3->addWidget(p_galDiameterLEdit, 1, 1, 1, 1);

        p_centMassCombo = new QComboBox(p_GalSettingsGrp);
        p_centMassCombo->addItem(QString());
        p_centMassCombo->addItem(QString());
        p_centMassCombo->setObjectName(QString::fromUtf8("p_centMassCombo"));

        gridLayout_3->addWidget(p_centMassCombo, 0, 1, 1, 1);

        p_galDiameterLabel = new QLabel(p_GalSettingsGrp);
        p_galDiameterLabel->setObjectName(QString::fromUtf8("p_galDiameterLabel"));

        gridLayout_3->addWidget(p_galDiameterLabel, 1, 0, 1, 1);

        p_massOfCentLabel = new QLabel(p_GalSettingsGrp);
        p_massOfCentLabel->setObjectName(QString::fromUtf8("p_massOfCentLabel"));

        gridLayout_3->addWidget(p_massOfCentLabel, 0, 2, 1, 1);

        p_centMassLabel = new QLabel(p_GalSettingsGrp);
        p_centMassLabel->setObjectName(QString::fromUtf8("p_centMassLabel"));

        gridLayout_3->addWidget(p_centMassLabel, 0, 0, 1, 1);

        p_massOfCentMassLEdit = new QLineEdit(p_GalSettingsGrp);
        p_massOfCentMassLEdit->setObjectName(QString::fromUtf8("p_massOfCentMassLEdit"));

        gridLayout_3->addWidget(p_massOfCentMassLEdit, 0, 3, 1, 1);


        verticalLayout->addWidget(p_GalSettingsGrp);

        p_starSettingsGrp = new QGroupBox(GalaxyCreationDialog);
        p_starSettingsGrp->setObjectName(QString::fromUtf8("p_starSettingsGrp"));
        gridLayout_4 = new QGridLayout(p_starSettingsGrp);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        p_numStarLEdit = new QLineEdit(p_starSettingsGrp);
        p_numStarLEdit->setObjectName(QString::fromUtf8("p_numStarLEdit"));

        gridLayout_4->addWidget(p_numStarLEdit, 0, 1, 1, 1);

        p_numStarsLabel = new QLabel(p_starSettingsGrp);
        p_numStarsLabel->setObjectName(QString::fromUtf8("p_numStarsLabel"));

        gridLayout_4->addWidget(p_numStarsLabel, 0, 0, 1, 1);

        p_starMassDSBox = new QDoubleSpinBox(p_starSettingsGrp);
        p_starMassDSBox->setObjectName(QString::fromUtf8("p_starMassDSBox"));

        gridLayout_4->addWidget(p_starMassDSBox, 0, 3, 1, 1);

        p_starMassLabel = new QLabel(p_starSettingsGrp);
        p_starMassLabel->setObjectName(QString::fromUtf8("p_starMassLabel"));

        gridLayout_4->addWidget(p_starMassLabel, 0, 2, 1, 1);


        verticalLayout->addWidget(p_starSettingsGrp);

        p_buttonBox = new QDialogButtonBox(GalaxyCreationDialog);
        p_buttonBox->setObjectName(QString::fromUtf8("p_buttonBox"));
        p_buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(p_buttonBox);

        p_warnLabel = new QLabel(GalaxyCreationDialog);
        p_warnLabel->setObjectName(QString::fromUtf8("p_warnLabel"));

        verticalLayout->addWidget(p_warnLabel);


        retranslateUi(GalaxyCreationDialog);
        QObject::connect(p_buttonBox, SIGNAL(accepted()), GalaxyCreationDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(GalaxyCreationDialog);
    } // setupUi

    void retranslateUi(QDialog *GalaxyCreationDialog)
    {
        GalaxyCreationDialog->setWindowTitle(QCoreApplication::translate("GalaxyCreationDialog", "GalaxyCreationDialog", nullptr));
        p_posAndRotGrp->setTitle(QCoreApplication::translate("GalaxyCreationDialog", "Position and Rotation", nullptr));
#if QT_CONFIG(tooltip)
        p_zPosLEdit->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "This is front to back coordinate. The \n"
"screen is at 0 and max is 10,000. \n"
"Units [Parsecs]", nullptr));
#endif // QT_CONFIG(tooltip)
        p_zPosLEdit->setText(QCoreApplication::translate("GalaxyCreationDialog", "0", nullptr));
#if QT_CONFIG(tooltip)
        p_yPosLEdit->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "The up and down cordinate. Negative \n"
"values are down and positive are up. \n"
" Units: [Parsecs]", nullptr));
#endif // QT_CONFIG(tooltip)
        p_yPosLEdit->setText(QCoreApplication::translate("GalaxyCreationDialog", "0", nullptr));
        p_yPosLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Position Y:", nullptr));
#if QT_CONFIG(tooltip)
        p_xPosLEdit->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "The left and right cordinate. Negative \n"
"values are left and positive are right. \n"
" Units: [Parsecs]", nullptr));
#endif // QT_CONFIG(tooltip)
        p_xPosLEdit->setText(QCoreApplication::translate("GalaxyCreationDialog", "0", nullptr));
        p_xRotLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "X Rotation:", nullptr));
        p_zPosLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Position Z:", nullptr));
        p_zRotLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Z Rotation:", nullptr));
        p_yRotLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Y Rotation:", nullptr));
        p_xPosLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Position X:", nullptr));
#if QT_CONFIG(tooltip)
        p_xRotDSBox->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "0 degrees of rotation for x, y, and z\n"
"corrisponds to the axis of rotation \n"
"coming out of the screen.\n"
"Units: Degrees  ", nullptr));
#endif // QT_CONFIG(tooltip)
        p_xRotDSBox->setSuffix(QCoreApplication::translate("GalaxyCreationDialog", "\302\260", nullptr));
#if QT_CONFIG(tooltip)
        p_yRotDSBox->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "0 degrees of rotation for x, y, and z\n"
"corrisponds to the axis of rotation \n"
"coming out of the screen.\n"
"Units: Degrees  ", nullptr));
#endif // QT_CONFIG(tooltip)
        p_yRotDSBox->setSuffix(QCoreApplication::translate("GalaxyCreationDialog", "\302\260", nullptr));
#if QT_CONFIG(tooltip)
        p_zRotDSBox->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "0 degrees of rotation for x, y, and z\n"
"corrisponds to the axis of rotation \n"
"coming out of the screen.\n"
"Units: Degrees  ", nullptr));
#endif // QT_CONFIG(tooltip)
        p_zRotDSBox->setSuffix(QCoreApplication::translate("GalaxyCreationDialog", "\302\260", nullptr));
        p_GalSettingsGrp->setTitle(QCoreApplication::translate("GalaxyCreationDialog", "Galaxy dimensions", nullptr));
#if QT_CONFIG(tooltip)
        p_galDiameterLEdit->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "Units: [Parsecs]", nullptr));
#endif // QT_CONFIG(tooltip)
        p_galDiameterLEdit->setText(QCoreApplication::translate("GalaxyCreationDialog", "12500", nullptr));
        p_centMassCombo->setItemText(0, QCoreApplication::translate("GalaxyCreationDialog", "Yes", nullptr));
        p_centMassCombo->setItemText(1, QCoreApplication::translate("GalaxyCreationDialog", "No", nullptr));

        p_galDiameterLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Diameter:", nullptr));
        p_massOfCentLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Mass of central mass:", nullptr));
        p_centMassLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Central mass:", nullptr));
#if QT_CONFIG(tooltip)
        p_massOfCentMassLEdit->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "Units: Millions of solar masses", nullptr));
#endif // QT_CONFIG(tooltip)
        p_massOfCentMassLEdit->setText(QCoreApplication::translate("GalaxyCreationDialog", "1500", nullptr));
        p_starSettingsGrp->setTitle(QCoreApplication::translate("GalaxyCreationDialog", "Star Settings", nullptr));
#if QT_CONFIG(tooltip)
        p_numStarLEdit->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "<html><head/><body><p>Number of stars in the galaxy.</p><p>For performance reasons it is better</p><p>to use powers of two.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        p_numStarLEdit->setInputMask(QString());
        p_numStarLEdit->setText(QCoreApplication::translate("GalaxyCreationDialog", "8192", nullptr));
        p_numStarLEdit->setPlaceholderText(QString());
        p_numStarsLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Number of Stars:", nullptr));
#if QT_CONFIG(tooltip)
        p_starMassDSBox->setToolTip(QCoreApplication::translate("GalaxyCreationDialog", "Mass in solar masses", nullptr));
#endif // QT_CONFIG(tooltip)
        p_starMassLabel->setText(QCoreApplication::translate("GalaxyCreationDialog", "Mass of stars:", nullptr));
        p_warnLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GalaxyCreationDialog: public Ui_GalaxyCreationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALAXYCREATIONDIALOG_H

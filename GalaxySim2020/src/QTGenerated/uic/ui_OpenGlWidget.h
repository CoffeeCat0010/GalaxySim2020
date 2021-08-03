/********************************************************************************
** Form generated from reading UI file 'OpenGlWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLWIDGET_H
#define UI_OPENGLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QOpenGLWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGlWidget
{
public:

    void setupUi(QOpenGLWidget *OpenGlWidget)
    {
        if (OpenGlWidget->objectName().isEmpty())
            OpenGlWidget->setObjectName(QString::fromUtf8("OpenGlWidget"));
        OpenGlWidget->resize(400, 300);

        retranslateUi(OpenGlWidget);

        QMetaObject::connectSlotsByName(OpenGlWidget);
    } // setupUi

    void retranslateUi(QOpenGLWidget *OpenGlWidget)
    {
        OpenGlWidget->setWindowTitle(QCoreApplication::translate("OpenGlWidget", "OpenGlWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenGlWidget: public Ui_OpenGlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLWIDGET_H

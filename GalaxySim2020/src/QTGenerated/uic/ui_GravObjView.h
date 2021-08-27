/********************************************************************************
** Form generated from reading UI file 'GravObjView.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAVOBJVIEW_H
#define UI_GRAVOBJVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_GravObjView
{
public:

    void setupUi(QTreeView *GravObjView)
    {
        if (GravObjView->objectName().isEmpty())
            GravObjView->setObjectName(QString::fromUtf8("GravObjView"));
        GravObjView->resize(400, 300);
        if (GravObjView->header()->objectName().isEmpty())

        retranslateUi(GravObjView);

        QMetaObject::connectSlotsByName(GravObjView);
    } // setupUi

    void retranslateUi(QTreeView *GravObjView)
    {
        GravObjView->setWindowTitle(QCoreApplication::translate("GravObjView", "GravObjView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GravObjView: public Ui_GravObjView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAVOBJVIEW_H

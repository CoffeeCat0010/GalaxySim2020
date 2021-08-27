/********************************************************************************
** Form generated from reading UI file 'GalaxyTreeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALAXYTREEWIDGET_H
#define UI_GALAXYTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_GalaxyTreeWidget
{
public:

    void setupUi(QTreeWidget *GalaxyTreeWidget)
    {
        if (GalaxyTreeWidget->objectName().isEmpty())
            GalaxyTreeWidget->setObjectName(QString::fromUtf8("GalaxyTreeWidget"));
        GalaxyTreeWidget->resize(400, 300);
        GalaxyTreeWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        GalaxyTreeWidget->setSortingEnabled(true);
        if (GalaxyTreeWidget->header()->objectName().isEmpty())

        retranslateUi(GalaxyTreeWidget);

        QMetaObject::connectSlotsByName(GalaxyTreeWidget);
    } // setupUi

    void retranslateUi(QTreeWidget *GalaxyTreeWidget)
    {
        QTreeWidgetItem *___qtreewidgetitem = GalaxyTreeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("GalaxyTreeWidget", "Properties", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("GalaxyTreeWidget", "Items", nullptr));
        GalaxyTreeWidget->setWindowTitle(QCoreApplication::translate("GalaxyTreeWidget", "GalaxyTreeWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GalaxyTreeWidget: public Ui_GalaxyTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALAXYTREEWIDGET_H

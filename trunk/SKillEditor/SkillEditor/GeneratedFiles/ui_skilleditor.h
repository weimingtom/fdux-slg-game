/********************************************************************************
** Form generated from reading UI file 'skilleditor.ui'
**
** Created: Sun Oct 9 10:44:28 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKILLEDITOR_H
#define UI_SKILLEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>
#include "renderwindow.h"
#include "timebar.h"

QT_BEGIN_NAMESPACE

class Ui_SkillEditorClass
{
public:
    QAction *actionAddItem;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    IIRenderWindow *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *treeWidget;
    TimeBar *widget;

    void setupUi(QMainWindow *SkillEditorClass)
    {
        if (SkillEditorClass->objectName().isEmpty())
            SkillEditorClass->setObjectName(QString::fromUtf8("SkillEditorClass"));
        SkillEditorClass->resize(658, 427);
        actionAddItem = new QAction(SkillEditorClass);
        actionAddItem->setObjectName(QString::fromUtf8("actionAddItem"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../\347\264\240\346\235\220\345\214\272/PNGico090418/NetByte Design Studio - 0022.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddItem->setIcon(icon);
        centralWidget = new QWidget(SkillEditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new IIRenderWindow(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        SkillEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SkillEditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 658, 23));
        SkillEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SkillEditorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SkillEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SkillEditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SkillEditorClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(SkillEditorClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        treeWidget = new QTreeWidget(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        horizontalLayout_2->addWidget(treeWidget);

        widget = new TimeBar(dockWidgetContents);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout_2->addWidget(widget);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 9);
        dockWidget->setWidget(dockWidgetContents);
        SkillEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget);

        mainToolBar->addAction(actionAddItem);

        retranslateUi(SkillEditorClass);

        QMetaObject::connectSlotsByName(SkillEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SkillEditorClass)
    {
        SkillEditorClass->setWindowTitle(QApplication::translate("SkillEditorClass", "SkillEditor", 0, QApplication::UnicodeUTF8));
        actionAddItem->setText(QApplication::translate("SkillEditorClass", "addItem", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("SkillEditorClass", "TimeBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SkillEditorClass: public Ui_SkillEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKILLEDITOR_H

/********************************************************************************
** Form generated from reading UI file 'launcher.ui'
**
** Created: Mon Sep 26 10:38:20 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LauncherClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCommandLinkButton *commandLinkButton;
    QCommandLinkButton *commandLinkButton_2;
    QCommandLinkButton *commandLinkButton_3;
    QCommandLinkButton *commandLinkButton_4;
    QCommandLinkButton *commandLinkButton_7;
    QCommandLinkButton *commandLinkButton_5;
    QCommandLinkButton *commandLinkButton_6;
    QLabel *label;

    void setupUi(QMainWindow *LauncherClass)
    {
        if (LauncherClass->objectName().isEmpty())
            LauncherClass->setObjectName(QString::fromUtf8("LauncherClass"));
        LauncherClass->resize(711, 401);
        LauncherClass->setMinimumSize(QSize(711, 401));
        LauncherClass->setMaximumSize(QSize(711, 401));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Link, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Link, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Link, brush);
        LauncherClass->setPalette(palette);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Launcher/Resources/Demo.png"), QSize(), QIcon::Normal, QIcon::Off);
        LauncherClass->setWindowIcon(icon);
        centralWidget = new QWidget(LauncherClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(490, 60, 181, 325));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        commandLinkButton = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton);

        commandLinkButton_2 = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton_2->setObjectName(QString::fromUtf8("commandLinkButton_2"));
        commandLinkButton_2->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton_2);

        commandLinkButton_3 = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton_3->setObjectName(QString::fromUtf8("commandLinkButton_3"));
        commandLinkButton_3->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton_3);

        commandLinkButton_4 = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton_4->setObjectName(QString::fromUtf8("commandLinkButton_4"));
        commandLinkButton_4->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton_4);

        commandLinkButton_7 = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton_7->setObjectName(QString::fromUtf8("commandLinkButton_7"));
        commandLinkButton_7->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton_7);

        commandLinkButton_5 = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton_5->setObjectName(QString::fromUtf8("commandLinkButton_5"));
        commandLinkButton_5->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton_5);

        commandLinkButton_6 = new QCommandLinkButton(verticalLayoutWidget);
        commandLinkButton_6->setObjectName(QString::fromUtf8("commandLinkButton_6"));
        commandLinkButton_6->setStyleSheet(QString::fromUtf8("QCommandLinkButton{\n"
"	font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        verticalLayout->addWidget(commandLinkButton_6);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 200, 341, 91));
        LauncherClass->setCentralWidget(centralWidget);

        retranslateUi(LauncherClass);

        QMetaObject::connectSlotsByName(LauncherClass);
    } // setupUi

    void retranslateUi(QMainWindow *LauncherClass)
    {
        LauncherClass->setWindowTitle(QApplication::translate("LauncherClass", "\345\277\230\345\215\264\347\232\204\346\210\230\345\234\272-\346\265\213\350\257\225\347\211\210", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("LauncherClass", "\347\252\227\345\217\243\346\250\241\345\274\217\350\277\220\350\241\214\346\270\270\346\210\217", 0, QApplication::UnicodeUTF8));
        commandLinkButton_2->setText(QApplication::translate("LauncherClass", "\345\205\250\345\261\217\346\250\241\345\274\217\350\277\220\350\241\214\346\270\270\346\210\217", 0, QApplication::UnicodeUTF8));
        commandLinkButton_3->setText(QApplication::translate("LauncherClass", "\346\270\270\346\210\217\346\211\213\345\206\214", 0, QApplication::UnicodeUTF8));
        commandLinkButton_4->setText(QApplication::translate("LauncherClass", "\350\207\252\350\277\260\346\226\207\346\241\243", 0, QApplication::UnicodeUTF8));
        commandLinkButton_7->setText(QApplication::translate("LauncherClass", "\346\204\217\350\247\201\345\217\215\351\246\210", 0, QApplication::UnicodeUTF8));
        commandLinkButton_5->setText(QApplication::translate("LauncherClass", "\345\256\211\350\243\205Directx9.0C", 0, QApplication::UnicodeUTF8));
        commandLinkButton_6->setText(QApplication::translate("LauncherClass", "\345\271\273\347\210\265\345\256\230\346\226\271\347\275\221\347\253\231", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LauncherClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:20pt; font-weight:600; color:#ff0000;\">\346\263\250\346\204\217!</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#ff0000;\">\345\246\202\346\236\234\345\234\250\350\277\233\345\205\245\346\210\230\346\226\227\347\225\214\351\235\242\346\227\266\347\250\213\345\272\217\345\264\251\346\272\203,</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0"
                        "px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#ff0000;\">\350\257\267\347\202\271\345\207\273\345\217\263\344\276\247\346\214\211\351\222\256,\345\256\211\350\243\205Directx9.0C.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LauncherClass: public Ui_LauncherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H

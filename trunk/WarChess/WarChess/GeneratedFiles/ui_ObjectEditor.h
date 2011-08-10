/********************************************************************************
** Form generated from reading UI file 'ObjectEditor.ui'
**
** Created: Fri Mar 25 17:10:58 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTEDITOR_H
#define UI_OBJECTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ObjectEditorClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ObjectName;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *button_ok;
    QPushButton *button_cancel;

    void setupUi(QDialog *ObjectEditorClass)
    {
        if (ObjectEditorClass->objectName().isEmpty())
            ObjectEditorClass->setObjectName(QString::fromUtf8("ObjectEditorClass"));
        ObjectEditorClass->resize(389, 71);
        verticalLayout = new QVBoxLayout(ObjectEditorClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(ObjectEditorClass);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        ObjectName = new QLineEdit(ObjectEditorClass);
        ObjectName->setObjectName(QString::fromUtf8("ObjectName"));

        horizontalLayout->addWidget(ObjectName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        button_ok = new QPushButton(ObjectEditorClass);
        button_ok->setObjectName(QString::fromUtf8("button_ok"));

        horizontalLayout_2->addWidget(button_ok);

        button_cancel = new QPushButton(ObjectEditorClass);
        button_cancel->setObjectName(QString::fromUtf8("button_cancel"));

        horizontalLayout_2->addWidget(button_cancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ObjectEditorClass);

        QMetaObject::connectSlotsByName(ObjectEditorClass);
    } // setupUi

    void retranslateUi(QDialog *ObjectEditorClass)
    {
        ObjectEditorClass->setWindowTitle(QApplication::translate("ObjectEditorClass", "\345\234\272\346\231\257\345\257\271\350\261\241\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectEditorClass", "\345\220\215\347\247\260:", 0, QApplication::UnicodeUTF8));
        button_ok->setText(QApplication::translate("ObjectEditorClass", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        button_cancel->setText(QApplication::translate("ObjectEditorClass", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectEditorClass: public Ui_ObjectEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTEDITOR_H

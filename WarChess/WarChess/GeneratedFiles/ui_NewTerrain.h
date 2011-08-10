/********************************************************************************
** Form generated from reading UI file 'NewTerrain.ui'
**
** Created: Wed Dec 1 11:26:49 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWTERRAIN_H
#define UI_NEWTERRAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewTerrain
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *NewTerrain)
    {
        if (NewTerrain->objectName().isEmpty())
            NewTerrain->setObjectName(QString::fromUtf8("NewTerrain"));
        NewTerrain->resize(397, 133);
        verticalLayout = new QVBoxLayout(NewTerrain);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(NewTerrain);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayout = new QFormLayout(groupBox_3);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        lineEdit_6 = new QLineEdit(groupBox_3);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_6);

        lineEdit_7 = new QLineEdit(groupBox_3);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_7);


        verticalLayout->addWidget(groupBox_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        okButton = new QPushButton(NewTerrain);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(NewTerrain);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NewTerrain);
        QObject::connect(okButton, SIGNAL(clicked()), NewTerrain, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), NewTerrain, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewTerrain);
    } // setupUi

    void retranslateUi(QDialog *NewTerrain)
    {
        NewTerrain->setWindowTitle(QApplication::translate("NewTerrain", "\346\226\260\345\273\272\345\234\260\345\275\242", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("NewTerrain", "\347\275\221\346\240\274", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewTerrain", "\346\257\217\344\270\252\347\275\221\346\240\274\350\276\271\351\225\277:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NewTerrain", "\345\234\260\345\233\276\346\240\274\346\225\260:", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("NewTerrain", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("NewTerrain", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewTerrain: public Ui_NewTerrain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWTERRAIN_H

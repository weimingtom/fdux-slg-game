/********************************************************************************
** Form generated from reading UI file 'scripteditor.ui'
**
** Created: Sun Jul 17 18:29:55 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPTEDITOR_H
#define UI_SCRIPTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScriptEditorClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_19;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *scrEdit;
    QVBoxLayout *verticalLayout_4;
    QPushButton *ClearButton;
    QPushButton *ParseButton;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_23;
    QPlainTextEdit *initEdit;
    QLabel *label_24;
    QTextEdit *luaEdit;
    QLabel *label_22;
    QTextEdit *retEdit;
    QPushButton *RunButton;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ImageFileNameEdit;
    QLabel *label_20;
    QLineEdit *universalTimeEdit;
    QLabel *label_2;
    QLineEdit *XEdit;
    QLabel *label_3;
    QLineEdit *YEdit;
    QPushButton *pushButton;
    QRadioButton *EffectsLayerButton;
    QRadioButton *MidLayerButton;
    QRadioButton *LeftLayerButton;
    QRadioButton *RightLayerButton;
    QRadioButton *BGLayerButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *DialogXEdit;
    QLabel *label_8;
    QLineEdit *MarginLeftEdit;
    QLabel *label_5;
    QLineEdit *DialogYEdit;
    QLabel *label_9;
    QLineEdit *MarginTopEdit;
    QLabel *label_6;
    QLineEdit *DialogWidthEdit;
    QLabel *label_11;
    QLineEdit *TextWidthEdit;
    QLabel *label_7;
    QLineEdit *DialogHeightEdit;
    QLabel *label_12;
    QLineEdit *TextHeightEdit;
    QLabel *label_10;
    QLineEdit *FontEdit;
    QPushButton *SetTextColorButton;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QLineEdit *RoleNameEdit;
    QPushButton *ShowRoleNameButton;
    QLabel *label_18;
    QLineEdit *DelayEdit;
    QTextEdit *TextEdit;
    QPushButton *ShowTextButton;
    QPushButton *ClearTextButton;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QLabel *label_13;
    QLineEdit *RoleNameXEdit;
    QLabel *label_14;
    QLineEdit *RoleNameYEdit;
    QPushButton *SetRoleNameColorButton;
    QLabel *label_16;
    QLineEdit *RoleNameFontEdit;
    QLabel *label_15;
    QLineEdit *RoleNameWidthEdit;
    QLabel *label_17;
    QLineEdit *RoleNameHeightEdit;
    QPushButton *SetDialogButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScriptEditorClass)
    {
        if (ScriptEditorClass->objectName().isEmpty())
            ScriptEditorClass->setObjectName(QString::fromUtf8("ScriptEditorClass"));
        ScriptEditorClass->resize(930, 652);
        centralWidget = new QWidget(ScriptEditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_19 = new QLabel(tab_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_3->addWidget(label_19);

        label_21 = new QLabel(tab_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_3->addWidget(label_21);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        scrEdit = new QTextEdit(tab_2);
        scrEdit->setObjectName(QString::fromUtf8("scrEdit"));

        horizontalLayout_2->addWidget(scrEdit);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ClearButton = new QPushButton(tab_2);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));

        verticalLayout_4->addWidget(ClearButton);

        ParseButton = new QPushButton(tab_2);
        ParseButton->setObjectName(QString::fromUtf8("ParseButton"));

        verticalLayout_4->addWidget(ParseButton);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_23 = new QLabel(tab_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        verticalLayout_3->addWidget(label_23);

        initEdit = new QPlainTextEdit(tab_2);
        initEdit->setObjectName(QString::fromUtf8("initEdit"));

        verticalLayout_3->addWidget(initEdit);

        label_24 = new QLabel(tab_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        verticalLayout_3->addWidget(label_24);

        luaEdit = new QTextEdit(tab_2);
        luaEdit->setObjectName(QString::fromUtf8("luaEdit"));

        verticalLayout_3->addWidget(luaEdit);

        label_22 = new QLabel(tab_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        verticalLayout_3->addWidget(label_22);

        retEdit = new QTextEdit(tab_2);
        retEdit->setObjectName(QString::fromUtf8("retEdit"));

        verticalLayout_3->addWidget(retEdit);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(1, 1);
        verticalLayout_3->setStretch(3, 10);
        verticalLayout_3->setStretch(5, 1);

        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        RunButton = new QPushButton(tab_2);
        RunButton->setObjectName(QString::fromUtf8("RunButton"));

        verticalLayout_2->addWidget(RunButton);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label);

        ImageFileNameEdit = new QLineEdit(groupBox);
        ImageFileNameEdit->setObjectName(QString::fromUtf8("ImageFileNameEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, ImageFileNameEdit);

        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_20);

        universalTimeEdit = new QLineEdit(groupBox);
        universalTimeEdit->setObjectName(QString::fromUtf8("universalTimeEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, universalTimeEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_2);

        XEdit = new QLineEdit(groupBox);
        XEdit->setObjectName(QString::fromUtf8("XEdit"));

        formLayout->setWidget(6, QFormLayout::FieldRole, XEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_3);

        YEdit = new QLineEdit(groupBox);
        YEdit->setObjectName(QString::fromUtf8("YEdit"));

        formLayout->setWidget(7, QFormLayout::FieldRole, YEdit);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(8, QFormLayout::SpanningRole, pushButton);

        EffectsLayerButton = new QRadioButton(groupBox);
        EffectsLayerButton->setObjectName(QString::fromUtf8("EffectsLayerButton"));

        formLayout->setWidget(0, QFormLayout::LabelRole, EffectsLayerButton);

        MidLayerButton = new QRadioButton(groupBox);
        MidLayerButton->setObjectName(QString::fromUtf8("MidLayerButton"));

        formLayout->setWidget(1, QFormLayout::LabelRole, MidLayerButton);

        LeftLayerButton = new QRadioButton(groupBox);
        LeftLayerButton->setObjectName(QString::fromUtf8("LeftLayerButton"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LeftLayerButton);

        RightLayerButton = new QRadioButton(groupBox);
        RightLayerButton->setObjectName(QString::fromUtf8("RightLayerButton"));

        formLayout->setWidget(1, QFormLayout::FieldRole, RightLayerButton);

        BGLayerButton = new QRadioButton(groupBox);
        BGLayerButton->setObjectName(QString::fromUtf8("BGLayerButton"));

        formLayout->setWidget(2, QFormLayout::LabelRole, BGLayerButton);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        DialogXEdit = new QLineEdit(groupBox_3);
        DialogXEdit->setObjectName(QString::fromUtf8("DialogXEdit"));

        gridLayout_2->addWidget(DialogXEdit, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        MarginLeftEdit = new QLineEdit(groupBox_3);
        MarginLeftEdit->setObjectName(QString::fromUtf8("MarginLeftEdit"));

        gridLayout_2->addWidget(MarginLeftEdit, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        DialogYEdit = new QLineEdit(groupBox_3);
        DialogYEdit->setObjectName(QString::fromUtf8("DialogYEdit"));

        gridLayout_2->addWidget(DialogYEdit, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 2, 1, 1);

        MarginTopEdit = new QLineEdit(groupBox_3);
        MarginTopEdit->setObjectName(QString::fromUtf8("MarginTopEdit"));

        gridLayout_2->addWidget(MarginTopEdit, 1, 3, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        DialogWidthEdit = new QLineEdit(groupBox_3);
        DialogWidthEdit->setObjectName(QString::fromUtf8("DialogWidthEdit"));

        gridLayout_2->addWidget(DialogWidthEdit, 2, 1, 1, 1);

        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 2, 2, 1, 1);

        TextWidthEdit = new QLineEdit(groupBox_3);
        TextWidthEdit->setObjectName(QString::fromUtf8("TextWidthEdit"));

        gridLayout_2->addWidget(TextWidthEdit, 2, 3, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        DialogHeightEdit = new QLineEdit(groupBox_3);
        DialogHeightEdit->setObjectName(QString::fromUtf8("DialogHeightEdit"));

        gridLayout_2->addWidget(DialogHeightEdit, 3, 1, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 3, 2, 1, 1);

        TextHeightEdit = new QLineEdit(groupBox_3);
        TextHeightEdit->setObjectName(QString::fromUtf8("TextHeightEdit"));

        gridLayout_2->addWidget(TextHeightEdit, 3, 3, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 4, 0, 1, 1);

        FontEdit = new QLineEdit(groupBox_3);
        FontEdit->setObjectName(QString::fromUtf8("FontEdit"));

        gridLayout_2->addWidget(FontEdit, 4, 1, 1, 1);

        SetTextColorButton = new QPushButton(groupBox_3);
        SetTextColorButton->setObjectName(QString::fromUtf8("SetTextColorButton"));

        gridLayout_2->addWidget(SetTextColorButton, 6, 0, 1, 4);


        gridLayout_4->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        RoleNameEdit = new QLineEdit(groupBox_5);
        RoleNameEdit->setObjectName(QString::fromUtf8("RoleNameEdit"));

        verticalLayout->addWidget(RoleNameEdit);

        ShowRoleNameButton = new QPushButton(groupBox_5);
        ShowRoleNameButton->setObjectName(QString::fromUtf8("ShowRoleNameButton"));

        verticalLayout->addWidget(ShowRoleNameButton);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout->addWidget(label_18);

        DelayEdit = new QLineEdit(groupBox_5);
        DelayEdit->setObjectName(QString::fromUtf8("DelayEdit"));

        verticalLayout->addWidget(DelayEdit);

        TextEdit = new QTextEdit(groupBox_5);
        TextEdit->setObjectName(QString::fromUtf8("TextEdit"));

        verticalLayout->addWidget(TextEdit);

        ShowTextButton = new QPushButton(groupBox_5);
        ShowTextButton->setObjectName(QString::fromUtf8("ShowTextButton"));

        verticalLayout->addWidget(ShowTextButton);

        ClearTextButton = new QPushButton(groupBox_5);
        ClearTextButton->setObjectName(QString::fromUtf8("ClearTextButton"));

        verticalLayout->addWidget(ClearTextButton);


        gridLayout_4->addWidget(groupBox_5, 0, 1, 3, 1);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 0, 0, 1, 1);

        RoleNameXEdit = new QLineEdit(groupBox_4);
        RoleNameXEdit->setObjectName(QString::fromUtf8("RoleNameXEdit"));

        gridLayout->addWidget(RoleNameXEdit, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 1, 0, 1, 1);

        RoleNameYEdit = new QLineEdit(groupBox_4);
        RoleNameYEdit->setObjectName(QString::fromUtf8("RoleNameYEdit"));

        gridLayout->addWidget(RoleNameYEdit, 1, 1, 1, 1);

        SetRoleNameColorButton = new QPushButton(groupBox_4);
        SetRoleNameColorButton->setObjectName(QString::fromUtf8("SetRoleNameColorButton"));

        gridLayout->addWidget(SetRoleNameColorButton, 3, 0, 1, 5);

        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout->addWidget(label_16, 0, 2, 1, 1);

        RoleNameFontEdit = new QLineEdit(groupBox_4);
        RoleNameFontEdit->setObjectName(QString::fromUtf8("RoleNameFontEdit"));

        gridLayout->addWidget(RoleNameFontEdit, 2, 1, 1, 1);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 2, 0, 1, 1);

        RoleNameWidthEdit = new QLineEdit(groupBox_4);
        RoleNameWidthEdit->setObjectName(QString::fromUtf8("RoleNameWidthEdit"));

        gridLayout->addWidget(RoleNameWidthEdit, 0, 3, 1, 1);

        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 1, 2, 1, 1);

        RoleNameHeightEdit = new QLineEdit(groupBox_4);
        RoleNameHeightEdit->setObjectName(QString::fromUtf8("RoleNameHeightEdit"));

        gridLayout->addWidget(RoleNameHeightEdit, 1, 3, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 1, 0, 1, 1);

        SetDialogButton = new QPushButton(groupBox_2);
        SetDialogButton->setObjectName(QString::fromUtf8("SetDialogButton"));

        gridLayout_4->addWidget(SetDialogButton, 2, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        tabWidget->addTab(tab, QString());

        gridLayout_3->addWidget(tabWidget, 1, 0, 1, 1);

        ScriptEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScriptEditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 930, 23));
        ScriptEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScriptEditorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ScriptEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScriptEditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ScriptEditorClass->setStatusBar(statusBar);

        retranslateUi(ScriptEditorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ScriptEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScriptEditorClass)
    {
        ScriptEditorClass->setWindowTitle(QApplication::translate("ScriptEditorClass", "ScriptEditor", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("ScriptEditorClass", "\350\204\232\346\234\254\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("ScriptEditorClass", "LUA\344\273\243\347\240\201\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        ClearButton->setText(QApplication::translate("ScriptEditorClass", "\346\270\205\347\251\272\345\267\246\350\276\271", 0, QApplication::UnicodeUTF8));
        ParseButton->setText(QApplication::translate("ScriptEditorClass", "\350\275\254\346\215\242", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("ScriptEditorClass", "\345\210\235\345\247\213\345\214\226\346\256\265", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("ScriptEditorClass", "LUA\346\256\265", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("ScriptEditorClass", "\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        RunButton->setText(QApplication::translate("ScriptEditorClass", "\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ScriptEditorClass", "\350\204\232\346\234\254\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ScriptEditorClass", "\345\233\276\347\211\207", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ScriptEditorClass", "\346\226\207\344\273\266\345\220\215:", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("ScriptEditorClass", "\346\270\220\345\217\230\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ScriptEditorClass", "X\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ScriptEditorClass", "Y\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ScriptEditorClass", "\346\230\276\347\244\272\345\233\276\347\211\207", 0, QApplication::UnicodeUTF8));
        EffectsLayerButton->setText(QApplication::translate("ScriptEditorClass", "\346\225\210\346\236\234\345\261\202", 0, QApplication::UnicodeUTF8));
        MidLayerButton->setText(QApplication::translate("ScriptEditorClass", "\344\270\255\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        LeftLayerButton->setText(QApplication::translate("ScriptEditorClass", "\345\267\246\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        RightLayerButton->setText(QApplication::translate("ScriptEditorClass", "\345\217\263\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        BGLayerButton->setText(QApplication::translate("ScriptEditorClass", "\350\203\214\346\231\257\345\261\202", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ScriptEditorClass", "\345\257\271\350\257\235\346\241\206", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ScriptEditorClass", "\345\257\271\350\257\235\346\241\206\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ScriptEditorClass", "X\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ScriptEditorClass", "\346\226\207\346\234\254\345\267\246\350\276\271\350\267\235:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ScriptEditorClass", "Y\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ScriptEditorClass", "\346\226\207\346\234\254\351\241\266\350\276\271\350\267\235:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ScriptEditorClass", "\345\256\275\345\272\246:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ScriptEditorClass", "\346\226\207\346\234\254\345\256\275\345\272\246:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ScriptEditorClass", "\351\253\230\345\272\246:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("ScriptEditorClass", "\346\226\207\346\234\254\351\253\230\345\272\246:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ScriptEditorClass", "\345\255\227\344\275\223:", 0, QApplication::UnicodeUTF8));
        SetTextColorButton->setText(QApplication::translate("ScriptEditorClass", "\350\256\276\347\275\256\346\226\207\345\255\227\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("ScriptEditorClass", "\346\266\210\346\201\257\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        ShowRoleNameButton->setText(QApplication::translate("ScriptEditorClass", "\346\230\276\347\244\272\350\247\222\350\211\262\345\220\215", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("ScriptEditorClass", "\345\273\266\346\227\266(\347\247\222):", 0, QApplication::UnicodeUTF8));
        DelayEdit->setText(QApplication::translate("ScriptEditorClass", "0.0", 0, QApplication::UnicodeUTF8));
        ShowTextButton->setText(QApplication::translate("ScriptEditorClass", "\346\230\276\347\244\272\346\226\207\345\255\227", 0, QApplication::UnicodeUTF8));
        ClearTextButton->setText(QApplication::translate("ScriptEditorClass", "\346\270\205\347\251\272", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ScriptEditorClass", "\350\247\222\350\211\262\345\220\215\347\247\260\346\241\206\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("ScriptEditorClass", "X\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("ScriptEditorClass", "Y\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        SetRoleNameColorButton->setText(QApplication::translate("ScriptEditorClass", "\350\256\276\347\275\256\350\247\222\350\211\262\345\220\215\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("ScriptEditorClass", "\345\256\275\345\272\246:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ScriptEditorClass", "\345\255\227\344\275\223:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("ScriptEditorClass", "\351\253\230\345\272\246:", 0, QApplication::UnicodeUTF8));
        SetDialogButton->setText(QApplication::translate("ScriptEditorClass", "\350\256\276\347\275\256\345\257\271\350\257\235\346\241\206", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ScriptEditorClass", "UI\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScriptEditorClass: public Ui_ScriptEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPTEDITOR_H

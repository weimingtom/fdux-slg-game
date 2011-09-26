/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Mar 25 13:34:50 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <../scr/framework/renderwindow.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *AddEntity_action;
    QAction *RemovEntity_action;
    QAction *Open_action;
    QAction *Save_action;
    QAction *LoadTerrain_action;
    QAction *NewTerrain_action;
    QAction *PM_POINTS_action;
    QAction *PM_WIREFRAME_action;
    QAction *PM_SOLID_action;
    QAction *NewObjectGroup_action;
    QAction *RemoveObjectGroup_action;
    QAction *RemovObject_action;
    QAction *Move_action;
    QAction *Rotate_action;
    QAction *Scale_action;
    QAction *MoveLock_action;
    QAction *ScaleLock_action;
    QAction *saveMap;
    QAction *loadMap;
    QAction *editMap;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_8;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    IIRenderWindow *graphicsView;
    QTextEdit *textEdit;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_15;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *mapName;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_12;
    QComboBox *team1Relation;
    QLineEdit *team1Faction;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_13;
    QComboBox *team2Relation;
    QLineEdit *team2Faction;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_14;
    QComboBox *team3Relation;
    QLineEdit *team3Faction;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_15;
    QComboBox *team4Relation;
    QLineEdit *team4Faction;
    QLabel *label_9;
    QLineEdit *mapScript;
    QLabel *label_10;
    QTextEdit *mapInfo;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *modBox;
    QPushButton *addMod;
    QLabel *label_3;
    QComboBox *langBox;
    QPushButton *addLang;
    QTabWidget *dataTab;
    QWidget *soldierTab;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *addSoldier;
    QPushButton *delSoldier;
    QTableView *soldierTableView;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addHorse;
    QPushButton *delHorse;
    QTableView *horseTableView;
    QWidget *weaponTab;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *addPWeapon;
    QPushButton *delPWeapon;
    QTableView *pweaponTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addSWeapon;
    QPushButton *delSWeapon;
    QTableView *sweaponTableView;
    QWidget *armorTab;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *addArmor;
    QPushButton *delArmor;
    QTableView *armorTableView;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *addShield;
    QPushButton *delShield;
    QTableView *shieldTableView;
    QWidget *skillTab;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *addEffect;
    QPushButton *delEffect;
    QTableView *effectTableView;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *addSkill;
    QPushButton *delSkill;
    QTableView *skillTableView;
    QWidget *squadTab;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_12;
    QListView *squadListView;
    QPushButton *addSquad;
    QPushButton *delSquad;
    QTableView *squadTableView;
    QVBoxLayout *verticalLayout_13;
    QTableView *squadEquipTableView;
    QTableView *squadSkillTableView;
    QPushButton *addSquadSkill;
    QPushButton *delSquadSkill;
    QWidget *stringTab;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addString;
    QPushButton *delString;
    QTableView *stringTableView;
    QWidget *tab_3;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuDix;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QToolBar *toolBar;
    QTreeView *treeView_2;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox;
    QLabel *label;
    QListWidget *listWidget;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QToolBar *toolBar5;
    QTreeView *treeView;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QDockWidget *dockWidget_5;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_16;
    QGridLayout *gridLayout;
    QPushButton *addArea;
    QPushButton *delArea;
    QPushButton *addCoord;
    QPushButton *delCoord;
    QPushButton *cancelArea;
    QListView *areaListView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1245, 701);
        AddEntity_action = new QAction(MainWindow);
        AddEntity_action->setObjectName(QString::fromUtf8("AddEntity_action"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/WarChess/Resources/edit_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddEntity_action->setIcon(icon);
        RemovEntity_action = new QAction(MainWindow);
        RemovEntity_action->setObjectName(QString::fromUtf8("RemovEntity_action"));
        RemovEntity_action->setCheckable(false);
        RemovEntity_action->setChecked(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/WarChess/Resources/edit_remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        RemovEntity_action->setIcon(icon1);
        Open_action = new QAction(MainWindow);
        Open_action->setObjectName(QString::fromUtf8("Open_action"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/WarChess/Resources/fileopen (2).png"), QSize(), QIcon::Normal, QIcon::Off);
        Open_action->setIcon(icon2);
        Save_action = new QAction(MainWindow);
        Save_action->setObjectName(QString::fromUtf8("Save_action"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/WarChess/Resources/linguist-filesave (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        Save_action->setIcon(icon3);
        LoadTerrain_action = new QAction(MainWindow);
        LoadTerrain_action->setObjectName(QString::fromUtf8("LoadTerrain_action"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/WarChess/Resources/textanchor.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoadTerrain_action->setIcon(icon4);
        NewTerrain_action = new QAction(MainWindow);
        NewTerrain_action->setObjectName(QString::fromUtf8("NewTerrain_action"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/WarChess/Resources/desktop-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewTerrain_action->setIcon(icon5);
        PM_POINTS_action = new QAction(MainWindow);
        PM_POINTS_action->setObjectName(QString::fromUtf8("PM_POINTS_action"));
        PM_POINTS_action->setCheckable(false);
        PM_WIREFRAME_action = new QAction(MainWindow);
        PM_WIREFRAME_action->setObjectName(QString::fromUtf8("PM_WIREFRAME_action"));
        PM_WIREFRAME_action->setCheckable(false);
        PM_SOLID_action = new QAction(MainWindow);
        PM_SOLID_action->setObjectName(QString::fromUtf8("PM_SOLID_action"));
        PM_SOLID_action->setCheckable(false);
        PM_SOLID_action->setChecked(false);
        NewObjectGroup_action = new QAction(MainWindow);
        NewObjectGroup_action->setObjectName(QString::fromUtf8("NewObjectGroup_action"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/WarChess/Resources/addGroup.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewObjectGroup_action->setIcon(icon6);
        RemoveObjectGroup_action = new QAction(MainWindow);
        RemoveObjectGroup_action->setObjectName(QString::fromUtf8("RemoveObjectGroup_action"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/WarChess/Resources/removeGroup.png"), QSize(), QIcon::Normal, QIcon::Off);
        RemoveObjectGroup_action->setIcon(icon7);
        RemovObject_action = new QAction(MainWindow);
        RemovObject_action->setObjectName(QString::fromUtf8("RemovObject_action"));
        RemovObject_action->setCheckable(false);
        RemovObject_action->setChecked(false);
        RemovObject_action->setIcon(icon1);
        Move_action = new QAction(MainWindow);
        Move_action->setObjectName(QString::fromUtf8("Move_action"));
        Move_action->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/WarChess/Resources/sizeall.png"), QSize(), QIcon::Normal, QIcon::Off);
        Move_action->setIcon(icon8);
        Rotate_action = new QAction(MainWindow);
        Rotate_action->setObjectName(QString::fromUtf8("Rotate_action"));
        Rotate_action->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/WarChess/Resources/refresh-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        Rotate_action->setIcon(icon9);
        Scale_action = new QAction(MainWindow);
        Scale_action->setObjectName(QString::fromUtf8("Scale_action"));
        Scale_action->setCheckable(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/WarChess/Resources/adjustsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        Scale_action->setIcon(icon10);
        MoveLock_action = new QAction(MainWindow);
        MoveLock_action->setObjectName(QString::fromUtf8("MoveLock_action"));
        MoveLock_action->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/WarChess/Resources/sizeall-lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        MoveLock_action->setIcon(icon11);
        ScaleLock_action = new QAction(MainWindow);
        ScaleLock_action->setObjectName(QString::fromUtf8("ScaleLock_action"));
        ScaleLock_action->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/WarChess/Resources/adjustsize-lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        ScaleLock_action->setIcon(icon12);
        saveMap = new QAction(MainWindow);
        saveMap->setObjectName(QString::fromUtf8("saveMap"));
        loadMap = new QAction(MainWindow);
        loadMap->setObjectName(QString::fromUtf8("loadMap"));
        editMap = new QAction(MainWindow);
        editMap->setObjectName(QString::fromUtf8("editMap"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_8 = new QVBoxLayout(centralWidget);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(2, 2, 2, 2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        graphicsView = new IIRenderWindow(tab);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(640, 480));

        verticalLayout_5->addWidget(graphicsView);

        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout_5->addWidget(textEdit);

        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_15 = new QVBoxLayout(tab_4);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        mapName = new QLineEdit(tab_4);
        mapName->setObjectName(QString::fromUtf8("mapName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, mapName);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        team1Relation = new QComboBox(tab_4);
        team1Relation->setObjectName(QString::fromUtf8("team1Relation"));
        team1Relation->setEnabled(false);

        horizontalLayout_12->addWidget(team1Relation);

        team1Faction = new QLineEdit(tab_4);
        team1Faction->setObjectName(QString::fromUtf8("team1Faction"));
        team1Faction->setEnabled(false);

        horizontalLayout_12->addWidget(team1Faction);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_12);

        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        team2Relation = new QComboBox(tab_4);
        team2Relation->setObjectName(QString::fromUtf8("team2Relation"));

        horizontalLayout_13->addWidget(team2Relation);

        team2Faction = new QLineEdit(tab_4);
        team2Faction->setObjectName(QString::fromUtf8("team2Faction"));

        horizontalLayout_13->addWidget(team2Faction);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_13);

        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        team3Relation = new QComboBox(tab_4);
        team3Relation->setObjectName(QString::fromUtf8("team3Relation"));

        horizontalLayout_14->addWidget(team3Relation);

        team3Faction = new QLineEdit(tab_4);
        team3Faction->setObjectName(QString::fromUtf8("team3Faction"));

        horizontalLayout_14->addWidget(team3Faction);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_14);

        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_8);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        team4Relation = new QComboBox(tab_4);
        team4Relation->setObjectName(QString::fromUtf8("team4Relation"));

        horizontalLayout_15->addWidget(team4Relation);

        team4Faction = new QLineEdit(tab_4);
        team4Faction->setObjectName(QString::fromUtf8("team4Faction"));

        horizontalLayout_15->addWidget(team4Faction);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_15);

        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_9);

        mapScript = new QLineEdit(tab_4);
        mapScript->setObjectName(QString::fromUtf8("mapScript"));

        formLayout->setWidget(5, QFormLayout::FieldRole, mapScript);


        verticalLayout_15->addLayout(formLayout);

        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_15->addWidget(label_10);

        mapInfo = new QTextEdit(tab_4);
        mapInfo->setObjectName(QString::fromUtf8("mapInfo"));

        verticalLayout_15->addWidget(mapInfo);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        modBox = new QComboBox(tab_2);
        modBox->setObjectName(QString::fromUtf8("modBox"));

        horizontalLayout_3->addWidget(modBox);

        addMod = new QPushButton(tab_2);
        addMod->setObjectName(QString::fromUtf8("addMod"));

        horizontalLayout_3->addWidget(addMod);

        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        langBox = new QComboBox(tab_2);
        langBox->setObjectName(QString::fromUtf8("langBox"));

        horizontalLayout_3->addWidget(langBox);

        addLang = new QPushButton(tab_2);
        addLang->setObjectName(QString::fromUtf8("addLang"));

        horizontalLayout_3->addWidget(addLang);


        verticalLayout_6->addLayout(horizontalLayout_3);

        dataTab = new QTabWidget(tab_2);
        dataTab->setObjectName(QString::fromUtf8("dataTab"));
        soldierTab = new QWidget();
        soldierTab->setObjectName(QString::fromUtf8("soldierTab"));
        verticalLayout_7 = new QVBoxLayout(soldierTab);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        addSoldier = new QPushButton(soldierTab);
        addSoldier->setObjectName(QString::fromUtf8("addSoldier"));

        horizontalLayout_4->addWidget(addSoldier);

        delSoldier = new QPushButton(soldierTab);
        delSoldier->setObjectName(QString::fromUtf8("delSoldier"));

        horizontalLayout_4->addWidget(delSoldier);


        verticalLayout_7->addLayout(horizontalLayout_4);

        soldierTableView = new QTableView(soldierTab);
        soldierTableView->setObjectName(QString::fromUtf8("soldierTableView"));
        soldierTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        soldierTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_7->addWidget(soldierTableView);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        addHorse = new QPushButton(soldierTab);
        addHorse->setObjectName(QString::fromUtf8("addHorse"));

        horizontalLayout_6->addWidget(addHorse);

        delHorse = new QPushButton(soldierTab);
        delHorse->setObjectName(QString::fromUtf8("delHorse"));

        horizontalLayout_6->addWidget(delHorse);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horseTableView = new QTableView(soldierTab);
        horseTableView->setObjectName(QString::fromUtf8("horseTableView"));

        verticalLayout_7->addWidget(horseTableView);

        dataTab->addTab(soldierTab, QString());
        weaponTab = new QWidget();
        weaponTab->setObjectName(QString::fromUtf8("weaponTab"));
        verticalLayout_9 = new QVBoxLayout(weaponTab);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addPWeapon = new QPushButton(weaponTab);
        addPWeapon->setObjectName(QString::fromUtf8("addPWeapon"));

        horizontalLayout->addWidget(addPWeapon);

        delPWeapon = new QPushButton(weaponTab);
        delPWeapon->setObjectName(QString::fromUtf8("delPWeapon"));

        horizontalLayout->addWidget(delPWeapon);


        verticalLayout_9->addLayout(horizontalLayout);

        pweaponTableView = new QTableView(weaponTab);
        pweaponTableView->setObjectName(QString::fromUtf8("pweaponTableView"));

        verticalLayout_9->addWidget(pweaponTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addSWeapon = new QPushButton(weaponTab);
        addSWeapon->setObjectName(QString::fromUtf8("addSWeapon"));

        horizontalLayout_2->addWidget(addSWeapon);

        delSWeapon = new QPushButton(weaponTab);
        delSWeapon->setObjectName(QString::fromUtf8("delSWeapon"));

        horizontalLayout_2->addWidget(delSWeapon);


        verticalLayout_9->addLayout(horizontalLayout_2);

        sweaponTableView = new QTableView(weaponTab);
        sweaponTableView->setObjectName(QString::fromUtf8("sweaponTableView"));

        verticalLayout_9->addWidget(sweaponTableView);

        dataTab->addTab(weaponTab, QString());
        armorTab = new QWidget();
        armorTab->setObjectName(QString::fromUtf8("armorTab"));
        verticalLayout_10 = new QVBoxLayout(armorTab);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        addArmor = new QPushButton(armorTab);
        addArmor->setObjectName(QString::fromUtf8("addArmor"));

        horizontalLayout_7->addWidget(addArmor);

        delArmor = new QPushButton(armorTab);
        delArmor->setObjectName(QString::fromUtf8("delArmor"));

        horizontalLayout_7->addWidget(delArmor);


        verticalLayout_10->addLayout(horizontalLayout_7);

        armorTableView = new QTableView(armorTab);
        armorTableView->setObjectName(QString::fromUtf8("armorTableView"));

        verticalLayout_10->addWidget(armorTableView);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        addShield = new QPushButton(armorTab);
        addShield->setObjectName(QString::fromUtf8("addShield"));

        horizontalLayout_8->addWidget(addShield);

        delShield = new QPushButton(armorTab);
        delShield->setObjectName(QString::fromUtf8("delShield"));

        horizontalLayout_8->addWidget(delShield);


        verticalLayout_10->addLayout(horizontalLayout_8);

        shieldTableView = new QTableView(armorTab);
        shieldTableView->setObjectName(QString::fromUtf8("shieldTableView"));

        verticalLayout_10->addWidget(shieldTableView);

        dataTab->addTab(armorTab, QString());
        skillTab = new QWidget();
        skillTab->setObjectName(QString::fromUtf8("skillTab"));
        verticalLayout_11 = new QVBoxLayout(skillTab);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        addEffect = new QPushButton(skillTab);
        addEffect->setObjectName(QString::fromUtf8("addEffect"));

        horizontalLayout_10->addWidget(addEffect);

        delEffect = new QPushButton(skillTab);
        delEffect->setObjectName(QString::fromUtf8("delEffect"));

        horizontalLayout_10->addWidget(delEffect);


        verticalLayout_11->addLayout(horizontalLayout_10);

        effectTableView = new QTableView(skillTab);
        effectTableView->setObjectName(QString::fromUtf8("effectTableView"));

        verticalLayout_11->addWidget(effectTableView);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        addSkill = new QPushButton(skillTab);
        addSkill->setObjectName(QString::fromUtf8("addSkill"));

        horizontalLayout_11->addWidget(addSkill);

        delSkill = new QPushButton(skillTab);
        delSkill->setObjectName(QString::fromUtf8("delSkill"));

        horizontalLayout_11->addWidget(delSkill);


        verticalLayout_11->addLayout(horizontalLayout_11);

        skillTableView = new QTableView(skillTab);
        skillTableView->setObjectName(QString::fromUtf8("skillTableView"));

        verticalLayout_11->addWidget(skillTableView);

        dataTab->addTab(skillTab, QString());
        squadTab = new QWidget();
        squadTab->setObjectName(QString::fromUtf8("squadTab"));
        horizontalLayout_9 = new QHBoxLayout(squadTab);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        squadListView = new QListView(squadTab);
        squadListView->setObjectName(QString::fromUtf8("squadListView"));

        verticalLayout_12->addWidget(squadListView);

        addSquad = new QPushButton(squadTab);
        addSquad->setObjectName(QString::fromUtf8("addSquad"));

        verticalLayout_12->addWidget(addSquad);

        delSquad = new QPushButton(squadTab);
        delSquad->setObjectName(QString::fromUtf8("delSquad"));

        verticalLayout_12->addWidget(delSquad);

        squadTableView = new QTableView(squadTab);
        squadTableView->setObjectName(QString::fromUtf8("squadTableView"));

        verticalLayout_12->addWidget(squadTableView);


        horizontalLayout_9->addLayout(verticalLayout_12);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        squadEquipTableView = new QTableView(squadTab);
        squadEquipTableView->setObjectName(QString::fromUtf8("squadEquipTableView"));

        verticalLayout_13->addWidget(squadEquipTableView);

        squadSkillTableView = new QTableView(squadTab);
        squadSkillTableView->setObjectName(QString::fromUtf8("squadSkillTableView"));

        verticalLayout_13->addWidget(squadSkillTableView);

        addSquadSkill = new QPushButton(squadTab);
        addSquadSkill->setObjectName(QString::fromUtf8("addSquadSkill"));

        verticalLayout_13->addWidget(addSquadSkill);

        delSquadSkill = new QPushButton(squadTab);
        delSquadSkill->setObjectName(QString::fromUtf8("delSquadSkill"));

        verticalLayout_13->addWidget(delSquadSkill);


        horizontalLayout_9->addLayout(verticalLayout_13);

        dataTab->addTab(squadTab, QString());
        stringTab = new QWidget();
        stringTab->setObjectName(QString::fromUtf8("stringTab"));
        verticalLayout_14 = new QVBoxLayout(stringTab);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        addString = new QPushButton(stringTab);
        addString->setObjectName(QString::fromUtf8("addString"));

        horizontalLayout_5->addWidget(addString);

        delString = new QPushButton(stringTab);
        delString->setObjectName(QString::fromUtf8("delString"));

        horizontalLayout_5->addWidget(delString);


        verticalLayout_14->addLayout(horizontalLayout_5);

        stringTableView = new QTableView(stringTab);
        stringTableView->setObjectName(QString::fromUtf8("stringTableView"));

        verticalLayout_14->addWidget(stringTableView);

        dataTab->addTab(stringTab, QString());

        verticalLayout_6->addWidget(dataTab);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());

        verticalLayout_8->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1245, 17));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuDix = new QMenu(menuBar);
        menuDix->setObjectName(QString::fromUtf8("menuDix"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menu_2);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFloating(false);
        dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        toolBar = new QToolBar(dockWidgetContents);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout_3->addWidget(toolBar);

        treeView_2 = new QTreeView(dockWidgetContents);
        treeView_2->setObjectName(QString::fromUtf8("treeView_2"));

        verticalLayout_3->addWidget(treeView_2);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        dockWidget_3 = new QDockWidget(MainWindow);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidget_3->setMinimumSize(QSize(328, 200));
        dockWidget_3->setMaximumSize(QSize(524287, 200));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 9, 0, 0);
        checkBox = new QCheckBox(dockWidgetContents_3);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_2->addWidget(checkBox);

        label = new QLabel(dockWidgetContents_3);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        listWidget = new QListWidget(dockWidgetContents_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setEnabled(false);

        verticalLayout_2->addWidget(listWidget);

        dockWidget_3->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBar5 = new QToolBar(dockWidgetContents_2);
        toolBar5->setObjectName(QString::fromUtf8("toolBar5"));
        toolBar5->setToolButtonStyle(Qt::ToolButtonIconOnly);

        verticalLayout->addWidget(toolBar5);

        treeView = new QTreeView(dockWidgetContents_2);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setDragEnabled(false);
        treeView->setDragDropMode(QAbstractItemView::NoDragDrop);
        treeView->setDefaultDropAction(Qt::IgnoreAction);

        verticalLayout->addWidget(treeView);

        dockWidget_2->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_2);
        dockWidget_4 = new QDockWidget(MainWindow);
        dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 9, 0, 0);
        tableWidget = new QTableWidget(dockWidgetContents_4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(tableWidget);

        dockWidget_4->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_4);
        dockWidget_5 = new QDockWidget(MainWindow);
        dockWidget_5->setObjectName(QString::fromUtf8("dockWidget_5"));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        verticalLayout_16 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        addArea = new QPushButton(dockWidgetContents_5);
        addArea->setObjectName(QString::fromUtf8("addArea"));

        gridLayout->addWidget(addArea, 0, 0, 1, 1);

        delArea = new QPushButton(dockWidgetContents_5);
        delArea->setObjectName(QString::fromUtf8("delArea"));

        gridLayout->addWidget(delArea, 0, 1, 1, 1);

        addCoord = new QPushButton(dockWidgetContents_5);
        addCoord->setObjectName(QString::fromUtf8("addCoord"));

        gridLayout->addWidget(addCoord, 2, 0, 1, 1);

        delCoord = new QPushButton(dockWidgetContents_5);
        delCoord->setObjectName(QString::fromUtf8("delCoord"));

        gridLayout->addWidget(delCoord, 2, 1, 1, 1);

        cancelArea = new QPushButton(dockWidgetContents_5);
        cancelArea->setObjectName(QString::fromUtf8("cancelArea"));

        gridLayout->addWidget(cancelArea, 0, 3, 1, 1);


        verticalLayout_16->addLayout(gridLayout);

        areaListView = new QListView(dockWidgetContents_5);
        areaListView->setObjectName(QString::fromUtf8("areaListView"));

        verticalLayout_16->addWidget(areaListView);

        dockWidget_5->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_5);

        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuDix->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(Open_action);
        menu->addAction(Save_action);
        menuDix->addAction(NewTerrain_action);
        menuDix->addAction(LoadTerrain_action);
        menu_2->addAction(menu_3->menuAction());
        menu_3->addAction(PM_POINTS_action);
        menu_3->addAction(PM_WIREFRAME_action);
        menu_3->addAction(PM_SOLID_action);
        menu_4->addAction(saveMap);
        menu_4->addAction(loadMap);
        mainToolBar->addAction(NewTerrain_action);
        mainToolBar->addAction(LoadTerrain_action);
        mainToolBar->addSeparator();
        mainToolBar->addAction(Move_action);
        mainToolBar->addAction(Rotate_action);
        mainToolBar->addAction(Scale_action);
        mainToolBar->addSeparator();
        mainToolBar->addAction(MoveLock_action);
        mainToolBar->addAction(ScaleLock_action);
        toolBar->addAction(NewObjectGroup_action);
        toolBar->addAction(RemoveObjectGroup_action);
        toolBar->addSeparator();
        toolBar->addAction(RemovObject_action);
        toolBar5->addAction(AddEntity_action);
        toolBar5->addAction(RemovEntity_action);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        dataTab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\345\234\272\346\231\257\347\274\226\350\276\221\345\231\250", 0, QApplication::UnicodeUTF8));
        AddEntity_action->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\256\236\344\275\223", 0, QApplication::UnicodeUTF8));
        RemovEntity_action->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\345\256\236\344\275\223", 0, QApplication::UnicodeUTF8));
        Open_action->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\345\256\236\344\275\223\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        Save_action->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\256\236\344\275\223\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        LoadTerrain_action->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\345\234\260\345\275\242", 0, QApplication::UnicodeUTF8));
        NewTerrain_action->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\345\234\260\345\275\242", 0, QApplication::UnicodeUTF8));
        PM_POINTS_action->setText(QApplication::translate("MainWindow", "\347\202\271", 0, QApplication::UnicodeUTF8));
        PM_WIREFRAME_action->setText(QApplication::translate("MainWindow", "\347\275\221\346\240\274", 0, QApplication::UnicodeUTF8));
        PM_SOLID_action->setText(QApplication::translate("MainWindow", "\351\235\242", 0, QApplication::UnicodeUTF8));
        NewObjectGroup_action->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\347\273\204", 0, QApplication::UnicodeUTF8));
        RemoveObjectGroup_action->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\347\273\204", 0, QApplication::UnicodeUTF8));
        RemovObject_action->setText(QApplication::translate("MainWindow", "\347\247\273\351\231\244\345\256\236\344\275\223", 0, QApplication::UnicodeUTF8));
        Move_action->setText(QApplication::translate("MainWindow", "Move", 0, QApplication::UnicodeUTF8));
        Rotate_action->setText(QApplication::translate("MainWindow", "rotate", 0, QApplication::UnicodeUTF8));
        Scale_action->setText(QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8));
        MoveLock_action->setText(QApplication::translate("MainWindow", "moveLock", 0, QApplication::UnicodeUTF8));
        ScaleLock_action->setText(QApplication::translate("MainWindow", "scaleLock", 0, QApplication::UnicodeUTF8));
        saveMap->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230 ", 0, QApplication::UnicodeUTF8));
        loadMap->setText(QApplication::translate("MainWindow", "\350\275\275\345\205\245", 0, QApplication::UnicodeUTF8));
        editMap->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\347\274\226\350\276\221\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\351\230\237\344\274\2151", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "\351\230\237\344\274\2152", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "\351\230\237\344\274\2153", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "\351\230\237\344\274\2154", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\350\204\232\346\234\254", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "\345\234\260\345\233\276\346\217\217\350\277\260", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\345\234\260\345\233\276\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\346\250\241\347\273\204\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        addMod->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\250\241\347\273\204", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\350\257\255\350\250\200\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        addLang->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\350\257\255\350\250\200", 0, QApplication::UnicodeUTF8));
        addSoldier->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\345\205\265\346\272\220", 0, QApplication::UnicodeUTF8));
        delSoldier->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\205\265\345\221\230", 0, QApplication::UnicodeUTF8));
        addHorse->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\351\251\254\345\214\271", 0, QApplication::UnicodeUTF8));
        delHorse->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\251\254\345\214\271", 0, QApplication::UnicodeUTF8));
        dataTab->setTabText(dataTab->indexOf(soldierTab), QApplication::translate("MainWindow", "\345\205\265\346\272\220/\351\251\254\345\214\271", 0, QApplication::UnicodeUTF8));
        addPWeapon->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\344\270\273\346\255\246\345\231\250", 0, QApplication::UnicodeUTF8));
        delPWeapon->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\344\270\273\346\255\246\345\231\250", 0, QApplication::UnicodeUTF8));
        addSWeapon->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\346\254\241\346\255\246\345\231\250", 0, QApplication::UnicodeUTF8));
        delSWeapon->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\254\241\346\255\246\345\231\250", 0, QApplication::UnicodeUTF8));
        dataTab->setTabText(dataTab->indexOf(weaponTab), QApplication::translate("MainWindow", "\344\270\273\346\255\246\345\231\250/\346\254\241\346\255\246\345\231\250", 0, QApplication::UnicodeUTF8));
        addArmor->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\347\233\224\347\224\262", 0, QApplication::UnicodeUTF8));
        delArmor->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\347\233\224\347\224\262", 0, QApplication::UnicodeUTF8));
        addShield->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\347\233\276\347\211\214", 0, QApplication::UnicodeUTF8));
        delShield->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\347\233\276\347\211\214", 0, QApplication::UnicodeUTF8));
        dataTab->setTabText(dataTab->indexOf(armorTab), QApplication::translate("MainWindow", "\347\233\224\347\224\262/\347\233\276\347\211\214", 0, QApplication::UnicodeUTF8));
        addEffect->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\346\225\210\346\236\234", 0, QApplication::UnicodeUTF8));
        delEffect->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\225\210\346\236\234", 0, QApplication::UnicodeUTF8));
        addSkill->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\346\212\200\350\203\275", 0, QApplication::UnicodeUTF8));
        delSkill->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\212\200\350\203\275", 0, QApplication::UnicodeUTF8));
        dataTab->setTabText(dataTab->indexOf(skillTab), QApplication::translate("MainWindow", "\346\225\210\346\236\234/\346\212\200\350\203\275", 0, QApplication::UnicodeUTF8));
        addSquad->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\260\217\351\230\237", 0, QApplication::UnicodeUTF8));
        delSquad->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\260\217\351\230\237", 0, QApplication::UnicodeUTF8));
        addSquadSkill->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\346\212\200\350\203\275", 0, QApplication::UnicodeUTF8));
        delSquadSkill->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\212\200\350\203\275", 0, QApplication::UnicodeUTF8));
        dataTab->setTabText(dataTab->indexOf(squadTab), QApplication::translate("MainWindow", "\345\260\217\351\230\237", 0, QApplication::UnicodeUTF8));
        addString->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\345\255\227\347\254\246\344\270\262", 0, QApplication::UnicodeUTF8));
        delString->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\255\227\347\254\246\344\270\262", 0, QApplication::UnicodeUTF8));
        dataTab->setTabText(dataTab->indexOf(stringTab), QApplication::translate("MainWindow", "\345\255\227\347\254\246\344\270\262\350\241\250", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\346\225\260\346\215\256\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\346\210\230\346\226\227\346\250\241\346\213\237", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\345\256\236\344\275\223", 0, QApplication::UnicodeUTF8));
        menuDix->setTitle(QApplication::translate("MainWindow", "\345\234\260\345\275\242", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\221\204\345\203\217\346\234\272", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\234\260\345\233\276", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("MainWindow", "\345\234\272\346\231\257\345\257\271\350\261\241\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        dockWidget_3->setWindowTitle(QApplication::translate("MainWindow", "\345\234\260\345\275\242\345\267\245\345\205\267\347\256\261", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "\345\220\257\347\224\250\345\234\260\345\275\242\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\345\234\260\350\241\250:", 0, QApplication::UnicodeUTF8));
        dockWidget_2->setWindowTitle(QApplication::translate("MainWindow", "\345\256\236\344\275\223\346\200\273\346\261\207", 0, QApplication::UnicodeUTF8));
        toolBar5->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        dockWidget_4->setWindowTitle(QApplication::translate("MainWindow", "\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        dockWidget_5->setWindowTitle(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        addArea->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\214\272\345\237\237", 0, QApplication::UnicodeUTF8));
        delArea->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\214\272\345\237\237", 0, QApplication::UnicodeUTF8));
        addCoord->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\235\220\346\240\207", 0, QApplication::UnicodeUTF8));
        delCoord->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\235\220\346\240\207", 0, QApplication::UnicodeUTF8));
        cancelArea->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

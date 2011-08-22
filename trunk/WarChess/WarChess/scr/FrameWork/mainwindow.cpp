#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QFileDialog>

#include "IIRoot.h"
#include "entitydialog.h"
#include "entityitemdelegate.h"

#include <ticpp.h>
#include "conversion.h"
#include "ObjectData.h"
#include <Windows.h>

#include "Common.h"
#include "AreaManager.h"
#include "Area.h"
#include "RampManager.h"
#include "TerrainEditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rWindow=ui->graphicsView;
	mFpsLable=new QLabel(this);
	mCameraLable=new QLabel(this);
	ui->statusBar->addWidget(mFpsLable);
	ui->statusBar->addWidget(mCameraLable);
	rWindow->setMainWindow(this);
	rWindow->setInfoLable(mFpsLable,mCameraLable);

	 ui->team2Relation->addItem("none");
	 ui->team2Relation->addItem("alliance");
	 ui->team2Relation->addItem("enemy1");
	 ui->team2Relation->addItem("enemy2");
	 ui->team2Relation->addItem("enemy3");
	 ui->team3Relation->addItem("none");
	 ui->team3Relation->addItem("alliance");
	 ui->team3Relation->addItem("enemy1");
	 ui->team3Relation->addItem("enemy2");
	 ui->team3Relation->addItem("enemy3");
	 ui->team4Relation->addItem("none");
	 ui->team4Relation->addItem("alliance");
	 ui->team4Relation->addItem("enemy1");
	 ui->team4Relation->addItem("enemy2");
	 ui->team4Relation->addItem("enemy3");
}

MainWindow::~MainWindow()
{
	delete dataEditorControl;
	delete terrainControl;
	delete entityTreeControl;
	delete cameraControl;
	delete rWindow;
	delete ui;
}

void MainWindow::messageLogged (const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName)
 {
     ui->textEdit->append(message.c_str());
 }

void MainWindow::initValue()
{
	attributeControl=new AttributeControl(ui->tableWidget);
	terrainControl=new TerrainControl(ui);
	cameraControl=new CameraControl();
	objectControl=new ObjcetControl(ui->treeView_2,attributeControl);
	entityTreeControl=new EntityTreeControl(ui->treeView,objectControl);
	mAreaControl = new AreaControl(ui->areaListView);
	//数据编辑器控制
	dataEditorControl = new DataEditorControl(ui);

	objectControl->mMoveAction=ui->Move_action;
	objectControl->mRotateAction=ui->Rotate_action;
	objectControl->mScaleAction=ui->Scale_action;
	this->connect(ui->Move_action,SIGNAL(triggered(bool)),objectControl,SLOT(moveAction(bool)));
	this->connect(ui->Rotate_action,SIGNAL(triggered(bool)),objectControl,SLOT(rotateAction(bool)));
	this->connect(ui->Scale_action,SIGNAL(triggered(bool)),objectControl,SLOT(scaleAction(bool)));
	this->connect(ui->NewObjectGroup_action,SIGNAL(triggered(bool)),objectControl,SLOT(addObjectGroup()));
	this->connect(ui->RemoveObjectGroup_action,SIGNAL(triggered(bool)),objectControl,SLOT(removeObjectGroup()));
	this->connect(ui->RemovObject_action,SIGNAL(triggered(bool)),objectControl,SLOT(removeObject()));
	this->connect(ui->MoveLock_action,SIGNAL(triggered(bool)),objectControl,SLOT(moveLockAction(bool)));
	this->connect(ui->ScaleLock_action,SIGNAL(triggered(bool)),objectControl,SLOT(scaleLockAction(bool)));
	this->connect(rWindow,SIGNAL(mouseMove(QMouseEvent*)),objectControl,SLOT(mouseMove(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(mousePress(QMouseEvent*)),objectControl,SLOT(mousePress(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(mouseRelease(QMouseEvent*)),objectControl,SLOT(mouseRelease(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(cameraMove(float,float,float)),objectControl,SLOT(cameraMove(float,float,float)));

	this->connect(ui->AddEntity_action,SIGNAL(triggered(bool)),entityTreeControl,SLOT(addEntity()));
	this->connect(ui->RemovEntity_action,SIGNAL(triggered(bool)),entityTreeControl,SLOT(removeEntity()));
	this->connect(ui->treeView,SIGNAL(pressed(const QModelIndex&)),entityTreeControl,SLOT(selectEntity(const QModelIndex&)));
	this->connect(rWindow,SIGNAL(mouseMove(QMouseEvent*)),entityTreeControl,SLOT(mouseMove(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(mousePress(QMouseEvent*)),entityTreeControl,SLOT(mousePress(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(mouseRelease(QMouseEvent*)),entityTreeControl,SLOT(mouseRelease(QMouseEvent*)));

	this->connect(ui->LoadTerrain_action,SIGNAL(triggered(bool)),terrainControl,SLOT(Load_Terrain()));
	this->connect(ui->NewTerrain_action,SIGNAL(triggered(bool)),terrainControl,SLOT(New_Terrain()));
	
	this->connect(ui->checkBox,SIGNAL(stateChanged(int)),terrainControl,SLOT(stateChanged(int)));
	this->connect(ui->listWidget,SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),terrainControl,SLOT(currentItemChanged(QListWidgetItem*, QListWidgetItem*)));

	this->connect(rWindow,SIGNAL(mouseMove(QMouseEvent*)),terrainControl,SLOT(mouseMove(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(mousePress(QMouseEvent*)),terrainControl,SLOT(mousePress(QMouseEvent*)));
	this->connect(rWindow,SIGNAL(mouseRelease(QMouseEvent*)),terrainControl,SLOT(mouseRelease(QMouseEvent*)));

	this->connect(ui->PM_POINTS_action,SIGNAL(triggered(bool)),cameraControl,SLOT(PM_POINTS_action()));
	this->connect(ui->PM_WIREFRAME_action,SIGNAL(triggered(bool)),cameraControl,SLOT(PM_WIREFRAME_action()));	
	this->connect(ui->PM_SOLID_action,SIGNAL(triggered(bool)),cameraControl,SLOT(PM_SOLID_action()));

	this->connect(rWindow,SIGNAL(mousePress(QMouseEvent*)),mAreaControl,SLOT(mousePress(QMouseEvent*)));
	this->connect(ui->addArea,SIGNAL(clicked()),mAreaControl,SLOT(AddArea()) );
	this->connect(ui->delArea,SIGNAL(clicked()),mAreaControl,SLOT(DelArea()) );
	this->connect(ui->cancelArea,SIGNAL(clicked()),mAreaControl,SLOT(CancelArea()) );
	this->connect(ui->addCoord,SIGNAL(clicked()),mAreaControl,SLOT(AddCoord()) );
	this->connect(ui->delCoord,SIGNAL(clicked()),mAreaControl,SLOT(DelCoord()) );

	this->connect(ui->loadMap,SIGNAL(triggered(bool)),this,SLOT(LoadMap()));
	this->connect(ui->saveMap,SIGNAL(triggered(bool)),this,SLOT(SaveMap()));
}

void MainWindow::timerEvent(QTimerEvent * event)
{
    rWindow->timerEvent(event);
    IIRoot::getSingletonPtr()->mRoot->renderOneFrame();
}

IIRenderWindow* MainWindow::getGView()
 {
     return rWindow;
 }

QStatusBar* MainWindow::getBar()
{
    return ui->statusBar;
}

void MainWindow::LoadMap()
{
	bool dialogOK;
	QString dialogText = QInputDialog::getText(this,
										tr("请输入地图文件名"),
										tr("地图文件名:"),
										QLineEdit::Normal,
										QString(),
										&dialogOK);
	//QMessageBox::information(NULL,
	//						tr("debug"),
	//						text);

	if (!dialogOK || dialogText.isEmpty()) return;

	std::wstring mapPath16 = dialogText.toStdWString();
	std::string mapPath8;
	UnicodeToANSI(mapPath16, mapPath8);

	WIN32_FIND_DATA findFileData;
	memset(&findFileData,0,sizeof(findFileData));

	ticpp::Document doc;
	doc.Clear();
	HANDLE hFind = FindFirstFile(mapPath16.c_str(),&findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		doc.LoadFile(mapPath8.c_str(),TIXML_ENCODING_UTF8);
		FindClose(hFind);
	}
	if (doc.NoChildren()) return;

	ticpp::Element *element = doc.FirstChildElement("MapName");
	ui->mapName->setText(QString::fromStdString(element->GetText()));
	element = element->NextSiblingElement("MapTeam");
	ticpp::Element *subElement = element->FirstChildElement("Team2");
	ui->team2Relation->setCurrentIndex(ui->team2Relation->findText(QString::fromStdString(subElement->GetAttribute("TeamType"))));
	ui->team2Faction->setText(QString::fromStdString(subElement->GetAttribute("TeamFaction")));
	subElement = subElement->NextSiblingElement("Team3");
	ui->team3Relation->setCurrentIndex(ui->team3Relation->findText(QString::fromStdString(subElement->GetAttribute("TeamType"))));
	ui->team3Faction->setText(QString::fromStdString(subElement->GetAttribute("TeamFaction")));
	subElement = subElement->NextSiblingElement("Team4");
	ui->team4Relation->setCurrentIndex(ui->team4Relation->findText(QString::fromStdString(subElement->GetAttribute("TeamType"))));
	ui->team4Faction->setText(QString::fromStdString(subElement->GetAttribute("TeamFaction")));
	element = element->NextSiblingElement("MapScript");
	ui->mapScript->setText(QString::fromStdString(element->GetText()));
	element = element->NextSiblingElement("MapInfo");
	ui->mapInfo->setText(QString::fromStdString(element->GetText()));
	element = element->NextSiblingElement("MapLoadBG");
	ui->mapBG->setText(QString::fromStdString(element->GetText()));
	element = element->NextSiblingElement("MapSize");
	int gridSize = QString::fromStdString(element->GetText()).toInt();
	TerrainSystem *terrain = IIRoot::getSingleton().mTerrain;
	terrain->initTerrain(gridSize, 16);
	TerrainEditor *editor = terrain->addEditor(GroundID,SecGrid);
	editor->setEditorMode(PutMode);
	element = element->NextSiblingElement("MapData");
	QString mapData = QString::fromStdString(element->GetText());
	for (int z = 0; z < gridSize; z++)
	{
		for (int x = 0; x < gridSize; x++)
		{
			int index = (z * gridSize + x) * 2;
			char prefix = mapData.at(index).toAscii();
			char suffix = mapData.at(index + 1).toAscii();
			std::string type;
			if (prefix == 'l')
			{
				if (suffix == 'g')
				{
					type = "GreenLand";
				}
				else if (suffix == 'd')
				{
					type = "Desert";
				}
				else if (suffix == 'w')
				{
					type = "Swamp";
				}
				else if (suffix == 's')
				{
					type = "Snow";
				}
			}
			else if (prefix == 'h')
			{
				if (suffix == 'g')
				{
					type = "HighGroundGreen";
				}
				else if (suffix == 'd')
				{
					type = "HighGroundDesert";
				}
				else if (suffix == 'w')
				{
					type = "HighGroundSwamp";
				}
				else if (suffix == 's')
				{
					type = "HighGroundSnow";
				}
			}
			else if (prefix == 'w')
			{
				if (suffix == 'g')
				{
					type = "WaterGreen";
				}
				else if (suffix == 'd')
				{
					type = "WaterDesert";
				}
				else if (suffix == 'w')
				{
					type = "WaterSwamp";
				}
				else if (suffix == 's')
				{
					type = "WaterSnow";
				}
			}
			else if (prefix == 'r')
			{
				type = "Ramp";
			}
			editor->setEditorType(type);
			editor->setGrid(x, z);
		}
	}
}

void MainWindow::SaveMap()
{
	bool ok;
	QString text = QInputDialog::getText(this,
										tr("请输入地图文件名"),
										tr("地图文件名:"),
										QLineEdit::Normal,
										QString(),
										&ok);
	if (ok && !text.isEmpty())
	{
		ticpp::Document* doc = new ticpp::Document(text.toStdString());
		doc->Clear();
		ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
		doc->LinkEndChild(decl);
		//地图基本信息
		ticpp::Element * element = new ticpp::Element( "MapName" );
		element->SetText(ui->mapName->text().toStdString());
		doc->LinkEndChild(element);
		element = new ticpp::Element( "MapTeam" );
		ticpp::Element * subelement = new ticpp::Element( "Team2" );
		subelement->SetAttribute("TeamType",ui->team2Relation->currentText().toStdString());
		subelement->SetAttribute("TeamFaction",ui->team2Faction->text().toStdString());
		element->LinkEndChild(subelement);
		subelement = new ticpp::Element( "Team3" );
		subelement->SetAttribute("TeamType",ui->team3Relation->currentText().toStdString());
		subelement->SetAttribute("TeamFaction",ui->team3Faction->text().toStdString());
		element->LinkEndChild(subelement);
		subelement = new ticpp::Element( "Team4" );
		subelement->SetAttribute("TeamType",ui->team4Relation->currentText().toStdString());
		subelement->SetAttribute("TeamFaction",ui->team4Faction->text().toStdString());
		element->LinkEndChild(subelement);
		doc->LinkEndChild(element);
		element = new ticpp::Element( "MapScript" );
		element->SetText(ui->mapScript->text().toStdString());
		doc->LinkEndChild(element);
		element = new ticpp::Element( "MapInfo" );
		element->SetText(ui->mapInfo->toPlainText().toStdString());
		doc->LinkEndChild(element);
		element = new ticpp::Element("MapLoadBG");
		element->SetText(ui->mapBG->text().toStdString());
		doc->LinkEndChild(element);
		//地图地形信息
		TerrainSystem* terrain = IIRoot::getSingleton().mTerrain;
		int mapsize = terrain->getGridSize();
		element = new ticpp::Element("MapSize");
		element->SetText(mapsize);
		doc->LinkEndChild(element);
		element = new ticpp::Element("MapData");
		char* mapdata = new char[mapsize * mapsize *2];
		char* mapdataptr = mapdata;
		for(int z = 0; z < mapsize; z++)
		{
			for(int x = 0; x < mapsize; x++)
			{
				switch (terrain->mTerrainBlocks[x][z]->getBlockType(BottomRight))
				{
				case HighGround:
					*mapdataptr = 'h';
					break;
				case LowGround:
					*mapdataptr = 'l';
					break;
				case Water:
					*mapdataptr = 'w';
					break;
				}
				if(terrain->mRamp->isRamp(x,z))
				{
					*mapdataptr = 'r';
				}
				mapdataptr++;
				switch (terrain->mTerrainBlocks[x][z]->getTerrianType(BottomRight))
				{
				case GreenLand:
					*mapdataptr = 'g';
					break;
				case Desert:
					*mapdataptr = 'd';
					break;
				case Swamp:
					*mapdataptr = 'w';
					break;
				case Snow:
					*mapdataptr = 's';
					break;
				}
				mapdataptr++;
			}
		}
		*mapdataptr = '\0';
		element->SetText(mapdata);
		//delete [] mapdata;
		doc->LinkEndChild(element);
		
		//地图物件信息
		element = new ticpp::Element("MapObject");
		EntityTreeModel* treemodel = static_cast<EntityTreeModel*>(ui->treeView_2->model());
		EntityTreeItem* groupitem = treemodel->getRootItem()->findItem("地表物件");
		int childCount = groupitem->childCount();
		if (childCount!=0)
		{
			for (int i=0;i<childCount;i++)
			{
				EntityTreeItem* childItem = groupitem->child(i);
				ObjectData* data=static_cast<ObjectData*>(childItem->data(0));
				subelement = new ticpp::Element( data->name.toStdString() );
				subelement->SetAttribute("Type",data->EntityType.toStdString() );
				subelement->SetAttribute("GridX",data->GridX );
				subelement->SetAttribute("GridY",data->GridY );
				subelement->SetAttribute("Mesh",data->mEntity->getMesh()->getName());
				//subelement->SetAttribute("Mat",data->mEntity->getSubEntity(0)->getMaterialName());
				//模型的信息
				element->LinkEndChild(subelement);
			}
		}
		doc->LinkEndChild(element);

		//地图物件信息
		element = new ticpp::Element("MapEffect");
		groupitem = treemodel->getRootItem()->findItem("地表特效");
		childCount = groupitem->childCount();
		if (childCount!=0)
		{
			for (int i=0;i<childCount;i++)
			{
				EntityTreeItem* childItem = groupitem->child(i);
				ObjectData* data=static_cast<ObjectData*>(childItem->data(0));
				subelement = new ticpp::Element( data->name.toStdString() );
				subelement->SetAttribute("Type",data->EntityType.toStdString() );
				subelement->SetAttribute("GridX",data->GridX );
				subelement->SetAttribute("GridY",data->GridY );
				//subelement->SetAttribute("Mesh",data->mEntity->getMesh()->getName());
				//subelement->SetAttribute("Mat",data->mEntity->getSubEntity(0)->getMaterialName());
				//模型的信息
				element->LinkEndChild(subelement);
			}
		}
		doc->LinkEndChild(element);
		//地图单位信息
		element = new ticpp::Element("MapSquad");
		for(int n = 1; n <5; n++)
		{
			char groupname[20];
			sprintf_s(groupname,20,"Team%d",n);
			subelement = new ticpp::Element(groupname);
			sprintf_s(groupname,20,"势力%d单位",n);
			groupitem = treemodel->getRootItem()->findItem(groupname);
			int childCount = groupitem->childCount();
			if (childCount!=0)
			{
				for (int i=0;i<childCount;i++)
				{
					EntityTreeItem* childItem = groupitem->child(i);
					ObjectData* data=static_cast<ObjectData*>(childItem->data(0));
					ticpp::Element* subsubelement = new ticpp::Element(data->name.toStdString());
					subsubelement->SetAttribute("Type",data->EntityType.toStdString() );
					subsubelement->SetAttribute("GridX",data->GridX );
					subsubelement->SetAttribute("GridY",data->GridY );
					subelement->LinkEndChild(subsubelement);
				}
			}
			element->LinkEndChild(subelement);
		}
		doc->LinkEndChild(element);
		//地图区域信息
		element = new ticpp::Element("MapArea");

		std::vector<Area *> area = AreaManager::getSingleton().mAreaList;
		std::vector<Area *>::iterator ite;
		for (ite = area.begin(); ite != area.end(); ite++)
		{
			std::vector<int> pointlist = (*ite)->getCoordList();
			if(pointlist.size()> 0)
			{
				subelement = new ticpp::Element((*ite)->mName);
				ticpp::Element* subsubelement;
				for(int d = 0; d < pointlist.size(); d += 2)
				{
					subsubelement = new ticpp::Element(Ogre::StringConverter::toString(d/2));
					subsubelement->SetAttribute("X",pointlist[d] );
					subsubelement->SetAttribute("Y",pointlist[d+1] );
					subelement->LinkEndChild(subsubelement);
				}
				element->LinkEndChild(subelement);
			}
		}

		doc->LinkEndChild(element);
		doc->SaveFile();
	}
}
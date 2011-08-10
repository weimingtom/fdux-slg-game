#include "terraincontrol.h"
#include "ui_mainwindow.h"

#include <QAction>

#include "newterrain.h"
#include "IIRoot.h"

#include "TerrainEditor.h"

TerrainControl::TerrainControl(Ui::MainWindow *ui):
mTerrainList(ui->listWidget),mTerrainSystem(IIRoot::getSingletonPtr()->mTerrain),mEnable(false)
{
	mMapName = ui->mapName;
	mTeam2Faction = ui->team2Faction;
	mTeam3Faction = ui->team3Faction;
	mTeam4Faction = ui->team4Faction;
	mTeam2Relation = ui->team2Relation;
	mTeam3Relation = ui->team3Relation;
	mTeam4Relation = ui->team4Relation;
	mMapScript = ui->mapScript;
	mMapInfo = ui->mapInfo;
	
}

TerrainControl::~TerrainControl()
{

}

void TerrainControl::Load_Terrain()
{
	//QString fileName = QFileDialog::getOpenFileName(NULL,"打开","", tr("场景文件 (*.cfg)"));
	//fileName=fileName.split("\\").last();
	////IIRoot::getSingletonPtr()->mSceneMgr->setWorldGeometry(fileName.toLatin1().data());
}

void TerrainControl::New_Terrain()
{
	NewTerrain newTerrain;
	int result=newTerrain.exec();
	if(result==QDialog::Accepted)
	{
		mTerrainSystem->initTerrain(newTerrain.MapGrids,newTerrain.GridSize);
		createEditor();
		initMapInfo();
	}
}

void TerrainControl::initMapInfo()
{
	mMapName->setText("newmap");
	mTeam2Faction->setText("none");
	mTeam3Faction->setText("none");
	mTeam4Faction->setText("none");
	mTeam2Relation->setCurrentIndex(0);
	mTeam3Relation->setCurrentIndex(0);
	mTeam4Relation->setCurrentIndex(0);
	mMapScript->setText("none");
	mMapInfo->setText("none");
}

void TerrainControl::createEditor()
{
	TerrainEditor* newEditor=NULL;
	std::vector<std::string> typeList;

	newEditor=mTerrainSystem->addEditor(GroundID,SecGrid);

	typeList=newEditor->getEditorTypeList();

	newEditor->setEditorMode(PutMode);

	createActions(typeList,mTerrainList,GroundID);

}

void TerrainControl::createActions(std::vector<std::string> typelist,QListWidget* terrainList,EditorID editorId)
{
	for (std::vector<std::string>::iterator it=typelist.begin();it!=typelist.end();it++)
	{
		QListWidgetItem* item=new QListWidgetItem(QString((*it).c_str()));
		item->setData(Qt::UserRole,(int)editorId);
		terrainList->addItem(item);
	}
}

void TerrainControl::mouseMove(QMouseEvent * event)
{
	if (mEnable)
	{
		IIRoot::getSingletonPtr()->mTerrain->mouseMove(event->x(),event->y());
	}
}

void TerrainControl::mousePress(QMouseEvent * event)
{
	if (mEnable)
	{
		if (event->button()==Qt::MouseButton::LeftButton)
		{
			IIRoot::getSingletonPtr()->mTerrain->mousePress(event->x(),event->y(),LeftButton);
		}
		else if (event->button()==Qt::MouseButton::MidButton)
		{
			IIRoot::getSingletonPtr()->mTerrain->mousePress(event->x(),event->y(),MidButton);
		}
		else if (event->button()==Qt::MouseButton::RightButton)
		{
			IIRoot::getSingletonPtr()->mTerrain->mousePress(event->x(),event->y(),RightButton);
		}
	}
}

void TerrainControl::mouseRelease(QMouseEvent * event)
{

}

void TerrainControl::stateChanged( int state )
{
	if (state==Qt::Checked)
	{
		mEnable=true;
		mTerrainList->setEnabled(mEnable);
		mTerrainSystem->setCurrentGridCursorVisible(true);
	}
	else
	{
		mEnable=false;
		mTerrainList->setEnabled(mEnable);
		mTerrainSystem->setCurrentGridCursorVisible(false);
	}
}

void TerrainControl::currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous )
{
	EditorID id=(EditorID)current->data(Qt::UserRole).toInt();
	TerrainEditor* editor=mTerrainSystem->getEditor(id);
	editor->setEditorType(std::string(current->text().toLocal8Bit().data()));
	mTerrainSystem->setCurrentEditor(id);
}

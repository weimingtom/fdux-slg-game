#include "AreaContral.h"

#include "AreaListModule.h"

#include "AreaManager.h"
#include "Area.h"
#include "IIRoot.h"

AreaControl::AreaControl(QListView *listview)
{
	mAreaListModule = new AreaListModule(this);
	mAreaList = listview;
	mAreaList->setModel(mAreaListModule);
	mArea = NULL;
	this->connect(mAreaList,SIGNAL(clicked(const QModelIndex& )), this,SLOT(ChooseArea(const QModelIndex& )));
}

AreaControl::~AreaControl()
{

}

void AreaControl::mousePress(QMouseEvent * event)
{
	if(event->button() == Qt::MouseButton::LeftButton)
	{
		switch(mState)
		{
		case AREA_ADD:
			if(mArea)
			{
				int x,y;
				IIRoot::getSingleton().mTerrain->coordinateToGrid(event->x(), event->y(), &x,&y);
				mArea->addCoord(x,y);
			}
			break;
		case AREA_DEL:
			if(mArea)
			{
				int x,y;
				IIRoot::getSingleton().mTerrain->coordinateToGrid(event->x(), event->y(), &x,&y);
				mArea->removeCoord(x,y);
			}
			break;
		}
	}
}

void AreaControl::AddArea()
{
	mAreaListModule->insertRow(0);
}
void AreaControl::DelArea()
{
	QItemSelectionModel* selectionModel =mAreaList->selectionModel();
	QModelIndex selectionIndex=selectionModel->currentIndex();
	Area *area = mArea = AreaManager::getSingleton().mAreaList[selectionIndex.row()];
	if(area == mArea)
	{
		mArea->setVisable(false);
		mArea = NULL;
	}
	mAreaListModule->removeRow(selectionIndex.row());
	mAreaList->reset();
	delete area;
}
void AreaControl::CancelArea()
{
	if(mArea)
	{
		mArea->setVisable(false);
		mArea = NULL;
	}
	mState = AREA_IDLE;
}

void AreaControl::AddCoord()
{
	if(mArea)
		mState = AREA_ADD;
}
void AreaControl::DelCoord()
{
	if(mArea)
		mState = AREA_DEL;
}

void AreaControl::ChooseArea(const QModelIndex & index)
{
	if(mArea)
	{
		mArea->setVisable(false);
		mArea = NULL;
	}
	mArea = AreaManager::getSingleton().mAreaList[index.row()];
	mArea->setVisable(true);
}
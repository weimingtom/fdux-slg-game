#include "ToolBarControl.h"

#include <QInputDialog>

ToolBarControl::ToolBarControl(QTreeWidget* tree,TimeBar* timeBar):mTree(tree),mTimeBar(timeBar)
{
	
}

ToolBarControl::~ToolBarControl()
{

}

void ToolBarControl::addAction( bool checked )
{
	QString name=QInputDialog::getText(NULL,tr("input_name"),tr("input_name"));
	unsigned int start=QInputDialog::getInteger(NULL,tr("input_startTime"),tr("input_startTime"));
	unsigned int end=QInputDialog::getInteger(NULL,tr("input_endTime"),tr("input_endTime"));
	
	if (!name.isEmpty())
	{
		QTreeWidgetItem* item=new QTreeWidgetItem(QStringList(name));
		mTree->addTopLevelItem(item);
		int index=mTree->indexOfTopLevelItem(item);
		TimeLine* timeLine=new TimeLine();
		timeLine->startTime=start;
		timeLine->endTime=end;
		mTimeBar->addTiemLine(index,timeLine);

	}
	
}

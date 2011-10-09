#ifndef TOOLBARCONTROL_H
#define TOOLBARCONTROL_H

#include "TimeBar.h"
#include <QTreeWidget>

class ToolBarControl : public QObject
{
	Q_OBJECT

public slots:
	void addAction(bool checked);

public:
	ToolBarControl(QTreeWidget* tree,TimeBar* timeBar);
	~ToolBarControl();

private:
	QTreeWidget* mTree;
	TimeBar* mTimeBar;
};

#endif // TOOLBARCONTROL_H

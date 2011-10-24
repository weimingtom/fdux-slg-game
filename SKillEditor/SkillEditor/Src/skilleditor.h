#ifndef SKILLEDITOR_H
#define SKILLEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_skilleditor.h"

#include <QLCDNumber>
#include <QLabel>
#include <QTimer>

#include <Ogre.h>

#include "renderwindow.h"
#include "ToolBarControl.h"
#include "SkillManager.h"

class SkillEditor : public QMainWindow,public Ogre::LogListener
{
	Q_OBJECT

public:
	SkillEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SkillEditor();

	void messageLogged (const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName);
	void initValue();
	void timerEvent(QTimerEvent * event);

	IIRenderWindow* getGView();

private:
	IIRenderWindow* rWindow;

	ToolBarControl* mToolBarControl;

	Ui::SkillEditorClass ui;
	QLCDNumber* mCruuTimeShower;
	QLabel* mFpsLable;
	QLabel* mCameraLable;

	SkillManager* mSkillManager;
	unsigned int mDeltaTime;
	QTimer mTimer;


};

#endif // SKILLEDITOR_H

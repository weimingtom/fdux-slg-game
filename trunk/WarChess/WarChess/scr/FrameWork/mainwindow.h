#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QKeyEvent>
#include <QGraphicsView>

#include <Ogre.h>
#include "renderwindow.h"
#include "terraincontrol.h"
#include "CameraControl.h"
#include "entitytreecontrol.h"
#include "ObjcetControl.h"
#include "AttributeControl.h"
#include "DataEditorControl.h"
#include "AreaContral.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow,public Ogre::LogListener
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void messageLogged (const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName);
    void initValue();
    void timerEvent(QTimerEvent * event);

    IIRenderWindow* getGView();
    QStatusBar* getBar();

private:
    Ui::MainWindow *ui;
    IIRenderWindow* rWindow;
	TerrainControl* terrainControl;
	CameraControl* cameraControl;
	EntityTreeControl* entityTreeControl;
	ObjcetControl* objectControl;
	AttributeControl* attributeControl;
	AreaControl *mAreaControl;

	QLabel* mFpsLable;
	QLabel* mCameraLable;

	//Êý¾Ý±à¼­Æ÷¿ØÖÆ
	DataEditorControl* dataEditorControl;

public slots:
	void SaveMap();
};

#endif // MAINWINDOW_H

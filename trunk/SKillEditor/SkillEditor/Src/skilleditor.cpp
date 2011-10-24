#include "skilleditor.h"

#include <IIRoot.h>

SkillEditor::SkillEditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),mDeltaTime(0)
{
	ui.setupUi(this);

	mSkillManager=new SkillManager();

	rWindow=ui.graphicsView;
	mFpsLable=new QLabel(this);
	mCameraLable=new QLabel(this);
	ui.statusBar->addWidget(mFpsLable);
	ui.statusBar->addWidget(mCameraLable);
	rWindow->setMainWindow(this);
	rWindow->setInfoLable(mFpsLable,mCameraLable);

	ui.treeWidget->setHeaderLabel(tr("layer"));

	//初始化工具条
	mToolBarControl=new ToolBarControl(ui.treeWidget,ui.widget);
	this->connect(ui.actionAddItem,SIGNAL(triggered(bool)),mToolBarControl,SLOT(addAction(bool)));
	
	//初始化LCD显示
	mCruuTimeShower=new QLCDNumber();
	mCruuTimeShower->setSegmentStyle(QLCDNumber::Flat);
	ui.statusBar->addWidget(new QLabel(tr("CurrTime:")));
	ui.statusBar->addWidget(mCruuTimeShower);
	this->connect(ui.widget,SIGNAL(CurrTimeChange(int)),mCruuTimeShower,SLOT(display(int)));
	ui.widget->setCurrTime(1000);
}

SkillEditor::~SkillEditor()
{

}

IIRenderWindow* SkillEditor::getGView()
{
	return rWindow;
}

void SkillEditor::timerEvent( QTimerEvent * event )
{
	mTimer.start();
	rWindow->timerEvent(event);
	mSkillManager->update(mDeltaTime);
	IIRoot::getSingletonPtr()->mRoot->renderOneFrame();
	mDeltaTime=mTimer.interval()+1;
	mTimer.stop();
}

void SkillEditor::messageLogged( const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName )
{

}

void SkillEditor::initValue()
{

}

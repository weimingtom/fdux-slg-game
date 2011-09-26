#include "launcher.h"

#include <windows.h>
Launcher::Launcher(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	bgimage.load("../Media/UI/menubg.png");
	this->connect(ui.commandLinkButton,SIGNAL(clicked(bool)),this,SLOT(windowRunGame()));
	this->connect(ui.commandLinkButton_2,SIGNAL(clicked(bool)),this,SLOT(fullSceneRunGame()));
	this->connect(ui.commandLinkButton_3,SIGNAL(clicked(bool)),this,SLOT(gameManual()));
	this->connect(ui.commandLinkButton_4,SIGNAL(clicked(bool)),this,SLOT(readMe()));
	this->connect(ui.commandLinkButton_5,SIGNAL(clicked(bool)),this,SLOT(setupDirectx()));
	this->connect(ui.commandLinkButton_6,SIGNAL(clicked(bool)),this,SLOT(visitWebSite()));
	this->connect(ui.commandLinkButton_7,SIGNAL(clicked(bool)),this,SLOT(sendFeedback()));
}

Launcher::~Launcher()
{

}

void Launcher::resizeEvent( QResizeEvent *event )
{
	QWidget::resizeEvent(event);

	QPalette pal(palette());

	pal.setBrush(QPalette::Window,QBrush(bgimage.scaled(event->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

	setPalette(pal);
}

void Launcher::windowRunGame()
{
	WinExec("ForgottenBattlefield.exe",SW_NORMAL);
	this->close();
}

void Launcher::fullSceneRunGame()
{
	WinExec("ForgottenBattlefield.exe -FullScene",SW_NORMAL);
	this->close();
}

void Launcher::gameManual()
{
	ShellExecute(NULL,NULL,L"..\\游戏手册.doc",NULL,NULL,SW_SHOWNORMAL);
}

void Launcher::readMe()
{
	ShellExecute(NULL,NULL,L"..\\readme不看木小JJ.txt",NULL,NULL,SW_SHOWNORMAL);
}

void Launcher::setupDirectx()
{
	WinExec("..\\Support\\DirectX\\DXSETUP.exe",SW_NORMAL);
}

void Launcher::visitWebSite()
{
	ShellExecute(NULL, L"open",L"http://fdux.xoom.it/ ", NULL, NULL, SW_SHOWNORMAL);  
}

void Launcher::sendFeedback()
{
	WinExec("Feedback.exe",SW_NORMAL);
}

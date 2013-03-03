#include "launcher.h"

#include <windows.h>

#include <QDomDocument>
Launcher::Launcher(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	bgimage.load("menubg.png");
	this->connect(ui.commandLinkButton,SIGNAL(clicked(bool)),this,SLOT(windowRunGame()));
	this->connect(ui.commandLinkButton_2,SIGNAL(clicked(bool)),this,SLOT(fullSceneRunGame()));
	this->connect(ui.commandLinkButton_3,SIGNAL(clicked(bool)),this,SLOT(gameManual()));
	this->connect(ui.commandLinkButton_4,SIGNAL(clicked(bool)),this,SLOT(readMe()));
	this->connect(ui.commandLinkButton_5,SIGNAL(clicked(bool)),this,SLOT(setupDirectx()));
	this->connect(ui.commandLinkButton_6,SIGNAL(clicked(bool)),this,SLOT(visitWebSite()));
	this->connect(ui.commandLinkButton_7,SIGNAL(clicked(bool)),this,SLOT(setupXP()));
	this->connect(ui.label,SIGNAL(linkActivated (QString)),this,SLOT(openRss(QString)));
	this->connect(ui.label_2,SIGNAL(linkActivated (QString)),this,SLOT(openRss(QString)));
	this->connect(ui.label_3,SIGNAL(linkActivated (QString)),this,SLOT(openRss(QString)));
	this->connect(ui.label_4,SIGNAL(linkActivated (QString)),this,SLOT(openRss(QString)));
	this->connect(ui.label_5,SIGNAL(linkActivated (QString)),this,SLOT(openRss(QString)));
	this->connect(ui.pushButton,SIGNAL(clicked(bool)),this,SLOT(weibo()));

	reply = manager.get(QNetworkRequest(QUrl("http://1.fdux.sinaapp.com/?cat=4&feed=rss2")));
	connect(reply, SIGNAL(finished()),
		this, SLOT(httpFinished()));
	connect(reply, SIGNAL(readyRead()),
		this, SLOT(httpReadyRead()));
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

void Launcher::setupXP()
{
	ShellExecute(NULL,NULL,L"..\\Support\\setup.bat",NULL,NULL,SW_SHOWNORMAL);
}

void Launcher::visitWebSite()
{
	ShellExecute(NULL, L"open",L"http://1.fdux.sinaapp.com/ ", NULL, NULL, SW_SHOWNORMAL);  
}

void Launcher::httpFinished()
{
	parseXML();
}

void Launcher::httpReadyRead()
{
	rss+=QString::fromUtf8(reply->readAll());
}

void Launcher::parseXML()
{
	QDomDocument doc;
	doc.setContent(rss);
	QDomElement docElem = doc.documentElement();
	QDomElement channel=docElem.firstChildElement("channel");
	
	int i=0;
	QDomNodeList itemList=channel.elementsByTagName("item");
	int a=itemList.length();
	
	for (i=0;i<itemList.size();i++)
	{
		QString titleString=itemList.at(i).firstChildElement("title").text();
		switch(i)
		{
		case 0:
			ui.label->setText("<font color='red'><a href='"+itemList.at(i).firstChildElement("link").text()+"'>"+titleString+"</a></font>");
			break;
		case 1:
			ui.label_2->setText("<a href='"+itemList.at(i).firstChildElement("link").text()+"'>"+titleString+"</a>");
			break;
		case 2:
			ui.label_3->setText("<a href='"+itemList.at(i).firstChildElement("link").text()+"'>"+titleString+"</a>");
			break;
		case 3:
			ui.label_4->setText("<a href='"+itemList.at(i).firstChildElement("link").text()+"'>"+titleString+"</a>");
			break;
		case 4:
			ui.label_5->setText("<a href='"+itemList.at(i).firstChildElement("link").text()+"'>"+titleString+"</a>");
			break;
		}

		
	}
}

void Launcher::openRss(QString link)
{
	wchar_t c[200];
	int a=link.toWCharArray(c);
	c[a]=0;
	ShellExecute(NULL, L"open",c, NULL, NULL, SW_SHOWNORMAL); 
}

void Launcher::weibo()
{
	ShellExecute(NULL, L"open",L"http://weibo.com/u/2891329060", NULL, NULL, SW_SHOWNORMAL);  
}

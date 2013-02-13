#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QtGui/QMainWindow>
#include "ui_launcher.h"

#include <QResizeEvent>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QUrl>
#include <QByteArray>
#include <QDate>
#include <QFile>
#include <QMessageBox>
class Launcher : public QMainWindow
{
	Q_OBJECT

public:
	Launcher(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Launcher();

private:
	Ui::LauncherClass ui;
	QPixmap bgimage;
	void resizeEvent(QResizeEvent *event);
	void parseXML();

public slots:
	void windowRunGame();
	void fullSceneRunGame();
	void gameManual();
	void readMe();
	void setupDirectx();
	void visitWebSite();
	void openRss(QString link);
	void weibo();

	void httpFinished();
	void httpReadyRead();
private:
	QNetworkAccessManager manager;
	QNetworkReply *reply;

	QString rss;
};

#endif // LAUNCHER_H

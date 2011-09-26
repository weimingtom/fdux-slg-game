#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QtGui/QMainWindow>
#include "ui_launcher.h"

#include <QResizeEvent>

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

public slots:
	void windowRunGame();
	void fullSceneRunGame();
	void gameManual();
	void readMe();
	void setupDirectx();
	void visitWebSite();
	void sendFeedback();
};

#endif // LAUNCHER_H

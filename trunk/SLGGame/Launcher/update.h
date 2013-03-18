#ifndef UPDATE_H
#define UPDATE_H

#include <QWidget>
#include "ui_update.h"

#include "launcher.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

enum updateSetp
{
	checkVer,
	getDownloadInfo,
	Download,
};

class update : public QWidget
{
	Q_OBJECT

public:
	update(QWidget *parent,Launcher* l);
	~update();

	void paintEvent(QPaintEvent * e);

public slots:

		void httpFinished();
		void httpReadyRead();
		void httpError(QNetworkReply::NetworkError);
		void downloadProgress(qint64 bytesReceived, qint64 bytesTotal );

private:
	void closeUpdate();

	Ui::Form ui;

	QNetworkAccessManager manager;
	QNetworkReply *reply;

	QString mCurVer;
	QString mNewVer;
	QString mGUID;
	QString mDownLoadRequest;
	QString mUpdateLog;
	QFile* mTempFile;

	updateSetp mSetp;
	QString mReceive;
	Launcher* mLauncher;


};

#endif // UPDATE_H

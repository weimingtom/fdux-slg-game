#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QtGui/QMainWindow>
#include "ui_feedback.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QUrl>
#include <QByteArray>
#include <QDate>

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QResizeEvent>
#include <QTextCodec>

class Feedback : public QMainWindow
{
	Q_OBJECT

public:
	Feedback(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Feedback();

private:
	void resizeEvent(QResizeEvent *event);
	void releaseNetworkResource();

public slots:
	void SendFeedback();

	void sendFeedbackFinished(QNetworkReply *reply);

private:
	Ui::FeedbackClass ui;
	QPixmap bgimage;

	QUrl *params;
	QByteArray *data;
	QNetworkAccessManager *manager;
	QNetworkRequest *request;
};

#endif // FEEDBACK_H

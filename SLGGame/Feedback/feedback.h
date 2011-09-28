#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QtGui/QMainWindow>
#include "ui_feedback.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>

#include <QUrl>
#include <QByteArray>
#include <QDate>

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QResizeEvent>

class Feedback : public QMainWindow
{
	Q_OBJECT

public:
	Feedback(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Feedback();

private:
	void resizeEvent(QResizeEvent *event);

public slots:
	void SendFeedback();

private:
	Ui::FeedbackClass ui;
	QPixmap bgimage;
};

#endif // FEEDBACK_H

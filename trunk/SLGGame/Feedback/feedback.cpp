#include "feedback.h"

Feedback::Feedback(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	bgimage.load("../Media/UI/menubg.png");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(SendFeedback()));

	manager = NULL;
	request = NULL;
	params = NULL;
	data = NULL;
}

Feedback::~Feedback()
{
	releaseNetworkResource();
}

void Feedback::SendFeedback()
{
	releaseNetworkResource();

	manager = new QNetworkAccessManager(this);
	request = new QNetworkRequest(QUrl("http://localhost/send_feedback.php"));
	request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QString date = QDate::currentDate().toString("yyyy.MM.dd");
	QString feedback = ui.plainTextEdit->toPlainText();
	QString name = ui.nameEdit->text();
	QString email = ui.emailEdit->text();
	if (feedback.isEmpty())
	{
		QMessageBox::information(NULL, QString::fromStdWString(L"提示"), QString::fromStdWString(L"您还没有填写任何反馈内容。"));
		return;
	}

    params = new QUrl();
	params->addQueryItem("date", date);
	params->addQueryItem("feedback", feedback);
	params->addQueryItem("name", name);
	params->addQueryItem("email", email);
    data = new QByteArray(params->encodedQuery());

	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(sendFeedbackFinished(QNetworkReply*)));
    manager->post(*request, *data);
}

void Feedback::releaseNetworkResource()
{
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}
	if (params != NULL)
	{
		delete params;
		params = NULL;
	}
	if (request != NULL)
	{
		delete request;
		request = NULL;
	}
	if (manager != NULL)
	{
		delete manager;
		manager = NULL;
	}
}

void Feedback::sendFeedbackFinished(QNetworkReply *reply)
{
	/*
	if (reply->error() == QNetworkReply::NoError)
	{
		QMessageBox::information(NULL, QString::fromStdWString(L"提示"), QString::fromStdWString(L"您已经成功提交了反馈，感谢您对游戏提出的宝贵意见！"));
	}
	else
	{
		QMessageBox::information(NULL, QString::fromStdWString(L"提示"), QString::fromStdWString(L"您的反馈提交失败！"));
	}
	*/

	QMessageBox::information(NULL, QString::fromStdWString(L"提示"), QTextCodec::codecForName("utf8")->toUnicode(reply->readAll()));
	reply->deleteLater();
}

void Feedback::resizeEvent( QResizeEvent *event )
{
	QWidget::resizeEvent(event);
	QPalette pal(palette());
	pal.setBrush(QPalette::Window,QBrush(bgimage.scaled(event->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
	setPalette(pal);
}
#include "feedback.h"

Feedback::Feedback(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	bgimage.load("../Media/UI/menubg.png");
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(SendFeedback()));
}

Feedback::~Feedback()
{
}

void Feedback::SendFeedback()
{
	QNetworkAccessManager manager(this);
	QNetworkRequest request(QUrl("http://localhost/send_feedback.php"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QString date = QDate::currentDate().toString("yyyy.MM.dd");
	QString feedback = ui.plainTextEdit->toPlainText();
	QString name = ui.nameEdit->text();
	QString email = ui.emailEdit->text();
	if (feedback.isEmpty())
	{
		QMessageBox::information(NULL, "debug", "empty feedback");
		return;
	}

    QUrl params;
	params.addQueryItem("date", date);
	params.addQueryItem("feedback", feedback);
	params.addQueryItem("name", name);
	params.addQueryItem("email", email);
    QByteArray data = params.encodedQuery();

    manager.post(request, data);

	QMessageBox::information(NULL, "debug", "feedback finished !");
}

void Feedback::resizeEvent( QResizeEvent *event )
{
	QWidget::resizeEvent(event);
	QPalette pal(palette());
	pal.setBrush(QPalette::Window,QBrush(bgimage.scaled(event->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
	setPalette(pal);
}
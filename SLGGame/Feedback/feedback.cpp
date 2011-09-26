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
}

void Feedback::resizeEvent( QResizeEvent *event )
{
	QWidget::resizeEvent(event);

	QPalette pal(palette());

	pal.setBrush(QPalette::Window,QBrush(bgimage.scaled(event->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

	setPalette(pal);
}
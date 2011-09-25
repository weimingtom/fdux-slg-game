#include "feedback.h"

Feedback::Feedback(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(SendFeedback()));

	try
	{
		driver = get_driver_instance();
		con = driver->connect("localhost", "root", "");
		con->setSchema("feedback");

		QMessageBox::information(NULL, "debug", "connected to the database");
	}
	catch(sql::SQLException &e)
	{
		QMessageBox::information(NULL, "debug", QString::fromStdString(e.what()));
	}
}

Feedback::~Feedback()
{
	try
	 {
		 delete con;

		 QMessageBox::information(NULL, "debug", "resource released");
	 }
	 catch(sql::SQLException &e)
	 {
		 QMessageBox::information(NULL, "debug", QString::fromStdString(e.what()));
	 }
}

void Feedback::SendFeedback()
{
	try
	{
		stmt = con->createStatement();
		stmt->execute("insert into feedback set feedback='" + ui.plainTextEdit->toPlainText().toStdString() + "'");
		delete stmt;

		QMessageBox::information(NULL, "debug", "feedback sent to the database");
	}
	catch(sql::SQLException &e)
	 {
		 QMessageBox::information(NULL, "debug", QString::fromStdString(e.what()));
	 }
}

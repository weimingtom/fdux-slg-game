#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QtGui/QMainWindow>
#include "ui_feedback.h"

#include <QMessageBox>
#include <QPlainTextEdit>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>

class Feedback : public QMainWindow
{
	Q_OBJECT

public:
	Feedback(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Feedback();

public slots:
	void SendFeedback();

private:
	Ui::FeedbackClass ui;

	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
};

#endif // FEEDBACK_H

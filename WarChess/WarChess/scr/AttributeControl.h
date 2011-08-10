#ifndef ATTRIBUTECONTROL_H
#define ATTRIBUTECONTROL_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMap>

class AttributeControl : public QObject
{
	Q_OBJECT

public:
	AttributeControl(QTableWidget* tableWidget);
	~AttributeControl();

	void setAttribute(const QMap<QString,QString>& attribute);
	void setAttribute(QString name,QString value);
	QMap<QString,QString> getAttribute();
	void clearAttribute();

signals:
	void attributeChangle(QString name,QString value);

public slots:
	void itemChanged(QTableWidgetItem * item);
private:
	QTableWidget* mTableWidget;	
};

#endif // ATTRIBUTECONTROL_H

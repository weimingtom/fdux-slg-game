#include "AttributeControl.h"

#include "AttributeItemDelegate.h"
#include <QStringList>

AttributeControl::AttributeControl(QTableWidget* tableWidget)
	: mTableWidget(tableWidget)
{
	AttributeItemDelegate* delegate=new AttributeItemDelegate();
	mTableWidget->setItemDelegate(delegate);

	connect(mTableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(itemChanged(QTableWidgetItem*)));
}

AttributeControl::~AttributeControl()
{

}

void AttributeControl::setAttribute( const QMap<QString,QString>& attribute )
{
	mTableWidget->clear();

	mTableWidget->setRowCount(attribute.size());
	mTableWidget->setColumnCount(2);
	mTableWidget->setSortingEnabled(false);

	int Row=0;

	QMapIterator<QString, QString> i(attribute);
	while (i.hasNext()) 
	{
		i.next();
		
		QStringList sl=i.key().split("#");//以#进行切分,取第二部分作为类型提示符
		QTableWidgetItem* newItemName = new QTableWidgetItem(sl.at(0));
		newItemName->setFlags(Qt::ItemFlag::NoItemFlags);
		mTableWidget->setItem(Row, 0, newItemName);
		QTableWidgetItem* newItemValue = new QTableWidgetItem(i.value());
		mTableWidget->setItem(Row, 1, newItemValue);

		if (sl.size()>=2)
		{
			if (sl.at(1).left(4)=="enum")
			{
				QStringList enumList;
				enumList=sl.at(1).split("|");
				enumList.removeFirst();
				newItemValue->setData(Qt::UserRole,QVariant(QString("enum")));
				newItemValue->setData(Qt::UserRole+1,QVariant(enumList));
			}
			else if (sl.at(1).left(7)=="integer")
			{
				QStringList intList;
				intList=sl.at(1).split("|");
				intList.removeFirst();
				newItemValue->setData(Qt::UserRole,QVariant(QString("integer")));
				newItemValue->setData(Qt::UserRole+1,QVariant(intList.at(0).toInt()));
				newItemValue->setData(Qt::UserRole+2,QVariant(intList.at(1).toInt()));
			}
			else
			{
				newItemValue->setData(Qt::UserRole,QVariant(sl.at(1)));
			}
		}

		Row++;
	}

	QStringList sl;
	sl.append("属性");
	sl.append("值");
	mTableWidget->setHorizontalHeaderLabels(sl);
}

void AttributeControl::setAttribute( QString name,QString value )
{
	QList<QTableWidgetItem*> itemList=mTableWidget->findItems(name,Qt::MatchFixedString);
	for(QList<QTableWidgetItem*>::Iterator it=itemList.begin();it!=itemList.end();it++)
	{
		if ((*it)->column()==0)
		{
			mTableWidget->item((*it)->row(),1)->setText(value);
			break;
		}
	}
}

QMap<QString,QString> AttributeControl::getAttribute()
{
	QMap<QString,QString> map;
	
	for (int i=0;i<mTableWidget->rowCount();i++)
	{
		QTableWidgetItem* name=mTableWidget->item(i,0);
		QTableWidgetItem* value=mTableWidget->item(i,1);
		map[name->text()]=value->text();
	}

	return map;
}

void AttributeControl::itemChanged( QTableWidgetItem * item )
{
	emit attributeChangle(mTableWidget->item(item->row(),0)->text(),item->text());
}

void AttributeControl::clearAttribute()
{
	mTableWidget->clear();
	mTableWidget->setColumnCount(0);
	mTableWidget->setRowCount(0);
}

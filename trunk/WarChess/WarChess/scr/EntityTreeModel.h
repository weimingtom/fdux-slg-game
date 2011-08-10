#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QDomDocument>

#include "EntityTreeItem.h"

class EntityTreeModel:public QAbstractItemModel
{
	Q_OBJECT

public:
	EntityTreeModel(QObject *parent = 0);
	~EntityTreeModel(void);

     QVariant data(const QModelIndex &index, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;	
	 
	 EntityTreeItem* getRootItem();

	 void setSelectItem(const QModelIndex &item);

	 void LoadXML(QDomDocument doc);
	 QDomDocument SaveXML();


private:
	EntityTreeItem* rootItem;
	QModelIndex mSelectItem;  

};

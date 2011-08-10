#include "EntityTreeModel.h"

#include <QIcon>

EntityTreeModel::EntityTreeModel(QObject *parent):QAbstractItemModel(parent),mSelectItem(QModelIndex())
{
	rootItem=new EntityTreeItem(new EntityData("Root"),NULL,EntityItemType::Group);
}

EntityTreeModel::~EntityTreeModel(void)
{
	delete rootItem;
}

QVariant EntityTreeModel::data(const QModelIndex &index, int role) const//取得QModelIndex指向的数据
{
     if (!index.isValid())
	 {
         return QVariant();
	 }
	 else
	 {
		 EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
		 if (role == Qt::DisplayRole)//如果要求取该Item的标题
		 {
			 return item->data(index.column())->name;
		 }
		 else if(role==Qt::DecorationRole)//如果要去取该Item的图标
		 {
			 if(item->entityItemType==EntityItemType::Group)
			 {
				 return QIcon(":/WarChess/Resources/fileopen.png");
			 }
			 else
			 {
				 if (mSelectItem.isValid() && mSelectItem==index)
				 {
					return QIcon(":/WarChess/Resources/ok.png");
				 }
				 else
				 {
					return QIcon(":/WarChess/Resources/drag.png");
				 }
			 }
		 }
		 else
		 {
			 return QVariant();
		 }
	 }
}

Qt::ItemFlags EntityTreeModel::flags(const QModelIndex &index) const//取得QModelIndex所指的项的属性,指是否可以编辑之类的
{
	if (!index.isValid())
	{
        return 0;
	}
	else
	{
		EntityTreeItem* item=static_cast<EntityTreeItem*>(index.internalPointer());
		if(item->parent()==NULL)
		{
			return (Qt::ItemFlag::ItemIsEnabled | Qt::ItemFlag::ItemIsSelectable);
		}
		else
		{
			return (Qt::ItemFlag::ItemIsEnabled |Qt::ItemFlag::ItemIsEditable| Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsDropEnabled | Qt::ItemFlag::ItemIsDragEnabled);
		}

	}
}

QVariant EntityTreeModel::headerData(int section, Qt::Orientation orientation,int role) const//返回表头信息
{
	 if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	 {
         return "实体列表";
	 }
	 else
	 {
		 return QVariant();
	 }
}

QModelIndex EntityTreeModel::index(int row, int column,const QModelIndex &parent) const
//这个函数对View来说，就是要你给它它所需要的行与列上的index.不管这个item有没有parent，view都会给你一个parent,当然，如果没有parent,那这个parent的index就是无效的。
{
	EntityTreeItem* parentItem;

	if(!parent.isValid())
	{
		parentItem=rootItem;
	}
	else
	{
		parentItem=static_cast<EntityTreeItem*>(parent.internalPointer());
	}

	EntityTreeItem *childItem = parentItem->child(row);

	if(childItem)
	{
		return createIndex(row,column,childItem);
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex EntityTreeModel::parent(const QModelIndex &index) const
//这个函数，是view向你要一个指定index的parent的index
{
	if(index.isValid())
	{
		EntityTreeItem* childItem=static_cast<EntityTreeItem*>(index.internalPointer());
		EntityTreeItem* parentItem=childItem->parent();
		
		if (parentItem==rootItem)
		{
			return QModelIndex();
		}
		else if(parentItem==NULL)
		{
			return QModelIndex();
		}
		else
		{
			return createIndex(parentItem->row(),0,parentItem);
		}
	} 
	else
	{
		return QModelIndex();
	}
}

int EntityTreeModel::rowCount(const QModelIndex &parent) const//返回某个父节点下的子节点的个数
{
	EntityTreeItem *parentItem;
	if(parent.isValid())
	{
		parentItem=static_cast<EntityTreeItem*>(parent.internalPointer());
	}
	else
	{
		parentItem=rootItem;
	}

	return parentItem->childCount();
}

int EntityTreeModel::columnCount(const QModelIndex &parent) const//一个节点有几个数据
{
	 if (parent.isValid())
	 {
         return static_cast<EntityTreeItem*>(parent.internalPointer())->columnCount();
	 }
     else
	 {
         return rootItem->columnCount();
	 }
}

EntityTreeItem* EntityTreeModel::getRootItem()
{
	return rootItem;
}

void EntityTreeModel::setSelectItem( const QModelIndex &item )
{	
	QModelIndex temp=mSelectItem;

	mSelectItem=item;

	if (temp.isValid())
	{
		emit dataChanged(temp,temp);//要求view重画以前的项,保证图标被更新
	}
}


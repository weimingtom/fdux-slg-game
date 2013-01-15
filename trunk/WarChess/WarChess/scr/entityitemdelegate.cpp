#include "entityitemdelegate.h"

#include "entitydialog.h"

EntityItemDelegate::EntityItemDelegate(QObject *parent)
{

}

EntityItemDelegate::~EntityItemDelegate()
{

}

QWidget* EntityItemDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem & option,
     const QModelIndex &index) const
 {
    EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
	if(item->entityItemType==EntityItemType::Group)
    {
		QLineEdit* stringEditor=new QLineEdit(parent);
        return stringEditor;
    }
	else if(item->entityItemType==EntityItemType::Entity)
    {
		EntityDialog* dialog=new EntityDialog(QStringList(),entityTreeModel);
		dialog->isEditer=true;
		return dialog;
    }
	else
	{
		return NULL;
	}
 }

void EntityItemDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
    EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
    if(item->entityItemType==EntityItemType::Group)
    {
		QLineEdit* stringEditor=static_cast<QLineEdit*>(editor);
        stringEditor->setText(item->data(0)->name);
    }
    else if(item->entityItemType==EntityItemType::Entity)
    {
        EntityDialog* dialog=static_cast<EntityDialog*>(editor);
		EntityDataImp* entityData=(EntityDataImp*)item->data(0);
		dialog->entityData->name=entityData->name;
		dialog->entityData->EntityName=entityData->EntityName;
		dialog->entityData->GroupName=entityData->GroupName;
		dialog->entityData->MatName=entityData->MatName;
		dialog->entityData->EntityType=entityData->EntityType;
		dialog->updataUI();
		//dialog->exec();
    }
 }

void EntityItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
	EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
    if(item->entityItemType==EntityItemType::Group)
    {
		QLineEdit* stringEditor=static_cast<QLineEdit*>(editor);
		item->data(0)->name=stringEditor->text();
		//更新下面子节点的数据

		for(int i=0;i<item->childCount();i++)//访问孩子
		{
			item->child(i)->data(0)->GroupName=stringEditor->text();//从root读取下面的子节点(就是组)
		}


    }
    else if(item->entityItemType==EntityItemType::Entity)
    {
        EntityDialog* dialog=static_cast<EntityDialog*>(editor);
		EntityDataImp* entityData=(EntityDataImp*)item->data(0);
		dialog->updataEntityData();
		entityData->name=dialog->entityData->name;
		entityData->EntityName=dialog->entityData->EntityName;
		entityData->GroupName=dialog->entityData->GroupName;
		entityData->MatName=dialog->entityData->MatName;
		entityData->EntityType=dialog->entityData->EntityType;
		if(item->data(0)->GroupName!=item->parent()->data(0)->name)//如果用户修改了实体的组
		{
			EntityTreeItem* newGroupItem=entityTreeModel->getRootItem()->findItem(item->data(0)->GroupName);
			item->parent()->removeChild(item);
			newGroupItem->appendChild(item);
			item->setParent(newGroupItem);

			treeView->reset();//修改了节点,要刷新数据
			treeView->expand(entityTreeModel->index(newGroupItem->row(),0));
		}
    }
 }

 void EntityItemDelegate::edited()
 {
     emit closeEditor(0);
 }

 void EntityItemDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &index ) const
 {
     editor->setGeometry(option.rect);
 }


#include "ObjcetItemDelegate.h"

#include "ObjectEditor.h"

ObjcetItemDelegate::ObjcetItemDelegate(QObject *parent)
{

}

ObjcetItemDelegate::~ObjcetItemDelegate()
{

}

QWidget* ObjcetItemDelegate::createEditor(QWidget *parent,
     const QStyleOptionViewItem & option,
     const QModelIndex &index) const
 {
    EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
	if(item->entityItemType==EntityItemType::Entity)
    {
		ObjectEditor* dialog=new ObjectEditor(entityTreeModel);
		//dialog->isEditer=true;
		return dialog;
    }
	else
	{
		return NULL;
	}
 }

void ObjcetItemDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
 {
    EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
    if(item->entityItemType==EntityItemType::Entity)
    {
        ObjectEditor* dialog=static_cast<ObjectEditor*>(editor);
		ObjectData* objectData=(ObjectData*)item->data(0);
		dialog->objectData->name=objectData->name;
		dialog->updataUI();
		//dialog->exec();
    }
 }

void ObjcetItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
 {
	EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());
    if(item->entityItemType==EntityItemType::Entity)
    {
		ObjectEditor* dialog=static_cast<ObjectEditor*>(editor);
		ObjectData* objectData=(ObjectData*)item->data(0);
		dialog->updataEntityData();
		objectData->name=dialog->objectData->name;
    }
 }

 void ObjcetItemDelegate::edited()
 {
     emit closeEditor(0);
 }

 void ObjcetItemDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &index ) const
 {
     editor->setGeometry(option.rect);
 }


#ifndef ENTITYITEMDELEGATE_H
#define ENTITYITEMDELEGATE_H

#include <QItemDelegate>
#include <QTreeView>

#include "EntityTreeModel.h"

class ObjcetItemDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ObjcetItemDelegate(QObject *parent);
	~ObjcetItemDelegate();

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,const QModelIndex &index) const;

	EntityTreeModel* entityTreeModel;
	QTreeView* treeView;


public slots:
    void edited();
};

#endif // ENTITYITEMDELEGATE_H

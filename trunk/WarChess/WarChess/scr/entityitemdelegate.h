#ifndef ENTITYITEMDELEGATE_H
#define ENTITYITEMDELEGATE_H

#include <QItemDelegate>
#include <QTreeView>

#include "EntityTreeModel.h"

class EntityItemDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	EntityItemDelegate(QObject *parent);
	~EntityItemDelegate();

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

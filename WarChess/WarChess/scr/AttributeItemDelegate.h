#ifndef ATTRIBUTEITEMDELEGATE_H
#define ATTRIBUTEITEMDELEGATE_H

#include <QItemDelegate>

class AttributeItemDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	AttributeItemDelegate();
	~AttributeItemDelegate();

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
private:
	
};

#endif // ATTRIBUTEITEMDELEGATE_H

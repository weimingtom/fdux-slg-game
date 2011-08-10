#include "AttributeItemDelegate.h"

#include <QTableWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>

AttributeItemDelegate::AttributeItemDelegate()
{

}

AttributeItemDelegate::~AttributeItemDelegate()
{

}

QWidget * AttributeItemDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QTableWidgetItem* item = static_cast<QTableWidgetItem*>(index.internalPointer());
	
	//取出类型提示符,根据类型创造相应的编辑器
	if (index.data(Qt::UserRole).toString()=="string")
	{
		QLineEdit* stringEditor=new QLineEdit(parent);
		return stringEditor;
	}
	else if (index.data(Qt::UserRole).toString()=="enum")
	{
		QComboBox* comboBox=new QComboBox(parent);
		return comboBox;
	}
	else if(index.data(Qt::UserRole).toString()=="integer")
	{
		QSpinBox* spinBox=new QSpinBox(parent);
		spinBox->setMinimum(index.data(Qt::UserRole+1).toInt());
		spinBox->setMaximum(index.data(Qt::UserRole+2).toInt());
		return spinBox;
	}
	else if(index.data(Qt::UserRole).toString()=="float")
	{
		QDoubleSpinBox* doubleSpinBox=new QDoubleSpinBox(parent);
		doubleSpinBox->setMinimum(-5000);
		doubleSpinBox->setMaximum(5000);
		doubleSpinBox->setSingleStep(0.1);
		return doubleSpinBox;
	}
	
	return NULL;
}

void AttributeItemDelegate::setEditorData( QWidget *editor, const QModelIndex &index ) const
{

	//取出类型提示符,根据类型设置数据
	if (index.data(Qt::UserRole).toString()=="string")
	{
		QLineEdit* stringEditor=static_cast<QLineEdit*>(editor);
		stringEditor->setText(index.data().toString());
	}
	else if (index.data(Qt::UserRole).toString()=="enum")
	{
		QComboBox* comboBox=static_cast<QComboBox*>(editor);
		QStringList sl=index.data(Qt::UserRole+1).toStringList();
		comboBox->addItems(sl);
		comboBox->setCurrentIndex(comboBox->findText(index.data().toString()));
	}
	else if(index.data(Qt::UserRole).toString()=="integer")
	{
		QSpinBox* spinBox=static_cast<QSpinBox*>(editor);
		spinBox->setValue(index.data().toInt());
	}
	else if(index.data(Qt::UserRole).toString()=="float")
	{
		QDoubleSpinBox* doubleSpinBox=static_cast<QDoubleSpinBox*>(editor);
		doubleSpinBox->setValue(index.data().toFloat());
	}
}

void AttributeItemDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	//取出类型提示符,根据类型取得数据
	if (index.data(Qt::UserRole).toString()=="string")
	{
		QLineEdit* stringEditor=static_cast<QLineEdit*>(editor);
		model->setData(index,stringEditor->text());
	}
	else if (index.data(Qt::UserRole).toString()=="enum")
	{
		QComboBox* comboBox=static_cast<QComboBox*>(editor);
		model->setData(index,comboBox->currentText());
	}
	else if(index.data(Qt::UserRole).toString()=="integer")
	{
		QSpinBox* spinBox=static_cast<QSpinBox*>(editor);
		model->setData(index,QString().setNum(spinBox->value()));
	}
	else if(index.data(Qt::UserRole).toString()=="float")
	{
		QDoubleSpinBox* doubleSpinBox=static_cast<QDoubleSpinBox*>(editor);
		model->setData(index,QString().setNum(doubleSpinBox->value()));
	}
}

void AttributeItemDelegate::updateEditorGeometry( QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

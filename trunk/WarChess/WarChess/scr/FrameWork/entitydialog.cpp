#include "entitydialog.h"

#include <QMessageBox>

EntityDialog::EntityDialog(QStringList groupList,EntityTreeModel* model,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	entityData=new EntityDataImp("null");

	this->connect(ui.okButton,SIGNAL(clicked(bool)),this,SLOT(okButton()));
	this->connect(ui.cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButton()));

	ui.comboBox->addItems(groupList);
	this->model=model;
	isEditer=false;
}

EntityDialog::~EntityDialog()
{
	delete entityData;
}

void EntityDialog::okButton()
{
	if(model->getRootItem()->findItem(ui.lineEdit->text())!=NULL  && isEditer==false)
	{
		QMessageBox::critical(NULL,"错误","已经有该实体了!");
		return;
	}
	else
	{
		updataEntityData();
		accept();
	}
}

void EntityDialog::cancelButton()
{
	reject();
}

void EntityDialog::updataUI()
{
	ui.lineEdit->setText(entityData->name);
	ui.lineEdit_2->setText(entityData->EntityName);
	ui.lineEdit_3->setText(entityData->MatName);
	ui.lineEdit_4->setText(entityData->EntityType);
	ui.comboBox->clear();

	QStringList groupList;
	for(int i=0;i<model->getRootItem()->childCount();i++)//生成组列表
	{
		groupList.append(model->getRootItem()->child(i)->data(0)->name);//从root读取下面的子节点(就是组)
	}

	ui.comboBox->addItems(groupList);
	ui.comboBox->setCurrentIndex(ui.comboBox->findText(entityData->GroupName));
}

void EntityDialog::updataEntityData()
{
	entityData->name=ui.lineEdit->text();
	entityData->EntityName=ui.lineEdit_2->text();
	entityData->MatName=ui.lineEdit_3->text();
	entityData->EntityType = ui.lineEdit_4->text();
	entityData->GroupName=ui.comboBox->itemText(ui.comboBox->currentIndex());
}
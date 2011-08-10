#include "ObjectEditor.h"

ObjectEditor::ObjectEditor(EntityTreeModel* model,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	objectData=new ObjectData("null");

	this->connect(ui.button_ok,SIGNAL(clicked(bool)),this,SLOT(okButton()));
	this->connect(ui.button_cancel,SIGNAL(clicked(bool)),this,SLOT(cancelButton()));

	this->model=model;
}

ObjectEditor::~ObjectEditor()
{
	delete objectData;
}	

void ObjectEditor::updataUI()
{
	ui.ObjectName->setText(objectData->name);
}

void ObjectEditor::updataEntityData()
{
	objectData->name=ui.ObjectName->text();
}

void ObjectEditor::okButton()
{
	if(model->getRootItem()->findItem(ui.ObjectName->text())!=NULL)
	{
		QMessageBox::critical(NULL,"错误","已经有该对象了!");
		return;
	}
	else
	{
		updataEntityData();
		accept();
	}
}

void ObjectEditor::cancelButton()
{
	reject();
}

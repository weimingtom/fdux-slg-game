#ifndef ENTITYDIALOG_H
#define ENTITYDIALOG_H

#include <QDialog>
#include <QStringList>
#include "ui_entitydialog.h"

#include "EntityTreeModel.h"
#include "EntityDataImp.h"

class EntityDialog : public QDialog
{
	Q_OBJECT

public:
	EntityDialog(QStringList groupList,EntityTreeModel* model,QWidget *parent = 0);
	~EntityDialog();

	void updataUI();
	void updataEntityData();
	
	EntityDataImp* entityData;

	bool isEditer;


public slots:
	void okButton();
	void cancelButton();

private:
	Ui::Dialog ui;
	EntityTreeModel* model;
};

#endif // ENTITYDIALOG_H

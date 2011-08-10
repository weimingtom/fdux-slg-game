#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H

#include <QDialog>
#include "ui_ObjectEditor.h"

#include "ObjectData.h"

class ObjectEditor : public QDialog
{
	Q_OBJECT

public:
	ObjectEditor(EntityTreeModel* model,QWidget *parent = 0);
	~ObjectEditor();

	void updataUI();
	void updataEntityData();

	ObjectData* objectData;

public slots:
	void okButton();
	void cancelButton();
private:
	Ui::ObjectEditorClass ui;

	EntityTreeModel* model;
};

#endif // OBJECTEDITOR_H

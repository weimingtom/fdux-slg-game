#ifndef NEWTERRAIN_H
#define NEWTERRAIN_H

#include <QDialog>
#include "ui_NewTerrain.h"

class NewTerrain : public QDialog
{
	Q_OBJECT

public:
	NewTerrain(QWidget *parent = 0);
	~NewTerrain();

	int GridSize;
	int MapGrids;

public slots:
	void okButton();
	void cancelButton();

private:
	Ui::NewTerrain ui;
};

#endif // NEWTERRAIN_H

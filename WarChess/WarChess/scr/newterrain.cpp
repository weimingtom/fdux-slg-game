#include "newterrain.h"

NewTerrain::NewTerrain(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->connect(ui.okButton,SIGNAL(clicked(bool)),this,SLOT(okButton()));
	this->connect(ui.cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButton()));
}

NewTerrain::~NewTerrain()
{

}

void NewTerrain::okButton()
{
	GridSize=ui.lineEdit_6->text().toInt();
	MapGrids=ui.lineEdit_7->text().toInt();
}

void NewTerrain::cancelButton()
{

}
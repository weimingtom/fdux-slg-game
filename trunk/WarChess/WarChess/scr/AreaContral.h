#pragma once

#include <QObject>
#include <QListView>

class AreaListModule;
class Area;

enum AreaControlState
{
	AREA_IDLE,
	AREA_ADD,
	AREA_DEL
};

class AreaControl : public QObject
{
	Q_OBJECT

public:
	AreaControl(QListView *listview);
	~AreaControl();
private:
	QListView *mAreaList;
	AreaListModule *mAreaListModule;

	Area* mArea;

	AreaControlState mState;

public slots:
	void mousePress(QMouseEvent * event);

	void AddArea();
	void DelArea();
	void CancelArea();
	void AddCoord();
	void DelCoord();

	void ChooseArea(const QModelIndex & index);
};
/*
 * 文件名:terraincontrol.h
 * 创建时间:2010:10:14   17:03
 * 编写者:winsock
 * 功能:  负责界面与地形系统的交互
 */

#ifndef TERRAINCONTROL_H
#define TERRAINCONTROL_H

#include <QObject>
#include <QMouseEvent>
#include <QMap>
#include <QAction>
#include <QListWidget>
#include <QComboBox>
#include <QTextEdit>

#include <vector>
#include <string>

#include "Common.h"

namespace Ui
{
	class MainWindow;
}

class TerrainSystem;

class TerrainControl : public QObject
{
	Q_OBJECT

public:
	TerrainControl(Ui::MainWindow *ui);
	~TerrainControl();

public slots:
	void Load_Terrain();
	void New_Terrain();

	void stateChanged(int state);
	void currentItemChanged( QListWidgetItem * current, QListWidgetItem * previous );

	void mouseMove(QMouseEvent * event);
	void mousePress(QMouseEvent * event);
	void mouseRelease(QMouseEvent * event);

private:

	void createEditor();//初始化Editor

	void initMapInfo();

	void createActions(std::vector<std::string> typelist,QListWidget* terrainList,EditorID editorId);//将动作添加到ListWidget里

	TerrainSystem* mTerrainSystem;

	QListWidget* mTerrainList;

	QLineEdit* mMapName;
	QLineEdit* mTeam2Faction;
	QLineEdit* mTeam3Faction;
	QLineEdit* mTeam4Faction;
	QComboBox* mTeam2Relation;
	QComboBox* mTeam3Relation;
	QComboBox* mTeam4Relation;
	QLineEdit* mMapScript;
	QTextEdit* mMapInfo;
	QLineEdit* mMapBG;

	bool mEnable;
};

#endif // TERRAINCONTROL_H

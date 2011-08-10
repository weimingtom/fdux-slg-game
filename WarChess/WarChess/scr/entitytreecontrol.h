/*
 * 文件名:entitytreecontrol.h
 * 创建时间:2010:10:28   16:57
 * 编写者:winsock
 * 功能: EntityTree控制器,负责外部交互
 */

#ifndef ENTITYTREECONTROL_H
#define ENTITYTREECONTROL_H

#include <QObject>
#include <QTreeView>
#include <Ogre.h>

#include "EntityTreeModel.h"

class ObjcetControl;

class TerrainSystem;

class EntityDataImp;

class EntityTreeControl : public QObject
{
	Q_OBJECT

public:
	EntityTreeControl(QTreeView* treeView,ObjcetControl* objectControl);
	~EntityTreeControl();

	void open(QString filename);
	void save(QString filename);
	bool addGroup(QString name);
	bool removeGroup(QString name);

public slots:
	void addEntity();
	void removeEntity();

	void mouseMove(QMouseEvent * event);//接收来自渲染窗口的鼠标消息
	void mousePress(QMouseEvent * event);
	void mouseRelease(QMouseEvent * event);

	void selectEntity(const QModelIndex & index );//当用户选择某EntityItem时
private:
	void LoadXML(QDomDocument doc);//将xml载入到树中
	QDomDocument SaveXML();//把树保存回xml
	void cancelSelect();//取消选择

	QTreeView* mTreeView;
	EntityTreeModel* mEntityTreeModel;
	ObjcetControl* mObjectControl;
	Ogre::SceneNode* mSelectNode;//已经有选中的项
	Ogre::Entity* mSelectEntity;//节点使用的实体
	EntityDataImp* mEntityItemData;//选中的项包含的数据
	Ogre::SceneManager* mSceneManager;
	TerrainSystem* mTerrain;
	
};

#endif // ENTITYTREECONTROL_H

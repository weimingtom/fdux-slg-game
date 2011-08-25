#ifndef OBJCETCONTROL_H
#define OBJCETCONTROL_H

#include <QObject>
#include <QTreeView>
#include <QMouseEvent>
#include <QAction>
#include <QInputDialog>

#include <Ogre.h>

#include "EntityTreeModel.h"
#include "CollisionTools.h"

class ObjectData;

class AttributeControl;

class ObjcetControl : public QObject
{
	Q_OBJECT

public:
	ObjcetControl(QTreeView* treeView,AttributeControl* attribute);
	~ObjcetControl();

	void addObject(QString name,QString groupName,QString entityType,Ogre::SceneNode* objcetNode,Ogre::Entity* objectEntity, const QMap<QString, QString>& attrMap);//添加一个场景对象到场景中,仅允许从实体中创造

	QAction* mMoveAction;
	QAction* mRotateAction;
	QAction* mScaleAction;

public slots:
	void removeObject();//移除一个场景实例

	void addObjectGroup();//添加一个对象组
	void removeObjectGroup();//移除一个对象组

	void mouseMove(QMouseEvent * event);//接收来自渲染窗口的鼠标消息
	void mousePress(QMouseEvent * event);
	void mouseRelease(QMouseEvent * event);
	void cameraMove(float x,float y,float z);

	void moveAction(bool checked);//界面上对应的3个按钮
	void rotateAction(bool checked);
	void scaleAction(bool checked);
	void moveLockAction(bool checked);
	void scaleLockAction(bool checked);

	void attributeChangle(QString name,QString value);

private:
	AttributeControl* mAttribute;//属性面板控制对象

	EntityTreeModel* mObjectModel;//数据模型
	QTreeView* mTreeView;//数据视图

	float mLastX,mLastY;//上一次鼠标位置

	ObjectData* mSelectObject;//当前选择的对象

	enum ObjectEditMode//对象的编辑模式
	{
		NoneEdit,
		Move,
		Rotate,
		Scale
	};

	enum ArrowType//对象的编辑模式
	{
		NoneArrow,
		ArrowX,
		ArrowY,
		ArrowZ
	};
	
	ObjectEditMode mEditMode;
	
	Ogre::SceneManager* mSceneManager;
	Ogre::RenderWindow* mWindow;
	Ogre::Camera* mCamera;
	Ogre::RaySceneQuery* mRaySceneQuery;
	MOC::CollisionTools* mCollisionTools;
	Ogre::SceneNode* mArrowNode;//箭头节点
	Ogre::SceneNode* mArrowXNode;//箭头X节点
	Ogre::SceneNode* mArrowYNode;//箭头Y节点
	Ogre::SceneNode* mArrowZNode;//箭头Z节点
	Ogre::Entity* mArrowXEntity;//X箭头
	Ogre::Entity* mArrowYEntity;//Y箭头
	Ogre::Entity* mArrowZEntity;//Z箭头

	
	void moveObject(Ogre::Vector3 tagetPos);//移动当前选择对象
	void rotateObject(int mouseY);//旋转当前选择对象
	void scaleObject(int mouseY);//缩放当前选择对象
	void createAssistPlane(ArrowType type,Ogre::Vector3 pos);//创建移动辅助平面
	void setAttribute();//将选中的对象的属性设置到属性面板上;
	Ogre::Plane* mAssistPlane;//轴移动辅助对象
	Ogre::Vector3 mLastPosition;//上一次的位置
	bool mMoveLocked;//是否移动的时候对齐到网格
	bool mScaleLocked;//是否使用全轴缩放
	int mLastMouseY;//上一次鼠标Y轴
	ArrowType mPressArrow;//当前按下的轴

	void setArrowStyle();//设置箭头的样式

	EntityTreeItem* findEntity(const QModelIndex& index,const Ogre::Entity* entity);//递归匹配实体

};

#endif // OBJCETCONTROL_H

#include "entitytreecontrol.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "entityitemdelegate.h"
#include "entitydialog.h"
#include "IIRoot.h"

EntityTreeControl::EntityTreeControl(QTreeView* treeView,ObjcetControl* objectControl):mTreeView(treeView),mSelectEntity(NULL),mTerrain(IIRoot::getSingletonPtr()->mTerrain),mObjectControl(objectControl)
{
	//创建模型类,将模型设置到视图上,并将我们自己的编辑器类关联到视图上
	mEntityTreeModel=new EntityTreeModel();
	mTreeView->setModel(mEntityTreeModel);
	EntityItemDelegate* entitiyItemDelegate=new EntityItemDelegate(NULL);
	entitiyItemDelegate->entityTreeModel=mEntityTreeModel;
	entitiyItemDelegate->treeView=mTreeView;
	mTreeView->setItemDelegate(entitiyItemDelegate);

	open("Entity.xml");//载入默认列表	
	
	mSceneManager=IIRoot::getSingletonPtr()->mSceneMgr;
	mSelectNode=mSceneManager->getRootSceneNode()->createChildSceneNode();//创建放置模型使用的节点
	mSelectNode->setPosition(0,-1000,0);
}

EntityTreeControl::~EntityTreeControl()
{
	//退出时,保存列表;
	save("Entity.xml");
}

bool EntityTreeControl::addGroup(QString name)
{
	EntityTreeItem* rootItem=mEntityTreeModel->getRootItem();

	if(rootItem->findItem(name)!=NULL)
	{
		return false;
	}

	rootItem->appendChild(new EntityTreeItem(new EntityDataImp(name),rootItem,EntityItemType::Group));

	mTreeView->reset();//改变数据后,记得通知view刷新

	return true;
}

bool EntityTreeControl::removeGroup(QString name)
{
	EntityTreeItem* rootItem=mEntityTreeModel->getRootItem();

	if(rootItem->findItem(name)!=NULL)
	{
		EntityTreeItem* childItem=rootItem->findItem(name);
		if(childItem->entityItemType==EntityItemType::Group)
		{
			mEntityTreeModel->removeRow(childItem->row());
			childItem->parent()->removeChild(childItem);		
			mTreeView->reset();//改变数据后,记得通知view刷新
			delete childItem;//切记!必须要让view刷新后,才能delete数据项
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}


}

void EntityTreeControl::addEntity()
{

	QStringList groupList;

	for(int i=0;i<mEntityTreeModel->getRootItem()->childCount();i++)//生成组列表
	{
		groupList.append(mEntityTreeModel->getRootItem()->child(i)->data(0)->name);//从root读取下面的子节点(就是组)
	}

	if(groupList.isEmpty())
	{
		QMessageBox::information(NULL,"错误","没有组,请先建立一个组");
		return ;
	}

	EntityDialog dialog(groupList,mEntityTreeModel);
	dialog.exec();
	int result=dialog.result();

	if(result==QDialog::Accepted)
	{
		EntityTreeItem* groupItem=mEntityTreeModel->getRootItem()->findItem(dialog.entityData->GroupName);//得到组节点
		groupItem->appendChild(new EntityTreeItem(new EntityDataImp(*dialog.entityData),groupItem,EntityItemType::Entity));
		mTreeView->reset();//改变数据后,记得通知view刷新
		mTreeView->expand(mEntityTreeModel->index(groupItem->row(),0));//展开对应的组
	}

}

void EntityTreeControl::removeEntity()
{
	QItemSelectionModel* selectionModel =mTreeView->selectionModel();
	QModelIndex selectionIndex=selectionModel->currentIndex();

	if(selectionIndex.isValid())
	{
		EntityTreeItem* childItem=static_cast<EntityTreeItem*>(selectionIndex.internalPointer());
		if(childItem->entityItemType==EntityItemType::Entity)
		{
			QMessageBox::StandardButton button=QMessageBox::information(NULL,"提示","真的要删除该实体?",(QMessageBox::Yes | QMessageBox::No));
			if(button==QMessageBox::Yes)
			{
				if (childItem->data(0)==mEntityItemData)//如果当前选中的项要被删除,则进行清理
				{
					cancelSelect();
				}

				mEntityTreeModel->removeRow(selectionIndex.row());
				childItem->parent()->removeChild(childItem);		
				mTreeView->reset();//改变数据后,记得通知view刷新
				delete childItem;//切记!必须要让view刷新后,才能delete数据项
			}
		}
	}
}

void EntityTreeControl::open(QString filename)
{
	if(filename!="")
	{
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(NULL,"错误","无法打开文件!");
			return ;
		}
		QString XMLStr=QTextStream(&file).readAll();
		file.close();

		QDomDocument doc;
		QString errorStr;
		int errorLine;
		int errorCol;
		if(!doc.setContent(XMLStr,false,&errorStr,&errorLine,&errorCol))
		{
			QMessageBox::critical(NULL,"错误",QString("XML解析失败!errorLine=%1,errorCol=%2,errorStr=%3").arg(errorLine).arg(errorCol).arg(errorStr));
			return;
		}
		LoadXML(doc);
	}
}

void EntityTreeControl::save(QString filename)
{
	if(filename!="")
	{
		QDomDocument doc=SaveXML();
		QString XMLStr=doc.toString();
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly))
		{
			QMessageBox::critical(NULL,"错误","无法打开文件!");
			return ;
		}
		QTextStream stream(&file);
		stream<<"<?xml version=\"1.0\" encoding=\"GB2312\"?>";
		stream<<"\n";
		stream<<XMLStr;
		file.close();
	}
}

void EntityTreeControl::LoadXML(QDomDocument doc)//将xml载入到树中
{
	QList<EntityTreeItem*> childItems;
	EntityTreeItem* rootItem=mEntityTreeModel->getRootItem();
	for(int i=0;i<rootItem->childCount();i++)
	{
		childItems.append(rootItem->child(i));
		rootItem->removeChild(rootItem->child(i));
	}
	mTreeView->reset();
	qDeleteAll(childItems);

	QDomElement root=doc.documentElement();

	QDomElement groupList=root.firstChildElement("GroupList");

	QDomElement entityList=root.firstChildElement("EntityList");

	QDomElement group=groupList.firstChildElement();

	while(!group.isNull())
	{
		rootItem->appendChild(new EntityTreeItem(new EntityData(group.attribute("name")),NULL,EntityItemType::Group));
		group=group.nextSiblingElement();
	}

	QDomElement entity=entityList.firstChildElement();
	while(!entity.isNull())
	{
		EntityTreeItem* groupItem=rootItem->findItem(entity.attribute("group"));
		EntityDataImp* entityData=new EntityDataImp(entity.attribute("name"));
		entityData->GroupName=entity.attribute("group");
		entityData->EntityName=entity.attribute("entity");
		entityData->MatName=entity.attribute("mat");
		entityData->EntityType = entity.attribute("type");
		groupItem->appendChild(new EntityTreeItem(static_cast<EntityData*>(entityData),groupItem,EntityItemType::Entity));
		entity=entity.nextSiblingElement();
	}

}

QDomDocument EntityTreeControl::SaveXML()
{
	QDomDocument doc;

	QDomElement root=doc.createElement("Root");

	QDomElement groupList=doc.createElement("GroupList");

	QDomElement entityList=doc.createElement("EntityList");

	EntityTreeItem* rootItem=mEntityTreeModel->getRootItem();

	doc.appendChild(root);
	root.appendChild(groupList);
	root.appendChild(entityList);

	for(int i=0;i<rootItem->childCount();i++)
	{
		QDomElement group=doc.createElement("Group");
		group.setAttribute("name",rootItem->child(i)->data(0)->name);
		groupList.appendChild(group);

		for(int j=0;j<rootItem->child(i)->childCount();j++)
		{
			QDomElement entity=doc.createElement("Entity");
			EntityDataImp* entityData=static_cast<EntityDataImp*>(rootItem->child(i)->child(j)->data(0));
			entity.setAttribute("name",entityData->name);
			entity.setAttribute("group",entityData->GroupName);
			entity.setAttribute("entity",entityData->EntityName);
			entity.setAttribute("mat",entityData->MatName);
			entity.setAttribute("type",entityData->EntityType);
			entityList.appendChild(entity);
		}
	}

	return doc;
}

void EntityTreeControl::selectEntity( const QModelIndex & index )
{
	if (index.isValid())
	{
		EntityTreeItem* item = static_cast<EntityTreeItem*>(index.internalPointer());

		if (item->entityItemType!=Group)
		{
			EntityDataImp* entityData=static_cast<EntityDataImp*>(item->data(0));
			mEntityItemData=entityData;

			if (Ogre::ResourceGroupManager::getSingletonPtr()->resourceExistsInAnyGroup(entityData->EntityName.toLocal8Bit().data()))
			{		
				mEntityTreeModel->setSelectItem(index);
				if (mSelectEntity!=NULL)
				{
					mSelectNode->detachObject(mSelectEntity);
					mSceneManager->destroyEntity(mSelectEntity);
				}
				mSelectEntity=mSceneManager->createEntity(entityData->EntityName.toLocal8Bit().data());
				mSelectEntity->setMaterialName(entityData->MatName.toLocal8Bit().data());
				mSelectNode->attachObject(mSelectEntity);
				mSelectNode->setPosition(0,-1000,0);//初始时移动到一个看不到的地方
			}
			else//如果mesh不存在
			{
				QMessageBox::warning(NULL,"错误",QString("%1 不存在!").arg(entityData->EntityName));
				mTreeView->openPersistentEditor(index);
			}
		}
	}
	else//表示清空选择
	{
		mEntityTreeModel->setSelectItem(index);
	}
	
}

void EntityTreeControl::mouseMove( QMouseEvent * event )
{
	if (mSelectEntity!=NULL && mTerrain->isInit())
	{
		int GX,GY;
		if (mTerrain->coordinateToGrid(event->x(),event->y(),&GX,&GY))
		{
			Ogre::Vector2 v=mTerrain->getRealXY(GX,GY,SecGrid);
			float height=mTerrain->getHeight(GX,GY);
			mSelectNode->setPosition(v.x,height,v.y);
		}
	}
}

void EntityTreeControl::mousePress( QMouseEvent * event )
{
	if (mSelectEntity!=NULL && mTerrain->isInit())
	{
		if (event->button()==Qt::MouseButton::LeftButton)
		{
			//这里要做几件事情
			//1.复制一个节点
			Ogre::SceneNode* node=mSceneManager->getRootSceneNode()->createChildSceneNode();
			node->setPosition(mSelectNode->getPosition());
			//2.把实体也复制一个
			Ogre::Entity* entity=mSceneManager->createEntity(mEntityItemData->EntityName.toLocal8Bit().data());
			entity->setQueryFlags(DEFAULT_QUERY_MARK);
			entity->setMaterialName(mEntityItemData->MatName.toLocal8Bit().data());
			node->attachObject(entity);
			//3.将信息提交到ObjctControl
			QMap<QString, QString> map;
			mObjectControl->addObject(mEntityItemData->name,mEntityItemData->GroupName,mEntityItemData->EntityType,node,entity,map);

		}
		else if (event->button()==Qt::MouseButton::RightButton)
		{
			cancelSelect();//右键取消选择
		}

	}
}

void EntityTreeControl::mouseRelease( QMouseEvent * event )
{

}

void EntityTreeControl::cancelSelect()
{
	mSelectNode->detachObject(mSelectEntity);
	mSceneManager->destroyEntity(mSelectEntity);
	mSelectEntity=NULL;
	mEntityItemData=NULL;
	selectEntity(QModelIndex());
}

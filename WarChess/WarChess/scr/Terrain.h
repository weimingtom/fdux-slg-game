/*
 * 文件名:Terrain.h
 * 创建时间:2010:10:14   16:10
 * 编写者:winsock
 * 功能:地形系统,这个类包括了全部的地形的管理
 */

#pragma once

#include <Ogre.h>

#include <map>

#include "Grid.h"
#include "TerrainBlock.h"
#include "Common.h"
#include "TerrainEditor.h"

class TerrainSystem
{
public:
	TerrainSystem(Ogre::SceneManager* sceneManager,Ogre::RenderWindow* renderWindow,Ogre::Camera* camera);
	~TerrainSystem(void);
	
	//初始化地形系统,GridSize:网格总大小,BlockSize:每个网格的大小
	void initTerrain(int GridSize,int BlockSize);

	//来着外部的点击事件,注意此处接受的是屏幕2d的坐标
	void mouseMove(float x,float y);
	void mousePress(float x,float y,MouseButton button);
	void mouseRelease(float x,float y,MouseButton button);

	TerrainEditor* addEditor(EditorID id,GridID gridID);//添加一个编辑器到系统中来,gridID指明使用主网格还是用副网格
	void deleteEditor(EditorID id);//删除一个编辑器
	TerrainEditor* getEditor(EditorID id);//获取编辑器
	void setCurrentEditor(EditorID id);//设置当前的编辑器
	void setCurrentGridCursorVisible(bool show);//设置某个光标的显隐

	void updateGridHeight(GridID gridID);//更新网格的高度

	//提供一个对外的接口,用于查询当前鼠标在哪一格,使用副网格
	bool coordinateToGrid(float x,float y,int* GX,int* GY);
	
	//提供一个对外的接口,用于查询某个坐标在哪一格,使用副网格
	void calculateGrid(float x,float y,int* GX, int* GY );

	//从网格格子转换回实际的中心坐标;
	Ogre::Vector2 getRealXY(int GX,int GY,GridID gridId);

	//获取网格的大小
	int getGridSize();
	float getBlockSize();

	//获取某格高度
	float getHeight(int GX,int GY);

	bool isInit();//是否初始化

	TerrainBlock* mTerrainBlocks[MAX_MAPSIZE][MAX_MAPSIZE];//地形块数据集合

	RampManager* mRamp;	

private:

	//转换二维屏幕x,y坐标到网格坐标上,返回值表示是否成功
	bool coordinateToGrid(float x,float y,int* GX,int* GY,Grid* grid);

	//计算坐标在哪一格
	void calculateGrid(float x,float y,int* GX, int* GY, Grid* grid );

	//创建大平面
	Ogre::MeshPtr createPlane(int gridSize,int blockSize);

	//初始化大平面
	void initPlaneVertex(int gridSize,int blockSize,Ogre::MeshPtr mesh);

	bool mIsInit;//是否初始化
	Grid* mMGrid;//主网格系统
	Grid* mSGrid;//副网格系统
	Ogre::SceneManager* mSceneManager;//Ogre场景
	Ogre::Camera* mCamera;//Ogre主摄像机
	Ogre::RenderWindow* mWindow;//渲染窗口
		

	enum MouseState//鼠标状态枚举
	{
		MouseRelease,
		MousePress
	};

	MouseState mMouseState;//鼠标状态

	std::map<TerrainEditor*,GridID> mEditors;//Editor与GridId的对应关系

	TerrainEditor* mCurrentEditor;//当前激活的编辑器
	Grid* mCurrentGrid;//当前激活的编辑器对应的网格指针

	Ogre::SceneNode* mPlaneNode;//模型节点
	Ogre::Entity* mPlaneEntity;//地面实体
	Ogre::MeshPtr mMesh;//地面网格指针

	Ogre::Entity* mWaterEntity;//测试水面
	Ogre::SceneNode* mWaterNode;//测试水面节点

};

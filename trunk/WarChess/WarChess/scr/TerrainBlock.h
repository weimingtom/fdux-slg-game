#pragma once

#include <Ogre.h>
#include <string>

#include "Common.h"

class TerrainBlock
{
public:
	TerrainBlock(int GX,int GY,float X,float Y,int gridSize,int blockSize,Ogre::SceneManager* sceneManager,Ogre::MeshPtr planeMesh);
	~TerrainBlock(void);

	void setTerrainAsMesh(std::string name, int angle);
	void setTerrainAsPlane(float height);
	void setMeshMaterial(std::string name);
	void setPlaneMaterial(GroundType trrianType, ConerType coner);

	void removeMesh();
	void removeMat();

	void getTileName();//返回该块的名字

	bool isPlane();

	BlockType getBlockType(); //返回当前的地形块类型
	BlockType getBlockType(ConerType coner); //返回当前的地形块一个角的类型
	int getBlockMeshIndex(); //返回当前地形块模型使用的编号
	GroundType getTerrianType(ConerType coner);//返回当前模型使用的地图贴图类型
	void setBlockType(BlockType blokType, GroundType terrianType, int index);//设置地形块类型,设定好模型后调用

	void _updateTile(float* pBufferPos , float* pBufferUV , bool bUpdatePos,bool bUpdateUV);//仅供Terrain初始化的时候允许外部调用

	int mGridX;//在逻辑网格上的X
	int mGridY;//在逻辑网格上的Y

	float mX;//左上角X坐标
	float mY;//左上角Y坐标

	float mHeight;//地块高度
	int mGridSize;//地图每行块数
	int mBlockSize;//每一块的大小

private:
	Ogre::SceneNode* mBlockNode;//模型节点
	Ogre::Entity* mBlockEntity;//地形块实体对象
	Ogre::MeshPtr mPlaneMesh;//大平面的网格指针
	std::string mTileName;//地形块名称
	GroundType mConerTerrian[4];//每一层对应的贴图类型
	Ogre::SceneManager* mSceneManager;//场景管理器

	bool mPlane;//是否为平地

	int mAngle;//模型的旋转角度

	BlockType mBlockType;//当前地形块的类型
	int mIndex; //模型使用的编号，同平地计算拼接的方法
	
	void updatePos(float* pBufferPos);
	void updateUV(float* pBufferUV);
	void WriteConerTexCoords(float* pos, int index, int coner);
};

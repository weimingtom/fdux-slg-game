#pragma once

#include "Core.h"
#include "iisingleton.hpp"
using namespace izayoi;
#include "CollisionTools.h"

#include <vector>
#include <map>

class MapDataManager;

static const float PLANEHEIGHT = 0.0f;
static const float TILESIZE = 16.0f;
static const float HEIGHGROUNDHEIGHT = 5.0f;
static const float WATERHEIGHT = -1.0f;
static const float WATERDEEP = -2.0f;


static const int VERTEX_POS_BINDING=0;//顶点位置绑定位置
static const int VERTEX_NOM_BINDING=1;
static const int VERTEX_UV_BINDING=2;//贴图坐标绑定位置
static const int TEXTURE_COUNT=4;//贴图坐标数
static const int VERTEX_QUAD = 4;//每一个地形块拥有的顶点数
static const int VERTEX_PREQUAD = 6;//每一个地形块的索引数

static const int TOPLEFT = 0;
static const int TOPRIGHT = 1;
static const int BOTTOMLEFT = 2;
static const int BOTTOMRIGHT = 3;

static const float TERRAINTEXSIZE = 256.0f;
static const float TERRAINTEXTILESIZE = 64.0f;

static const Ogre::uint32 TERRAIN_MASK = 1 << 0;
static const Ogre::uint32 GRID_MASK = 1 << 2;

class Terrain:public IISingleton<Terrain>,public Ogre::RenderTargetListener
{
public:
	Terrain();
	~Terrain();
	
	bool createTerrain();
	void destoryTerrian();

	void createGrid();

	//提供一个对外的接口,用于查询当前鼠标在哪一格
	bool coordinateToGrid(float x,float y,int& GX,int& GY);

	//计算格子的实际坐标
	void getWorldCoords(int x, int y, float &wx, float &wy);
	
	//计算坐标对应的格子
	void calculateGrid(float x,float y,int& GX, int& GY);
	
	//获取格子的高度
	float getHeight(float x, float y);
	
	int createMapObj(int x, int y, std::string meshname);
	void deleteMapObj(int index);

	int createMapParticle(int x, int y,std::string particlename);
	void deleteMapParticle(int index);

	void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
	void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
private:

	MOC::CollisionTools* mCollisionTools;

	Ogre::SceneNode* mTerrainNode;
	Ogre::Entity* mTerrainEntity;
	Ogre::MeshPtr mTerrainMesh;

	Ogre::SceneNode* mWaterNode;
	Ogre::ManualObject* mWaterObject;

	Ogre::SceneNode* mGridNode;
	Ogre::ManualObject* mGrid;

	Ogre::Light* mLight;

	struct stTileEntityData
	{
		Ogre::SceneNode* mTileNode;
		Ogre::Entity* mTileEntity;
	};
	std::vector<stTileEntityData *> mTileEntityVector;
	std::map<int, stTileEntityData*> mMapObjMap;
	int mObjId;

	struct stTilePUData
	{
		Ogre::SceneNode* mTileNode;
		ParticleUniverse::ParticleSystem* mTileParticle;
	};
	std::map<int, stTilePUData*> mMapPUMap;
	int mPUId;

	MapDataManager *mMapData;

	void createTile(int x, int y,float sx, float sy, float *posbuffer, float *uvbuffer, float *nombuffer);
	std::string randMesh(int x, int y);

	Ogre::Plane mWaterPlane;
	Ogre::RenderTarget* mReflectionTarget;
	Ogre::RenderTarget* mShadowDepthMapTarget;
};
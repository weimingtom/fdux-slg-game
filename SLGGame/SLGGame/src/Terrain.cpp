#include "Terrain.h"

#include "MapDataManager.h"
#include "SquadGrapManager.h"
#include "CameraContral.h"
#include "DataLibrary.h"

#include <iostream>

Terrain::Terrain()
{
	mCollisionTools = new MOC::CollisionTools(Core::getSingleton().mSceneMgr);
	mObjId = 0;
	mPUId = 0;
	mGridNode = NULL;
	mMainViewport = NULL;
}

Terrain::~Terrain()
{
	destoryTerrian();
}

bool Terrain::createTerrain()
{

	if(mMainViewport == NULL) 
		mMainViewport = Core::getSingleton().mCamera->getViewport();
	Ogre::CompositorManager::getSingleton().addCompositor(mMainViewport, "DemoCompositor");
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mMainViewport, "DemoCompositor", true);

	mMapData = MapDataManager::getSingletonPtr();
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int terrainszie = mMapData->getMapSize() + 2 * MAPBOLDER + 1;

	Core::getSingleton().mSceneMgr->setSkyBox(true, "SkyBox",200);



	//创建灯光
	Core::getSingleton().mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	mLight = Core::getSingleton().mSceneMgr->createLight("TerrainLight");
	mLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mLight->setPosition(-500.0f,500.0f, 500.0f);
	mLight->setDirection(1.0f, -1.0f, -1.0f);
	mLight->setDiffuseColour(Ogre::ColourValue(0.6f, 0.6f,0.6f));
	mLight->setSpecularColour(Ogre::ColourValue(1.0f, 1.0f,1.0f));

	//设置深度图投影
	Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("shadowdepthmap");
	if(tex.isNull())
		tex = Ogre::TextureManager::getSingleton().createManual("shadowdepthmap",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 1024, 1024, 0, Ogre::PF_FLOAT16_R, Ogre::TU_RENDERTARGET);
	mShadowDepthMapTarget = tex->getBuffer()->getRenderTarget();
	Ogre::Viewport* vp = mShadowDepthMapTarget->addViewport(CameraContral::getSingleton().getShadowMapCamera());
	vp->setSkiesEnabled(false);
	vp->setOverlaysEnabled(false);
	vp->setVisibilityMask(VISMASK_OPAQUE);
	vp->setMaterialScheme("WriteDepthMap");
	vp->setBackgroundColour(Ogre::ColourValue(1.0f,1.0f,1.0f));
	mShadowDepthMapTarget->addListener(this);
	//弱爆了……
	Ogre::MaterialPtr mat;
	mat = Ogre::MaterialManager::getSingleton().getByName("TerrainTile");
	Ogre::AliasTextureNamePairList texAliasList;
	std::string texname;
	datalib->getData("GameData/BattleData/MapData/Ground/G0Tex",texname);
	texAliasList.insert(std::make_pair("Diffuse",texname));
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse",texname));
	datalib->getData("GameData/BattleData/MapData/Ground/G1Tex",texname);
	texAliasList.insert(std::make_pair("Diffuse1",texname));
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse1",texname));
	datalib->getData("GameData/BattleData/MapData/Ground/G2Tex",texname);
	texAliasList.insert(std::make_pair("Diffuse2",texname));
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse2",texname));
	datalib->getData("GameData/BattleData/MapData/Ground/G3Tex",texname);
	texAliasList.insert(std::make_pair("Diffuse3",texname));
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse3",texname));
	mat->applyTextureAliases(texAliasList);
	texAliasList.clear();

	mat = Ogre::MaterialManager::getSingleton().getByName("CliffMat1");
	datalib->getData("GameData/BattleData/MapData/Ground/G0Tex",texname);
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse1","Cliff.dds"));
	mat->applyTextureAliases(texAliasList);
	texAliasList.clear();

	mat = Ogre::MaterialManager::getSingleton().getByName("CliffMat2");
	datalib->getData("GameData/BattleData/MapData/Ground/G1Tex",texname);
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse1","Cliff.dds"));
	mat->applyTextureAliases(texAliasList);
	texAliasList.clear();

	mat = Ogre::MaterialManager::getSingleton().getByName("CliffMat3");
	datalib->getData("GameData/BattleData/MapData/Ground/G2Tex",texname);
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse1","Cliff.dds"));
	mat->applyTextureAliases(texAliasList);
	texAliasList.clear();

	mat = Ogre::MaterialManager::getSingleton().getByName("CliffMat4");
	datalib->getData("GameData/BattleData/MapData/Ground/G3Tex",texname);
	//mat->applyTextureAliases(Ogre::AliasTextureNamePairList("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse",texname));
	texAliasList.insert(std::make_pair("Diffuse1","Cliff.dds"));
	mat->applyTextureAliases(texAliasList);
	texAliasList.clear();

	//创建地面Mesh
	mTerrainNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode("TerrainNode");

	int numVertices = terrainszie * terrainszie * VERTEX_QUAD;
	int numIndex = terrainszie * terrainszie * VERTEX_PREQUAD;
	mTerrainMesh = Ogre::MeshManager::getSingleton().createManual("TerrianMesh",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::SubMesh* subMesh  = mTerrainMesh->createSubMesh();
	subMesh->useSharedVertices=false;
	subMesh->setMaterialName("TerrainTile");

	// 创建顶点数据结构
	subMesh->vertexData = new Ogre::VertexData();
	subMesh->vertexData->vertexStart = 0;
	subMesh->vertexData->vertexCount = numVertices;

	//顶点声明与缓冲区绑定
	Ogre::VertexDeclaration* vdecl = subMesh->vertexData->vertexDeclaration;
	Ogre::VertexBufferBinding* vbind = subMesh->vertexData->vertexBufferBinding;

	//设置顶点数据结构
	size_t offsetUV = 0;
	vdecl->addElement(VERTEX_POS_BINDING, 0, Ogre::VET_FLOAT3,Ogre::VES_POSITION);//向顶点添加一个位置元素
	vdecl->addElement(VERTEX_NOM_BINDING, 0, Ogre::VET_FLOAT3,Ogre::VES_NORMAL);
	for(int i = 0 ; i < TEXTURE_COUNT ; i ++)
	{
		offsetUV += vdecl->addElement (VERTEX_UV_BINDING, offsetUV, Ogre::VET_FLOAT2,  Ogre::VES_TEXTURE_COORDINATES , i).getSize();
	}

	// 创建世界坐标顶点缓冲区
	Ogre::HardwareVertexBufferSharedPtr vbufPos =
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		vdecl->getVertexSize(VERTEX_POS_BINDING),
		numVertices,
		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
	vbind->setBinding(VERTEX_POS_BINDING, vbufPos);

	Ogre::HardwareVertexBufferSharedPtr vbufNOM =
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		vdecl->getVertexSize(VERTEX_NOM_BINDING),
		numVertices,
		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
	vbind->setBinding(VERTEX_NOM_BINDING, vbufNOM);

	// 创建纹理坐标顶点缓冲区
	Ogre::HardwareVertexBufferSharedPtr vbufUV =
		Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
		vdecl->getVertexSize(VERTEX_UV_BINDING),
		numVertices,
		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
	vbind->setBinding(VERTEX_UV_BINDING, vbufUV);

	// 创建索引缓冲区
	Ogre::HardwareIndexBufferSharedPtr indexBuffer =
		Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
		Ogre::HardwareIndexBuffer::IT_16BIT ,
		numIndex,
		Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	//创建地形
	float* pBufferPos = (float*)vbufPos->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	float* pBufferUV = (float*)vbufUV->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	float* pBufferNom = (float*)vbufNOM->lock(Ogre::HardwareBuffer::HBL_DISCARD);

	float startpos = - terrainszie * TILESIZE / 2;
	for(int y = 0 ; y < terrainszie; y ++)
	{
		for(int x = 0 ; x < terrainszie; x ++)
		{
			createTile(x, y, startpos + x * TILESIZE, startpos + y * TILESIZE, pBufferPos, pBufferUV, pBufferNom);
			pBufferPos += 3 * VERTEX_QUAD ;
			pBufferNom += 3 * VERTEX_QUAD ;
			pBufferUV += 2 * VERTEX_QUAD * 4;
		}
	}

	vbufNOM->unlock();
	vbufUV->unlock();
	vbufPos->unlock();

	//写入索引信息
	// 锁定索引缓冲区
	Ogre::ushort* pIdx = (Ogre::ushort*)indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);
	for(int y = 0 ; y < terrainszie ; y ++)
	{
		for(int x = 0 ; x < terrainszie ; x ++)
		{
			Ogre::ushort iIndexTopLeft = (x + y * terrainszie) * VERTEX_QUAD;
			Ogre::ushort iIndexTopRight = iIndexTopLeft + 1;
			Ogre::ushort iIndexBottomLeft = iIndexTopLeft + 2;
			Ogre::ushort iIndexBottomRight = iIndexTopLeft + 3;
			*pIdx++ = iIndexBottomLeft;
			*pIdx++ = iIndexBottomRight;
			*pIdx++ = iIndexTopLeft;

			*pIdx++ = iIndexBottomRight;
			*pIdx++ = iIndexTopRight;
			*pIdx++ = iIndexTopLeft;
		}
	}
	indexBuffer->unlock();
	//设置模型的的索引数据
	subMesh->indexData->indexBuffer = indexBuffer;
	subMesh->indexData->indexStart = 0;
	subMesh->indexData->indexCount =numIndex;

	Ogre::AxisAlignedBox meshBounds(startpos,0,startpos,
		-startpos,5,-startpos);
	mTerrainMesh->_setBounds(meshBounds);

	mTerrainEntity = Core::getSingleton().mSceneMgr->createEntity("TerrianMesh");
	mTerrainNode->attachObject(mTerrainEntity);
	mTerrainEntity->setQueryFlags(QUERYMASK_TERRAIN);
	mTerrainNode->setPosition(0,0,0);

	//创建水面
	tex = Ogre::TextureManager::getSingleton().getByName("reflection");
	if(tex.isNull())
		tex = Ogre::TextureManager::getSingleton().createManual("reflection",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 512, 512, 0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);
	mReflectionTarget = tex->getBuffer()->getRenderTarget();
	mReflectionTarget->addViewport(Core::getSingleton().mCamera)->setOverlaysEnabled(false);
	mReflectionTarget->addListener(this);
// 	mat = Ogre::MaterialManager::getSingleton().getByName("ReflectionWater");
// 	tech = mat->getTechnique(0);
// 	pass = tech->getPass(0);
// 	tu =  pass->getTextureUnitState(1);
// 	tu->setTextureName(tex->getName());

	mWaterPlane = Ogre::Plane(Ogre::Vector3::UNIT_Y, WATERHEIGHT);

	mWaterNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode("WaterNode");
	mWaterObject = Core::getSingleton().mSceneMgr->createManualObject("WaterObject");

	mWaterObject->begin("DemoWater",Ogre::RenderOperation::OT_TRIANGLE_LIST);
	startpos += TILESIZE/2;
	for(int y = 0; y < terrainszie; y++)
		for(int x = 0; x < terrainszie; x++)
		{
			if(mMapData->getTerrainType(x -MAPBOLDER, y -MAPBOLDER ) == Water)
			{
				mWaterObject->position(startpos + x * TILESIZE, 0.0f, startpos + y * TILESIZE);
				mWaterObject->colour(1.0f,1.0f,1.0f);
				mWaterObject->normal(0.0f,1.0f,0.0f);
				mWaterObject->textureCoord(0.0f,0.0f);
				mWaterObject->position(startpos + (x+1) * TILESIZE, 0.0f, startpos + (y+1) * TILESIZE);
				mWaterObject->colour(1.0f,1.0f,1.0f);
				mWaterObject->normal(0.0f,1.0f,0.0f);
				mWaterObject->textureCoord(1.0f,1.0f);
				mWaterObject->position(startpos + (x+1) * TILESIZE, 0.0f, startpos + y * TILESIZE);
				mWaterObject->colour(1.0f,1.0f,1.0f);
				mWaterObject->normal(0.0f,1.0f,0.0f);
				mWaterObject->textureCoord(1.0f,0.0f);
				mWaterObject->position(startpos + (x+1) * TILESIZE, 0.0f, startpos + (y+1) * TILESIZE);
				mWaterObject->colour(1.0f,1.0f,1.0f);
				mWaterObject->normal(0.0f,1.0f,0.0f);
				mWaterObject->textureCoord(1.0f,1.0f);
				mWaterObject->position(startpos + x * TILESIZE, 0.0f, startpos + y * TILESIZE);
				mWaterObject->colour(1.0f,1.0f,1.0f);
				mWaterObject->normal(0.0f,1.0f,0.0f);
				mWaterObject->textureCoord(0.0f,0.0f);
				mWaterObject->position(startpos + x * TILESIZE, 0.0f, startpos + (y+1) * TILESIZE);
				mWaterObject->colour(1.0f,1.0f,1.0f);
				mWaterObject->normal(0.0f,1.0f,0.0f);
				mWaterObject->textureCoord(0.0f,1.0f);
			}
		}
	mWaterObject->end();

	mWaterNode->attachObject(mWaterObject);
	mWaterNode->setPosition(0,WATERHEIGHT,0);


	//设置摄像机移动范围
	
	float minx = 0.0f;// = ( - (float)(terrainszie - 2 * MAPBOLDER) / 2.0f - 1.0f) * TILESIZE ;
	getWorldCoords(0,0,minx,minx);
	minx -= TILESIZE/2;
	CameraContral::getSingleton().setMoveRect(minx, minx);
	CameraContral::getSingleton().resetCamera();

	//深度投影测试
// 	Ogre::MeshManager::getSingleton().createPlane("testplane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
// 		mWaterPlane, 64, 64, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
// 	Ogre::Entity* testent = Core::getSingleton().mSceneMgr->createEntity("testplaneent", "testplane");
// 	testent->setMaterialName("DepthTest");
// 	Ogre::SceneNode* testnode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
// 	testnode->attachObject(testent);
// 	testnode->setPosition(0.0f,10.0f,0.0f);
	return true;
}

void Terrain::destoryTerrian()
{

	Ogre::CompositorManager::getSingleton().removeCompositor(mMainViewport,"DemoCompositor");


	Core* core = Core::getSingletonPtr();
	core->mSceneMgr->destroyLight(mLight);


	mGridNode->detachObject(mGrid);
	core->mSceneMgr->destroyManualObject(mGrid);
	mGrid = NULL;
	core->mSceneMgr->destroySceneNode(mGridNode);
	mGridNode = NULL;

	//清除地表物件
	std::map<int, stTilePUData*>::iterator puite;
	for(puite = mMapPUMap.begin();  puite!=mMapPUMap.end(); puite++)
	{
		puite->second->mTileParticle->stop();
		puite->second->mTileNode->detachObject(puite->second->mTileParticle);
		core->destroyPUSystem(puite->second->mTileParticle);
		core->mSceneMgr->destroySceneNode(puite->second->mTileNode);
		delete puite->second;
	}
	mMapPUMap.clear();
	
	std::map<int, stTileEntityData*>::iterator entite;
	for(entite = mMapObjMap.begin(); entite != mMapObjMap.end(); entite++)
	{
		entite->second->mTileNode->detachObject(entite->second->mTileEntity);
		core->mSceneMgr->destroyEntity(entite->second->mTileEntity);
		core->mSceneMgr->destroySceneNode(entite->second->mTileNode);
		delete entite->second;
	}
	mMapObjMap.clear();

	//清除水面
	mWaterNode->detachObject(mWaterObject);
	core->mSceneMgr->destroyManualObject(mWaterObject);
	mWaterObject = NULL;
	core->mSceneMgr->destroySceneNode(mWaterNode);
	mWaterNode = NULL;

	//清除地面
	std::vector<stTileEntityData *>::iterator tileite;
	for(tileite = mTileEntityVector.begin(); tileite!= mTileEntityVector.end(); tileite++)
	{
		(*tileite)->mTileNode->detachObject((*tileite)->mTileEntity);
		core->mSceneMgr->destroyEntity((*tileite)->mTileEntity);
		core->mSceneMgr->destroySceneNode((*tileite)->mTileNode);
	}
	mTileEntityVector.clear();
	
	mTerrainNode->detachObject(mTerrainEntity);
	core->mSceneMgr->destroyEntity(mTerrainEntity);
	mTerrainEntity = NULL;
	core->mSceneMgr->destroySceneNode(mTerrainNode);
	mTerrainNode = NULL;
	Ogre::ResourceGroupManager::getSingleton().deleteResource("TerrianMesh");

	//Ogre::RenderSystem *rSys = Core::getSingleton().mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
	mReflectionTarget->removeAllListeners();
	mReflectionTarget->removeAllViewports();
	//Ogre::ResourceGroupManager::getSingleton().deleteResource("reflection");
	//rSys->destroyRenderTarget(mReflectionTarget->getName());
	//Ogre::TextureManager::getSingleton().remove("reflection");

	mShadowDepthMapTarget->removeAllListeners();
	mShadowDepthMapTarget->removeAllViewports();
	//rSys->destroyRenderTarget(mShadowDepthMapTarget->getName());
	//Ogre::ResourceGroupManager::getSingleton().deleteResource("shadowdepthmap");
	//Ogre::TextureManager::getSingleton().remove("shadowdepthmap");

}

void Terrain::getWorldCoords(int x, int y, float &wx, float &wy)
{
	int s = mMapData->getMapSize();
	wx = ((float)x - (float)s / 2.0f + 0.5f) * TILESIZE ;
	wy = ((float)y - (float)s / 2.0f + 0.5f) * TILESIZE;
}

float Terrain::getHeight(float x, float y)
{
	float height = PLANEHEIGHT;
	int xx = 0,yy = 0;
	int s = mMapData->getMapSize();
	calculateGrid(x,y,xx,yy);
	switch (mMapData->getTerrainType(xx,yy))
	{
	case HighGround:
		height = HEIGHGROUNDHEIGHT;
		break;
	case LowGround:
	case Water:
		height = PLANEHEIGHT;
		break;
	case Cliff:
	case Ramp:
		Ogre::Entity* entity = NULL;
		Ogre::Vector3 result = Ogre::Vector3::ZERO;
		float distToColl = 20.0f;
		if(mCollisionTools->raycastFromPoint(Ogre::Vector3(x,20.0f,y),Ogre::Vector3::NEGATIVE_UNIT_Y,result,(Ogre::ulong&)entity,distToColl,QUERYMASK_TERRAIN))
		{
			height = 20.0f - distToColl;
		}
		else
			height = PLANEHEIGHT;
		break;
		/*
		bool ishighground[8];
		ishighground[0] = mMapData->getTerrainType(xx - 1,yy - 1) == HighGround;
		ishighground[1] = mMapData->getTerrainType(xx,yy - 1) == HighGround;
		ishighground[2] = mMapData->getTerrainType(xx + 1,yy - 1) == HighGround;
		ishighground[3] = mMapData->getTerrainType(xx - 1,yy) == HighGround;
		ishighground[4] = mMapData->getTerrainType(xx + 1,yy) == HighGround;
		ishighground[5] = mMapData->getTerrainType(xx - 1,yy + 1) == HighGround;
		ishighground[6] = mMapData->getTerrainType(xx,yy + 1) == HighGround;
		ishighground[7] = mMapData->getTerrainType(xx + 1,yy + 1) == HighGround;
		float dx,dy;
		getWorldCoords(xx,yy,dx,dy);
		dx = x - dx;
		if(dx == 0.0f)
			dx += 0.01f;
		dy = y - dy;
		float z[4];
		z[0] = (ishighground[3] || ishighground[0] || ishighground[1])? HEIGHGROUNDHEIGHT:PLANEHEIGHT;
		z[1] = (ishighground[1] || ishighground[2] || ishighground[4])? HEIGHGROUNDHEIGHT:PLANEHEIGHT;
		z[2] = (ishighground[3] || ishighground[5] || ishighground[6])? HEIGHGROUNDHEIGHT:PLANEHEIGHT;
		z[3] = (ishighground[5] || ishighground[6] || ishighground[7])? HEIGHGROUNDHEIGHT:PLANEHEIGHT;
		if(z[0] != z[1])
			height = z[0] + z[1] * dx /TILESIZE;
		else if(z[0] != z[2])
			height = z[0] + z[2] / dy;
		else if(z[2] != z[3])
			height = z[2] + z[3] / dx;
		else if(z[1] != z[3])
			height = z[1] + z[3] / dy;
		else
			height = PLANEHEIGHT;
		*/
	}
	return height;
}

void Terrain::createTile(int x, int y,float sx, float sy, float *posbuffer, float *uvbuffer, float *nombuffer)
{
	//确定地形块类型
	TerrainType tt[VERTEX_QUAD];
	tt[TOPLEFT] = mMapData->getTerrainType(x -MAPBOLDER -1 , y -MAPBOLDER -1);
	tt[TOPRIGHT] = mMapData->getTerrainType(x -MAPBOLDER , y -MAPBOLDER -1 );
	tt[BOTTOMLEFT] = mMapData->getTerrainType(x -MAPBOLDER  - 1, y -MAPBOLDER );
	tt[BOTTOMRIGHT] = mMapData->getTerrainType(x -MAPBOLDER, y -MAPBOLDER );
	int terrainindex[6] = {0,0,0,0,0,0};
	terrainindex[tt[TOPLEFT]] += 2;
	terrainindex[tt[TOPRIGHT]] += 1;
	terrainindex[tt[BOTTOMLEFT]] += 8;
	terrainindex[tt[BOTTOMRIGHT]] += 4;
	float height = WATERDEEP;
	if(terrainindex[LowGround] + terrainindex[Cliff] + terrainindex[Ramp]== 15)
	{
		height = PLANEHEIGHT;
	}
	if(terrainindex[HighGround] == 15)
	{
		height = HEIGHGROUNDHEIGHT;
	}

	//确定地表贴图
	GroundType gt[VERTEX_QUAD];
	gt[TOPLEFT] = mMapData->getGroundType(x -MAPBOLDER -1 , y -MAPBOLDER -1);
	gt[TOPRIGHT] = mMapData->getGroundType(x -MAPBOLDER , y -MAPBOLDER -1);
	gt[BOTTOMLEFT] = mMapData->getGroundType(x -MAPBOLDER  - 1, y -MAPBOLDER  );
	gt[BOTTOMRIGHT] = mMapData->getGroundType(x -MAPBOLDER, y -MAPBOLDER );
	int groundindex[4] = {0,0,0,0};
	groundindex[gt[TOPLEFT]] +=8;
	groundindex[gt[TOPRIGHT]] += 4;
	groundindex[gt[BOTTOMLEFT]] += 2;
	groundindex[gt[BOTTOMRIGHT]] += 1;

	//绘制地形块位置
	//左上
	(*posbuffer) = sx;
	posbuffer++;
	(*posbuffer)= height;
	posbuffer++;
	(*posbuffer) = sy;
	//右上
	posbuffer++;
	(*posbuffer) = sx + TILESIZE;
	posbuffer++;
	(*posbuffer)= height;
	posbuffer++;
	(*posbuffer) = sy;
	//左下
	posbuffer++;
	(*posbuffer) = sx;
	posbuffer++;
	(*posbuffer)= height;
	posbuffer++;
	(*posbuffer) = sy + TILESIZE;
	//右下
	posbuffer++;
	(*posbuffer) = sx + TILESIZE;
	posbuffer++;
	(*posbuffer)= height;
	posbuffer++;
	(*posbuffer) = sy + TILESIZE;

	//法线
	(*nombuffer) = 0.0f;
	nombuffer++;
	(*nombuffer)= 1.0f;
	nombuffer++;
	(*nombuffer) = 0.0f;
	//右上
	nombuffer++;
	(*nombuffer) = 0.0f;
	nombuffer++;
	(*nombuffer)= 1.0f;
	nombuffer++;
	(*nombuffer) = 0.0f;
	//左下
	nombuffer++;
	(*nombuffer) = 0.0f;
	nombuffer++;
	(*nombuffer)= 1.0f;
	nombuffer++;
	(*nombuffer) = 0.0f;
	//右下
	nombuffer++;
	(*nombuffer) = 0.0f;
	nombuffer++;
	(*nombuffer)= 1.0f;
	nombuffer++;
	(*nombuffer) = 0.0f;
	

	//绘制地形块UV
	bool bottomlayer = false;
	for(int n = 0; n < TEXTURE_COUNT; n++)
	{
		if(groundindex[n] > 0 && !bottomlayer)
		{
			bottomlayer = true;
			groundindex[n] = 15;
		}
		float u,v;
		u = (groundindex[n] % 4) * TERRAINTEXTILESIZE / TERRAINTEXSIZE;
		v = (groundindex[n] / 4) * TERRAINTEXTILESIZE / TERRAINTEXSIZE;
		float d = 1.0f / TERRAINTEXSIZE;
		*uvbuffer = u;
		*(uvbuffer + 1) = v + d;
		*(uvbuffer + 8) = u + TERRAINTEXTILESIZE / TERRAINTEXSIZE - d;
		*(uvbuffer + 9) = v + d;
		*(uvbuffer + 16) = u + d;
		*(uvbuffer + 17) = v + TERRAINTEXTILESIZE / TERRAINTEXSIZE -d;
		*(uvbuffer + 24)= u + TERRAINTEXTILESIZE / TERRAINTEXSIZE -d;
		*(uvbuffer + 25) = v + TERRAINTEXTILESIZE / TERRAINTEXSIZE -d;

		uvbuffer += 2;
	}

	//添加相关模型
	bool usemesh = false;
	int meshindex;
	std::string meshName;
	std::string materialName;
	if(terrainindex[HighGround] > 0 && terrainindex[HighGround] < 15)
	{
		usemesh = true;
		meshName = "Cliff";
		materialName = "Cliff";
		meshindex = terrainindex[HighGround];
	}
	else if(terrainindex[Water] > 0 && terrainindex[Water] < 15)
	{
		usemesh = true;
		meshName = "Bank";
		materialName = "Cliff";
		meshindex = terrainindex[Water];
	}
	if(usemesh)
	{
		switch(mMapData->getGroundType(x -MAPBOLDER -1 , y -MAPBOLDER -1))
		{
		case GreenLand:
			materialName =  materialName + "Mat1";
			break;
		case Desert:
			materialName =  materialName + "Mat2";
			break;
		case Swamp:
			materialName =  materialName + "Mat3";
			break;
		case Snow:
			materialName =  materialName + "Mat4";
			break;
		}
		int angle;
		switch(meshindex)
		{
		case 1:
			meshName = meshName + "1";
			if(meshName == "Cliff1")
			{
				int i = 0;
				if(tt[BOTTOMRIGHT] == Ramp)
					i += 1;
				if(tt[TOPLEFT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp1_1";
					break;
				case 2:
					meshName = "Ramp1_2";
					break;
				case 3:
					meshName = "Ramp1_3";
					break;
				}
			}
			angle = 0;
			break;
		case 2:
			meshName = meshName + "1";
			if(meshName == "Cliff1")
			{
				int i = 0;
				if(tt[TOPRIGHT] == Ramp)
					i += 1;
				if(tt[BOTTOMLEFT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp1_1";
					break;
				case 2:
					meshName = "Ramp1_2";
					break;
				case 3:
					meshName = "Ramp1_3";
					break;
				}
			}
			angle = 90;
			break;
		case 3:
			meshName = meshName + "2";
			if(meshName == "Cliff2")
			{
				int i = 0;
				if(tt[BOTTOMRIGHT] == Ramp)
					i += 1;
				if(tt[BOTTOMLEFT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp2_1";
					break;
				case 2:
					meshName = "Ramp2_2";
					break;
				case 3:
					meshName = "Ramp2_3";
					break;
				}
			}
			angle = 0;
			break;
		case 4:
			meshName = meshName + "1";
			if(meshName == "Cliff1")
			{
				int i = 0;
				if(tt[BOTTOMLEFT] == Ramp)
					i += 1;
				if(tt[TOPRIGHT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp1_1";
					break;
				case 2:
					meshName = "Ramp1_2";
					break;
				case 3:
					meshName = "Ramp1_3";
					break;
				}
			}
			angle = -90;
			break;
		case 5:
			meshName = meshName + "2";
			if(meshName == "Cliff2")
			{
				int i = 0;
				if(tt[BOTTOMLEFT] == Ramp)
					i += 1;
				if(tt[TOPLEFT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp2_1";
					break;
				case 2:
					meshName = "Ramp2_2";
					break;
				case 3:
					meshName = "Ramp2_3";
					break;
				}
			}
			angle = -90;
			break;
		case 6:
			meshName = meshName + "4";
			angle = -90;
			break;
		case 7:
			meshName = meshName + "3";
			angle = 0;
			break;
		case 8:
			meshName = meshName + "1";
			if(meshName == "Cliff1")
			{
				int i = 0;
				if(tt[TOPLEFT] == Ramp)
					i += 1;
				if(tt[BOTTOMRIGHT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp1_1";
					break;
				case 2:
					meshName = "Ramp1_2";
					break;
				case 3:
					meshName = "Ramp1_3";
					break;
				}
			}
			angle = 180;
			break;
		case 9:
			meshName = meshName + "4";
			angle = 0;
			break;
		case 10:
			meshName = meshName + "2";
			if(meshName == "Cliff2")
			{
				int i = 0;
				if(tt[TOPRIGHT] == Ramp)
					i += 1;
				if(tt[BOTTOMRIGHT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp2_1";
					break;
				case 2:
					meshName = "Ramp2_2";
					break;
				case 3:
					meshName = "Ramp2_3";
					break;
				}
			}
			angle = 90;
			break;
		case 11:
			meshName = meshName + "3";
			angle = 90;
			break;
		case 12:
			meshName = meshName + "2";
			if(meshName == "Cliff1")
			{
				int i = 0;
				if(tt[TOPLEFT] == Ramp)
					i += 1;
				if(tt[TOPRIGHT] == Ramp)
					i += 2;
				switch(i)
				{
				case 1:
					meshName = "Ramp2_1";
					break;
				case 2:
					meshName = "Ramp2_2";
					break;
				case 3:
					meshName = "Ramp2_3";
					break;
				}
			}
			angle = 180;
			break;
		case 13:
			meshName = meshName + "3";
			angle = -90;
			break;
		case 14:
			meshName = meshName + "3";
			angle = 180;
			break;
		}
		meshName = meshName + randMesh(x, y);
		stTileEntityData* entitydata = new stTileEntityData;
		entitydata->mTileEntity = Core::getSingleton().mSceneMgr->createEntity(meshName + ".mesh");
		entitydata->mTileEntity->setMaterialName(materialName);
		entitydata->mTileNode = mTerrainNode->createChildSceneNode();
		entitydata->mTileNode->attachObject(entitydata->mTileEntity);
		entitydata->mTileEntity->setQueryFlags(QUERYMASK_TERRAIN);
		entitydata->mTileNode->setPosition(sx + TILESIZE /2 ,PLANEHEIGHT,sy + TILESIZE /2);
		entitydata->mTileNode->yaw(Ogre::Degree(angle));
		mTileEntityVector.push_back(entitydata);
	}
}

void Terrain::createGrid()
{
	//float startpos = - mMapData->getMapSize() * TILESIZE / 2.0f  -TILESIZE;//公式有错
	float startpos;
	getWorldCoords(0,0,startpos,startpos);
	startpos -= TILESIZE /2.0f;
	mGridNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode("GridNode");
	mGrid = Core::getSingleton().mSceneMgr->createManualObject("GridObject");
	mGrid->begin("GridMat",Ogre::RenderOperation::OT_LINE_LIST);
	for(int y = 0; y < mMapData->getMapSize(); y++)
		for(int x = 0; x < mMapData->getMapSize(); x++)
		{
			if(mMapData->getPassable(x,y,0))
			{
				float xx = startpos + x * TILESIZE;
				float yy = startpos + y * TILESIZE;
				if(!mMapData->getPassable(x ,y -1,-1))
				{
					mGrid->position(xx,getHeight(xx,yy),yy);
					mGrid->colour(1.0f,1.0f,1.0f);
					mGrid->position(xx+TILESIZE,getHeight(xx+TILESIZE,yy),yy);
					mGrid->colour(1.0f,1.0f,1.0f);
				}
				if(!mMapData->getPassable(x - 1,y,-1))
				{
					mGrid->position(xx,getHeight(xx,yy+TILESIZE),yy+TILESIZE);
					mGrid->colour(1.0f,1.0f,1.0f);
					mGrid->position(xx,getHeight(xx,yy),yy);
					mGrid->colour(1.0f,1.0f,1.0f);
				}
				mGrid->position(xx+TILESIZE,getHeight(xx+TILESIZE,yy),yy);
				mGrid->colour(1.0f,1.0f,1.0f);
				mGrid->position(xx+TILESIZE,getHeight(xx+TILESIZE,yy+TILESIZE),yy+TILESIZE);
				mGrid->colour(1.0f,1.0f,1.0f);
				mGrid->position(xx,getHeight(xx,yy+TILESIZE),yy+TILESIZE);
				mGrid->colour(1.0f,1.0f,1.0f);
				mGrid->position(xx+TILESIZE,getHeight(xx+TILESIZE,yy+TILESIZE),yy+TILESIZE);
				mGrid->colour(1.0f,1.0f,1.0f);
			}
		}
		mGrid->end();
		mGrid->setQueryFlags(QUERYMASK_GRID);
		mGrid->setVisibilityFlags(VISMASK_TRANSPARENT);
		mGridNode->attachObject(mGrid);
		mGridNode->setPosition(0,PLANEHEIGHT+ 0.5f,0);
}

std::string Terrain::randMesh(int x, int y)
{
	char temp[8];
	int num = abs(x + y)%2 +1;
	sprintf_s(temp, 8, "_%d", num);
	return temp;
}

bool Terrain::coordinateToGrid( float x,float y,int& GX,int& GY )
{
	Ogre::Vector2 mRenderWindowSize(Core::getSingletonPtr()->mWindow->getWidth(),Core::getSingletonPtr()->mWindow->getHeight());

	// 检查边界条件
	if  (x < 0 || x > mRenderWindowSize.x || y < 0 || y > mRenderWindowSize.y)
		return false;

	//执行射线运算,获取与网格的交点
	Ogre::Ray ray = Core::getSingletonPtr()->mCamera->getCameraToViewportRay(x / mRenderWindowSize.x, y / mRenderWindowSize.y);
	
	Ogre::Vector3 point;
	Ogre::ulong target;
	float d;
	if(mCollisionTools->raycast(ray,point,target,d,QUERYMASK_TERRAIN))
	{
		calculateGrid(point.x,point.z,GX, GY);
		return true;
	}
	else
	{
		return false;
	}
}

void Terrain::calculateGrid( float x,float y,int& GX, int& GY )
{
	//// 将坐标转换成正值
	//float x1=x+(mMapData->getMapSize()+1) * TILESIZE / 2;
	//float y1=y+(mMapData->getMapSize()+1) * TILESIZE / 2;

	////向内移动3格半
	//x1-=2.5* TILESIZE;
	//y1-=2.5* TILESIZE;
	
	float x1=x+mMapData->getMapSize() * TILESIZE / 2.0f;
	float y1=y+mMapData->getMapSize() * TILESIZE / 2.0f;

	GX=x1/TILESIZE;
	GY=y1/TILESIZE;

	/*
	if(GX>=mMapData->getMapSize())
	{
		GX=mMapData->getMapSize()-1;
	}
	else if (GX<0)
	{
		GX=0;
	}

	if(GY>=mMapData->getMapSize())
	{
		GY=mMapData->getMapSize()-1;
	}
	else if (GY<0)
	{
		GY=0;
	}
	*/
}

int Terrain::createMapObj(int x, int y, std::string meshname)
{
	stTileEntityData* entitydata = new stTileEntityData;
	entitydata->mTileEntity = Core::getSingleton().mSceneMgr->createEntity(meshname);
	entitydata->mTileNode = mTerrainNode->createChildSceneNode();
	entitydata->mTileNode->attachObject(entitydata->mTileEntity);
	float xx,yy;
	getWorldCoords(x,y,xx,yy);
	entitydata->mTileNode->setPosition(xx ,getHeight(xx,yy),yy);
	mObjId ++;
	mMapObjMap.insert(std::map<int, stTileEntityData*>::value_type(mObjId,entitydata ));
	return mObjId;
}
void Terrain::deleteMapObj(int index)
{
	std::map<int, stTileEntityData*>::iterator ite;
	ite = mMapObjMap.find(index);
	if(ite!=mMapObjMap.end())
	{
		ite->second->mTileNode->detachObject(ite->second->mTileEntity);
		Core::getSingleton().mSceneMgr->destroyEntity(ite->second->mTileEntity);
		Core::getSingleton().mSceneMgr->destroySceneNode(ite->second->mTileNode);
		delete ite->second;
		mMapObjMap.erase(ite);
	}
}

int Terrain::createMapParticle(int x, int y,std::string particlename)
{
	stTilePUData* pudata = new stTilePUData;
	pudata->mTileNode = mTerrainNode->createChildSceneNode();
	pudata->mTileParticle = Core::getSingleton().createPUSystem(pudata->mTileNode->getName() + "_PU", particlename);
	pudata->mTileNode->attachObject(pudata->mTileParticle);
	pudata->mTileParticle->prepare();
	pudata->mTileParticle->start();
	float xx,yy;
	getWorldCoords(x,y,xx,yy);
	pudata->mTileNode->setPosition(xx ,getHeight(xx,yy),yy);
	mPUId ++;
	mMapPUMap.insert(std::map<int, stTilePUData*>::value_type(mPUId,pudata ));
	return mPUId;
}
void Terrain::deleteMapParticle(int index)
{
	std::map<int, stTilePUData*>::iterator ite;
	ite = mMapPUMap.find(index);
	if(ite!=mMapPUMap.end())
	{
		ite->second->mTileParticle->stop();
		ite->second->mTileNode->detachObject(ite->second->mTileParticle);
		Core::getSingleton().destroyPUSystem(ite->second->mTileParticle);
		Core::getSingleton().mSceneMgr->destroySceneNode(ite->second->mTileNode);
		delete ite->second;
		mMapPUMap.erase(ite);
	}
}

void Terrain::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	mWaterNode->setVisible(false);
	Core::getSingleton().mCamera->enableReflection(mWaterPlane);
	if(mGridNode)
		mGridNode->setVisible(false);
	if(evt.source == mShadowDepthMapTarget)
	{
// 		std::map<int, stTilePUData*>::iterator ite;
// 		for(ite = mMapPUMap.begin(); ite!= mMapPUMap.end(); ite++)
// 		if(ite!=mMapPUMap.end())
// 		{
// 			ite->second->mTileNode->setVisible(false);
// 		}
// 		//隐藏单位粒子效果
// 		SquadGrapManager::getSingleton().setParticleVisible(false);

		Ogre::GpuSharedParametersPtr sharedparams = Ogre::GpuProgramManager::getSingleton().getSharedParameters("ShadowSharedParamsName");
		Ogre::Matrix4 cameraview= CameraContral::getSingleton().getShadowMapCamera()->getViewMatrix();
		sharedparams->setNamedConstant("texView",cameraview);
		//Ogre::Vector3 shadowdir = CameraContral::getSingleton().getShadowMapCamera()->getDirection();
		//sharedparams->setNamedConstant("shadowDir",shadowdir);
	}
// 	else
// 	{
// 		Ogre::CompositorManager::getSingleton().setCompositorEnabled(mMainViewport, "DemoCompositor", false);
// 	}
}
void Terrain::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	mWaterNode->setVisible(true);
	Core::getSingleton().mCamera->disableReflection();
	if(mGridNode)
		mGridNode->setVisible(true);
// 	if(evt.source == mShadowDepthMapTarget)
// 	{
// 		std::map<int, stTilePUData*>::iterator ite;
// 		for(ite = mMapPUMap.begin(); ite!= mMapPUMap.end(); ite++)
// 			if(ite!=mMapPUMap.end())
// 			{
// 				ite->second->mTileNode->setVisible(true);
// 			}
// 		SquadGrapManager::getSingleton().setParticleVisible(true);
// 	}
// 	if(evt.source == mReflectionTarget)
// 	{
// 		Ogre::CompositorManager::getSingleton().setCompositorEnabled(mMainViewport, "DemoCompositor", true);
// 	}
	if(evt.source == mReflectionTarget)
	{
		Ogre::GpuSharedParametersPtr sharedparams = Ogre::GpuProgramManager::getSingleton().getSharedParameters("TestSharedParamsName");
		Ogre::Matrix4 cameraview= Core::getSingleton().mCamera->getViewMatrix().inverse();
		sharedparams->setNamedConstant("viewInv",cameraview);
	}
}
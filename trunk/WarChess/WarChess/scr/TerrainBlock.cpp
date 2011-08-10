#include "TerrainBlock.h"
#include <QDebug>

TerrainBlock::TerrainBlock(int GX,int GY,float X,float Y,int gridSize,int blockSize,Ogre::SceneManager* sceneManager,Ogre::MeshPtr planeMesh):
mX(X),mY(Y),mGridX(GX),mGridY(GY),mGridSize(gridSize),mBlockSize(blockSize),mBlockEntity(NULL),mPlaneMesh(planeMesh),mSceneManager(sceneManager),mPlane(true),mHeight(DefaultHeight),mIndex(0),mBlockType(LowGround)
{
	mBlockNode=mSceneManager->getRootSceneNode()->createChildSceneNode();
	mConerTerrian[TopRight] = mConerTerrian[TopLeft] = mConerTerrian[BottomLeft] = mConerTerrian[BottomRight] = GreenLand;
}

TerrainBlock::~TerrainBlock(void)
{
}

void TerrainBlock::setTerrainAsMesh(std::string name, int angle)
{
	if (mBlockEntity!=NULL)
	{
		removeMesh();
	}

	mBlockEntity=mSceneManager->createEntity(name+".mesh");

	mBlockNode->attachObject(mBlockEntity);

	mBlockNode->setPosition(mX,0,mY);

	mBlockNode->yaw(Ogre::Degree(angle));

	mAngle = angle;

	mHeight=0;

	mPlane=false;
}

void TerrainBlock::_updateTile(float* pBufferPos , float* pBufferUV , bool bUpdatePos,bool bUpdateUV)
{

	// 获得顶点大小
	const size_t iPosVertexSize = mPlaneMesh->getSubMesh(0)->vertexData->vertexDeclaration->getVertexSize(VERTEX_POS_BINDING);
	const size_t iUVVertexSize = mPlaneMesh->getSubMesh(0)->vertexData->vertexDeclaration->getVertexSize(VERTEX_UV_BINDING);

	// 偏移到当前Tile的顶点位置
	pBufferPos += (mGridX+mGridY*mGridSize)* (iPosVertexSize/4) * VERTEX_QUAD;
	pBufferUV += (mGridX+mGridY*mGridSize)* (iUVVertexSize/4) * VERTEX_QUAD;

	// 一个Tile由4个顶点组成
	if(bUpdatePos)
	{
		updatePos(pBufferPos);

	}
	
	if (bUpdateUV)
	{
		updateUV(pBufferUV);
	}
}

void TerrainBlock::updatePos( float* pBufferPos )
{

	//左上
	(*pBufferPos)=mX-mBlockSize/2;//X
	pBufferPos++;
	(*pBufferPos)=mHeight;//Y
	pBufferPos++;
	(*pBufferPos)=mY-mBlockSize/2;//Z
	pBufferPos++;

	//右上
	(*pBufferPos)=mX+mBlockSize/2;//X
	pBufferPos++;
	(*pBufferPos)=mHeight;//Y
	pBufferPos++;
	(*pBufferPos)=mY-mBlockSize/2;//Z
	pBufferPos++;


	//左下
	(*pBufferPos)=mX-mBlockSize/2;//X
	pBufferPos++;
	(*pBufferPos)=mHeight;//Y
	pBufferPos++;
	(*pBufferPos)=mY+mBlockSize/2;//Z
	pBufferPos++;

	//右下
	(*pBufferPos)=mX+mBlockSize/2;//X
	pBufferPos++;
	(*pBufferPos)=mHeight;//Y
	pBufferPos++;
	(*pBufferPos)=mY+mBlockSize/2;//Z

}

void TerrainBlock::updateUV(float* pBufferUV)
{
	int texIndex[4] = {0};
	int lowLayer = 5;
	for(int n = 0; n<4; n++)
	{
		for(int m = 0; m < 4; m++)
		{
			if(mConerTerrian[m] == n)
			{
				switch(m)
				{
				case 0:
					texIndex[n] += 1;
					break;
				case 1:
					texIndex[n] += 2;
					break;
				case 2:
					texIndex[n] += 8;
					break;
				case 3:
					texIndex[n] += 4;
					break;

				}
			}
		}
		if (texIndex[n] > 0 && lowLayer == 5)
		{
			lowLayer = n;
		}
	}
	texIndex[lowLayer] = 15;

	float* bufferUV=pBufferUV;

	for(int m=0;m<4;m++)//对m代表当前设置第几层的贴图坐标
	{
		WriteConerTexCoords(bufferUV,texIndex[m],0);//更新左上角顶点
		WriteConerTexCoords(bufferUV+8,texIndex[m],1);//更新右上角顶点
		WriteConerTexCoords(bufferUV+16,texIndex[m],2);//更新左下角顶点
		WriteConerTexCoords(bufferUV+24,texIndex[m],3);//更新右下角顶点
		bufferUV+=2;
	}
}

void TerrainBlock::WriteConerTexCoords(float* pos, int index, int coner)
{
	int x,y;
	y = index % (int)(TEXTURE_SIZE/TEXTURE_BLOCK_SIZE);
	x = index / (int)(TEXTURE_SIZE/TEXTURE_BLOCK_SIZE);
	switch (coner)
	{
	case 0://左上
		*pos = x * TEXTURE_BLOCK_SIZE  / TEXTURE_SIZE;
		pos++;
		*pos = y * TEXTURE_BLOCK_SIZE  / TEXTURE_SIZE;
		break;
	case 1://右上
		*pos = (x * TEXTURE_BLOCK_SIZE + TEXTURE_BLOCK_SIZE) / TEXTURE_SIZE;
		pos++;
		*pos = y * TEXTURE_BLOCK_SIZE  / TEXTURE_SIZE;
		break;
	case 2://左下
		*pos = x * TEXTURE_BLOCK_SIZE  / TEXTURE_SIZE;
		pos++;
		*pos = (y * TEXTURE_BLOCK_SIZE + TEXTURE_BLOCK_SIZE) / TEXTURE_SIZE;
		break;
	case 3://右下
		*pos = (x * TEXTURE_BLOCK_SIZE + TEXTURE_BLOCK_SIZE) / TEXTURE_SIZE;
		pos++;
		*pos = (y * TEXTURE_BLOCK_SIZE + TEXTURE_BLOCK_SIZE) / TEXTURE_SIZE;
		break;
	}
}

void TerrainBlock::setPlaneMaterial(GroundType trrianType, ConerType coner)
{
	mConerTerrian[coner] = trrianType;

	Ogre::HardwareVertexBufferSharedPtr vbufUV = mPlaneMesh->getSubMesh(0)->vertexData->vertexBufferBinding->getBuffer(VERTEX_UV_BINDING);      
	float* pBufferUV =(float*)vbufUV->lock(Ogre::HardwareBuffer::HBL_DISCARD);
		_updateTile(NULL,pBufferUV,false,true);
	vbufUV->unlock();
}

void TerrainBlock::setMeshMaterial(std::string name)
{
	if (mBlockEntity!=NULL)
	{
		mBlockEntity->setMaterialName(name);
	}
}


void TerrainBlock::removeMesh()
{
	if (mBlockEntity!=NULL)
	{
		mBlockNode ->yaw(Ogre::Degree(- mAngle));
		mAngle = 0;
		mBlockNode->detachObject(mBlockEntity);
		mSceneManager->destroyEntity(mBlockEntity);
		mBlockEntity=NULL;
	}
}

void TerrainBlock::removeMat()
{
	if (mBlockEntity!=NULL)
	{
		mBlockEntity->setMaterialName("Mramor");
	}
}

bool TerrainBlock::isPlane()
{
	return mPlane;
}

void TerrainBlock::setTerrainAsPlane( float height )
{
	if (mBlockEntity!=NULL)
	{
		removeMesh();
	}
	mPlane=true;
	mHeight=height;
	Ogre::HardwareVertexBufferSharedPtr vbufPos =mPlaneMesh->getSubMesh(0)->vertexData->vertexBufferBinding->getBuffer(VERTEX_POS_BINDING);
	float* pBufferPos = (float*)vbufPos->lock(Ogre::HardwareBuffer::HBL_DISCARD);
		_updateTile(pBufferPos,NULL,true,false);
	vbufPos->unlock();
}


void TerrainBlock::setBlockType(BlockType blokType, GroundType terrianType, int index)
{
	mBlockType = blokType;
	if(terrianType!=GroundDisable)
		mConerTerrian[TopRight] = mConerTerrian[TopLeft] = mConerTerrian[BottomLeft] = mConerTerrian[BottomRight] = terrianType;
	mIndex = index;
}

BlockType TerrainBlock::getBlockType()
{
	return mBlockType;
}

BlockType TerrainBlock::getBlockType(ConerType coner)
{
	if(mBlockType != LowGround)
	{
		switch (coner)
		{
		case BottomRight:
			if((mIndex & 4) > 0 )
				return mBlockType;
			break;
		case BottomLeft:
			if((mIndex & 8) > 0 )
				return mBlockType;
			break;
		case TopRight:
			if((mIndex & 1) > 0 )
				return mBlockType;
			break;
		case TopLeft:
			if((mIndex & 2) > 0 )
				return mBlockType;
			break;
		}
	}
	return LowGround;
}

GroundType TerrainBlock::getTerrianType(ConerType coner)
{
	return mConerTerrian[coner];
}

int TerrainBlock::getBlockMeshIndex()
{
	return mIndex;
}
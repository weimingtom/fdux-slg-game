/*
-----------------------------------------------------------------------------
This source file is part of TankWar
This is a 3D tank war game, use ogre for render, support singleplayer and multiplayer.
For the latest info, see http://flyingpig.isgreat.org or https://sourceforge.net/projects/tankwar3d

Copyright (c) 2000-2010

Usage of this program is free for non-commercial use and licensed under the
the terms of the MIT License.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "Grid.h"

Grid::Grid(Ogre::SceneManager *sceneMgr, int gridX, int gridZ, int blockSize, const Ogre::ColourValue & gridColor,std::string gridName)
: mSceneManager(sceneMgr), mVisible(true),mBlockSize(blockSize),mGridSize(gridX),mGridColor(gridColor)
{
	mGridManualObject = mSceneManager->createManualObject(gridName);

	mNode = mSceneManager->getRootSceneNode()->createChildSceneNode();

	Ogre::MaterialManager &matMgr = Ogre::MaterialManager::getSingleton();
	Ogre::MaterialPtr pMaterial = matMgr.create("GridMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	pMaterial->setLightingEnabled(false);
	pMaterial->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

	float minX = gridX * blockSize / (-2);
	float minZ = gridZ * blockSize / (-2);

	mGirdConerHeight.reserve(gridX * gridX);

	for(int z = 0; z < gridZ; z++)
		for(int x = 0; x < gridX; x++)
		{
			mGridManualObject->begin("GridMaterial", Ogre::RenderOperation::OT_LINE_STRIP );

			mGridManualObject->position( minX + (x + 1) * blockSize, GRIDHEIGHT ,minZ + z * blockSize);
			mGridManualObject->colour(gridColor);

			mGridManualObject->position( minX + x * blockSize , GRIDHEIGHT , minZ + z * blockSize);
			mGridManualObject->colour(gridColor);

			mGridManualObject->position( minX + x * blockSize ,GRIDHEIGHT , minZ + (z + 1)* blockSize);
			mGridManualObject->colour(gridColor);

			mGridManualObject->position( minX + (x + 1) *blockSize, GRIDHEIGHT , minZ + (z  + 1) *blockSize);
			mGridManualObject->colour(gridColor);

			mGridManualObject->position( minX + (x + 1) * blockSize, GRIDHEIGHT ,minZ + z * blockSize);
			mGridManualObject->colour(gridColor);


			mGridManualObject->end();
			mGirdConerHeight.push_back(0);
		}


	mNode->attachObject(mGridManualObject);
	
	//创建光标

	mCursorPlane = mSceneManager->createManualObject(gridName+"_Cursor");
	mCursorPlane->begin("GridMaterial", Ogre::RenderOperation::OT_LINE_STRIP );

	mCursorPlane->position( -blockSize/2, GRIDHEIGHT ,blockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position( blockSize/2 , GRIDHEIGHT , blockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position( blockSize/2 , GRIDHEIGHT , -blockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position(-blockSize/2, GRIDHEIGHT , -blockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position(-blockSize/2, GRIDHEIGHT ,blockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->end();
	mCursorNode=mSceneManager->getRootSceneNode()->createChildSceneNode();
	mCursorNode->attachObject(mCursorPlane);
	
}

Grid::~Grid()
{
	mNode->detachObject(mGridManualObject);
	mSceneManager->destroyManualObject(mGridManualObject);
	mSceneManager->destroySceneNode(mNode);

	mGridManualObject = 0;
	mNode = 0;
}

void Grid::setPosition(const Ogre::Vector3 &pos)
{
	mNode->setPosition(pos);
}

void Grid::setVisible(bool visible)
{
	mVisible = visible;
	mNode->setVisible(visible);
}

bool Grid::isVisible()
{
	return mVisible;
}

Ogre::AxisAlignedBox Grid::getBoundingbox()
{
	return mGridManualObject->getBoundingBox();
}

float Grid::getMaxGrid()
{
	return mGridSize * mBlockSize / 2;
}

void Grid::setHeight( int x,int z,float height)
{
	int index = z * mGridSize + x;
	float minX = mGridSize * mBlockSize / (-2);
	float minZ = mGridSize * mBlockSize / (-2);

	mGridManualObject->beginUpdate(index);

	mGridManualObject->position( minX + (x + 1) * mBlockSize, height ,minZ + z * mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + x * mBlockSize , height , minZ + z * mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + x * mBlockSize , height , minZ + (z + 1)* mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + (x + 1) *mBlockSize, height , minZ + (z  + 1) *mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + (x + 1) * mBlockSize, height ,minZ + z * mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->end();
}



void Grid::setCursorPosition(int gX,int gY)
{

	int x=gX*mBlockSize-getMaxGrid()+mBlockSize/2;
	int y=gY*mBlockSize-getMaxGrid()+mBlockSize/2;

	int index = gY * mGridSize + gX;

	float minX = mGridSize * mBlockSize / (-2);
	float minZ = mGridSize * mBlockSize / (-2);

	mCursorPlane->beginUpdate(0);
	mCursorPlane->position( -mBlockSize/2, GRIDHEIGHT + ((mGirdConerHeight[index] >> 0) & 0x01) * HIGHGROUNDHEIGHT + 0.1f,mBlockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position( mBlockSize/2 , GRIDHEIGHT +  ((mGirdConerHeight[index] >> 3) & 0x01) * HIGHGROUNDHEIGHT + 0.1f, mBlockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position( mBlockSize/2 , GRIDHEIGHT + ((mGirdConerHeight[index] >> 2) & 0x01) * HIGHGROUNDHEIGHT + 0.1f, -mBlockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position(-mBlockSize/2, GRIDHEIGHT + ((mGirdConerHeight[index] >> 1) & 0x01) * HIGHGROUNDHEIGHT + 0.1f, -mBlockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);

	mCursorPlane->position(-mBlockSize/2, GRIDHEIGHT + ((mGirdConerHeight[index] >> 0) & 0x01) * HIGHGROUNDHEIGHT + 0.1f,mBlockSize/2);
	mCursorPlane->colour(Ogre::ColourValue::Red);
	mCursorPlane->end();

	mCursorNode->setPosition(x,0,y);
	
}

void Grid::setCursorVisible( bool value )
{
	mCursorPlane->setVisible(value);
}

void Grid::SetHighGround(int x, int z, WORD ConerMask)
{
	int index = z * mGridSize + x;
	if(x > -1 && x < mGridSize && z > -1 && z < mGridSize)
	{
		mGirdConerHeight[index] = mGirdConerHeight[index] | ConerMask;
		UpdataGrid(x,z);
	}

}


void Grid::SetLowGround(int x, int z, WORD ConerMask)
{
	int index = z * mGridSize + x;
	if(x > -1 && x < mGridSize && z > -1 && z < mGridSize)
	{
		mGirdConerHeight[index] = mGirdConerHeight[index] & ~ConerMask;
		UpdataGrid(x,z);
	}
}


void Grid::UpdataGrid(int x, int z)
{
	int index = z * mGridSize + x;
	float minX = mGridSize * mBlockSize / (-2);
	float minZ = mGridSize * mBlockSize / (-2);

	mGridManualObject->beginUpdate(index);

	mGridManualObject->position( minX + (x + 1) * mBlockSize, GRIDHEIGHT + (mGirdConerHeight[index] & 0x01) * HIGHGROUNDHEIGHT,minZ + z * mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + x * mBlockSize , GRIDHEIGHT  + ((mGirdConerHeight[index] >> 1) & 0x01) * HIGHGROUNDHEIGHT, minZ + z * mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + x * mBlockSize , GRIDHEIGHT  + ((mGirdConerHeight[index] >> 2 ) & 0x01) * HIGHGROUNDHEIGHT, minZ + (z + 1)* mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + (x + 1) *mBlockSize, GRIDHEIGHT  + ((mGirdConerHeight[index] >> 3) & 0x01) * HIGHGROUNDHEIGHT, minZ + (z  + 1) *mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->position( minX + (x + 1) * mBlockSize, GRIDHEIGHT  + (mGirdConerHeight[index] & 0x01) * HIGHGROUNDHEIGHT,minZ + z * mBlockSize);
	mGridManualObject->colour(mGridColor);

	mGridManualObject->end();
}
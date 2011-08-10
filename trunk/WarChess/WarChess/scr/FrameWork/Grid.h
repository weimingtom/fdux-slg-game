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

#pragma once

#include <Ogre.h>

#define HIGHGROUNDHEIGHT 5.0f
#define GRIDHEIGHT 0.5f
/**
地表辅助网格
*/
class Grid
{
public:
	// gridX X方向方格个数
	// gridZ Z方向方格个数
	// blockSize 方格宽度
	Grid(Ogre::SceneManager *sceneMgr, int gridX, int gridZ, int blockSize, const Ogre::ColourValue & gridColor,std::string gridName);

	~Grid();

	void setPosition(const Ogre::Vector3 &pos);

	void setVisible(bool visible);
	bool isVisible();

	// 获取网格的包围盒, 射线检测使用
	Ogre::AxisAlignedBox getBoundingbox();
	
	// 最大坐标
	float getMaxGrid();

	void setHeight(int x,int z,float height);//更新高度

	void setCursorPosition(int gX,int gY);//设置网格光标的位置

	void setCursorVisible(bool value);//设置光标可视状态

	//更新网格高度
	void SetHighGround(int x, int z,WORD ConerMask);
	void SetLowGround(int x, int z,WORD ConerMask);

	int mBlockSize;
	int mGridSize;
private:
	Ogre::SceneManager* mSceneManager;
	Ogre::ManualObject* mGridManualObject;//网格对象
	Ogre::SceneNode* mNode;//网格的节点
	Ogre::ColourValue mGridColor;//网格颜色
	Ogre::ManualObject* mCursorPlane;//光标对象
	Ogre::SceneNode* mCursorNode;//光标对象节点

	void UpdataGrid(int x, int z);
	std::vector<WORD>	mGirdConerHeight;

	bool mVisible;
};
/*
 * 文件名:TerrainEditor.h
 * 创建时间:2010:10:14   15:09
 * 编写者:winsock
 * 功能:  作为所有的地形系统编辑器的基类,使得外部模块与地形系统隔离开来
 */

#pragma once

#include <vector>
#include <map>
#include <string>
#include "Common.h"
#include "Grid.h"

class TerrainBlock;
class RampManager;

class TerrainEditor
{
public:
	TerrainEditor(TerrainBlock* (*terrainBlocks)[MAX_MAPSIZE][MAX_MAPSIZE],Grid* grid,RampManager* ramp ):mTerrainBlocks(terrainBlocks),mGrid(grid),mRamp(ramp),mMode(PutMode){};//意思是,传入一个数组的指针,这个数组是TerrainBlock的指针
	virtual ~TerrainEditor(void){};
	
	virtual EditorID getEditorId()=0;//返回该编辑器的ID
	virtual std::vector<std::string> getEditorTypeList()=0;//返回该编辑器支持哪些操作
	virtual std::vector<std::string> setEditorType(std::string type)=0;//设置当前编辑器的操作,返回一个stringList,指明该操作需要哪些参数
	virtual void setGrid(int GX,int GY)=0;//将目前选定的编辑器操作应用到地形上

	void setEditorMode(EditorMode mode)//设置编辑器的操作模式
	{
		mMode=mode;
	}

	void setEditorArgs(std::string name,std::string value)//设置编辑器操作参数
	{
		mArgs[name]=value;
	}

protected:
	TerrainBlock* (*mTerrainBlocks)[MAX_MAPSIZE][MAX_MAPSIZE];
	std::map<std::string,std::string> mArgs;
	EditorMode mMode;
	Grid* mGrid;
	RampManager *mRamp;
};

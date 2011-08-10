/*
 * 文件名:BlockEditor.h
 * 创建时间:2010:10:17   9:50
 * 编写者:winsock
 * 功能: 继承于TerrainEditor,实现了地形块的编辑
 */

#pragma once
#include "terraineditor.h"

class TerrainBlock;

class BlockEditor :
	public TerrainEditor
{
public:
	BlockEditor(TerrainBlock* (*terrainBlocks)[MAX_MAPSIZE][MAX_MAPSIZE],Grid* grid,RampManager* ramp);
	~BlockEditor(void);

	EditorID getEditorId()//返回该编辑器的ID
	{
		return BlockID;
	}

	std::vector<std::string> getEditorTypeList();//返回该编辑器支持哪些操作
	std::vector<std::string> setEditorType(std::string type);//设置当前编辑器的操作,返回一个stringList,指明该操作需要哪些参数
	void setGrid(int GX,int GY);//将目前选定的编辑器操作应用到地形上

private:
	std::string currType;
};

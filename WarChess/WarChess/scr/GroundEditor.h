/*
 * 文件名:BlockEditor.h
 * 创建时间:2010:10:17   9:50
 * 编写者:winsock
 * 功能: 继承于TerrainEditor,实现了地表的编辑
 */

#pragma once
#include "terraineditor.h"



class GroundEditor :
	public TerrainEditor
{
public:
	GroundEditor(TerrainBlock* (*terrainBlocks)[MAX_MAPSIZE][MAX_MAPSIZE],Grid* grid, RampManager* ramp);
	~GroundEditor(void);

	EditorID getEditorId()//返回该编辑器的ID
	{
		return GroundID;
	}

	std::vector<std::string> getEditorTypeList();//返回该编辑器支持哪些操作
	std::vector<std::string> setEditorType(std::string type);//设置当前编辑器的操作,返回一个stringList,指明该操作需要哪些参数
	void setGrid(int GX,int GY);//将目前选定的编辑器操作应用到地形上
	GroundType getTileTerrianType(int GX,int GZ);

private:
	GroundType currType;
	BlockType currBlockType;

	void planish(int GX,int GZ);//推平地形块
	void setTile(int GX,int GZ, BlockType blockType, GroundType trrianType);//设置地形实际调用
	void changeBlockMesh(int GX,int GZ, BlockType blockType, GroundType trrianType,int index); //修改地形的模型用
	BlockType getTileBlockType(int GX,int GZ);
	void changeHighGroundPlane(int GX,int GZ,GroundType trrianType );
	GroundType isHighGroundPlane(int GX,int GZ);
	void setRamp(int GX,int GZ);
};

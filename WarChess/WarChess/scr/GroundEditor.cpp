#include "GroundEditor.h"
#include "TerrainBlock.h"
#include "RampManager.h"

GroundEditor::GroundEditor( TerrainBlock* (*terrainBlocks)[MAX_MAPSIZE][MAX_MAPSIZE],Grid* grid, RampManager* ramp):
TerrainEditor(terrainBlocks,grid,ramp),currType(GreenLand)
{

}

GroundEditor::~GroundEditor(void)
{
}

std::vector<std::string> GroundEditor::getEditorTypeList()
{
	std::vector<std::string> result;

	result.push_back("GreenLand");//草地
	result.push_back("Desert");//沙漠
	result.push_back("Swamp");//沼泽
	result.push_back("Snow");//雪地

	result.push_back("HighGroundGreen");
	result.push_back("HighGroundDesert");
	result.push_back("HighGroundSwamp");
	result.push_back("HighGroundSnow");

	result.push_back("HighGroundGreenPlane");
	result.push_back("HighGroundDesertPlane");
	result.push_back("HighGroundSwampPlane");
	result.push_back("HighGroundSnowPlane");

	result.push_back("Planish");
	result.push_back("Ramp");

	result.push_back("WaterGreen");
	result.push_back("WaterDesert");
	result.push_back("WaterSwamp");
	result.push_back("WaterSnow");

	return result;
}

std::vector<std::string> GroundEditor::setEditorType( std::string type )
{
	if (type=="NULL")
	{
		currType=GroundDisable;
	}
	else if (type=="GreenLand")
	{
		currType=GreenLand;
		currBlockType = LowGround;
	}
	else if(type=="Desert")
	{
		currType=Desert;
		currBlockType = LowGround;
	}
	else if (type=="Swamp")
	{
		currType=Swamp;
		currBlockType = LowGround;
	}
	else if (type=="Snow")
	{
		currType=Snow;
		currBlockType = LowGround;
	}
	else if (type=="HighGroundGreen")
	{
		currType=GreenLand;
		currBlockType = HighGround;
	}
	else if(type=="HighGroundDesert")
	{
		currType=Desert;
		currBlockType = HighGround;
	}
	else if (type=="HighGroundSwamp")
	{
		currType=Swamp;
		currBlockType = HighGround;
	}
	else if (type=="HighGroundSnow")
	{
		currType=Snow;
		currBlockType = HighGround;
	}
	else if (type=="HighGroundGreenPlane")
	{
		currType=GreenLand;
		currBlockType = HighGroundPlane;
	}
	else if(type=="HighGroundDesertPlane")
	{
		currType=Desert;
		currBlockType = HighGroundPlane;
	}
	else if (type=="HighGroundSwampPlane")
	{
		currType=Swamp;
		currBlockType = HighGroundPlane;
	}
	else if (type=="HighGroundSnowPlane")
	{
		currType=Snow;
		currBlockType = HighGroundPlane;
	}
	else if (type=="WaterGreen")
	{
		currType=GreenLand;
		currBlockType = Water;
	}
	else if(type=="WaterDesert")
	{
		currType=Desert;
		currBlockType = Water;
	}
	else if (type=="WaterSwamp")
	{
		currType=Swamp;
		currBlockType = Water;
	}
	else if (type=="WaterSnow")
	{
		currType=Snow;
		currBlockType = Water;
	}
	else if(type == "Planish")
	{
		currBlockType = Planish;
	}
	else if(type == "Ramp")
	{
		currBlockType = Ramp;
	}
	return std::vector<std::string>();
}

void GroundEditor::setGrid( int GX,int GY )
{

	if(currType!=GroundDisable)
	{
		switch(mMode)
		{
		case PutMode:
			if(currBlockType == Planish)
				planish(GX,GY);
			else if(currBlockType == HighGroundPlane)
				changeHighGroundPlane(GX, GY, currType );
			else if(currBlockType == Ramp )
				setRamp(GX,GY);
			else
				setTile(GX, GY, currBlockType, currType);
			break;
		}
	}
}

void GroundEditor::planish(int GX,int GZ)
{
	GroundType  cliffType;
	for(int gz = GZ -1; gz < GZ + 2; gz++ )
	{
		for(int gx = GX -1; gx < GX + 2; gx++)
		{
			if(gz < 0 || gx <0 || (gx > (mGrid->mGridSize - 1)) || (gz > (mGrid->mGridSize -1)))
				continue;
			cliffType = isHighGroundPlane(gx,gz);
			if(cliffType != GroundDisable)
				changeHighGroundPlane(gx,gz,cliffType);
		}
	}

	std::multimap<int,int> MainGrids;
	ConerType gridType[4];
	int conerMask[4];
	int gridTypeIndex=0;
	MainGrids.insert(std::multimap<int,int>::value_type(GX+1, GZ+1));//右下
	gridType[0]=TopRight;
	conerMask[0] = 1;
	MainGrids.insert(std::multimap<int,int>::value_type(GX, GZ+1));//左下
	gridType[1]=BottomRight;
	conerMask[1] = 4;
	MainGrids.insert(std::multimap<int,int>::value_type(GX+1, GZ));//右上
	gridType[2]=TopLeft;
	conerMask[2] = 2;
	MainGrids.insert(std::multimap<int,int>::value_type(GX, GZ));//左上
	gridType[3]=BottomLeft;
	conerMask[3] = 8;

	std::multimap<int,int>::iterator it;
	for (it=MainGrids.begin();it!=MainGrids.end();it++)
	{
		int gX=it->first;
		int gZ=it->second;
		if (((*mTerrainBlocks)[gX][gZ])->getBlockType() != LowGround)
		{
			int index = ((*mTerrainBlocks)[gX][gZ])->getBlockMeshIndex();
			index = index & ~conerMask[gridTypeIndex];
			changeBlockMesh(gX,gZ,((*mTerrainBlocks)[gX][gZ])->getBlockType(),((*mTerrainBlocks)[gX][gZ])->getTerrianType(TopLeft),index);
		}
		gridTypeIndex++;
	} 
	mRamp->removeRamp(GX,GZ);
}

void GroundEditor::setTile(int GX,int GZ, BlockType blockType, GroundType trrianType)
{
	for(int gz = GZ -1; gz < GZ + 2; gz++ )
	{
		for(int gx = GX -1; gx < GX + 2; gx++)
		{
			if(gz < 0 || gx <0 || (gx > (mGrid->mGridSize - 1)) || (gz > (mGrid->mGridSize -1)))
				continue;
			if(blockType == LowGround)
			{
				if(getTileBlockType(gx,gz) != LowGround)
					if(getTileTerrianType(gx,gz) != trrianType)
						planish(gx,gz);
			}
			else
			{
				if(getTileBlockType(gx,gz) != blockType)
					planish(gx,gz);
				if(getTileTerrianType(gx,gz) != trrianType)
					setTile(gx,gz,LowGround,trrianType);
			}
		}
	}
	
	std::multimap<int,int> MainGrids;
	ConerType gridType[4];
	int conerMask[4];
	int gridTypeIndex=0;
	MainGrids.insert(std::multimap<int,int>::value_type(GX+1, GZ+1));//右下
	gridType[0]=TopRight;
	conerMask[0] = 1;
	MainGrids.insert(std::multimap<int,int>::value_type(GX, GZ+1));//左下
	gridType[1]=BottomRight;
	conerMask[1] = 4;
	MainGrids.insert(std::multimap<int,int>::value_type(GX+1, GZ));//右上
	gridType[2]=TopLeft;
	conerMask[2] = 2;
	MainGrids.insert(std::multimap<int,int>::value_type(GX, GZ));//左上
	gridType[3]=BottomLeft;
	conerMask[3] = 8;

	std::multimap<int,int>::iterator it;
	for (it=MainGrids.begin();it!=MainGrids.end();it++)
	{
		int gX=it->first;
		int gZ=it->second;
		if (blockType != LowGround)
		{
			int index = ((*mTerrainBlocks)[gX][gZ])->getBlockMeshIndex();
			index = index | conerMask[gridTypeIndex];
			changeBlockMesh(gX,gZ,blockType,trrianType,index);
		}
		else
		{
			((*mTerrainBlocks)[gX][gZ])->setPlaneMaterial(currType,gridType[gridTypeIndex]);
		}
		gridTypeIndex++;
	} 
}

void GroundEditor::changeBlockMesh(int GX,int GZ, BlockType blockType, GroundType trrianType, int index)
{
	Ogre::String meshName;
	Ogre::String materialName;
	int angle = 0;
	switch(blockType)
	{
	case HighGround:
		meshName = "Cliff";
		materialName = "Cliff";
		break;
	case Water:
		meshName = "Bank";
		materialName = "Water";
		break;
	}
	switch(trrianType)
	{
	case GreenLand:
		materialName =  materialName + "Mat1";
		break;
	case Desert:
		materialName = materialName + "Mat2";
		break;
	case Swamp:
		materialName = materialName + "Mat3";
		break;
	case Snow:
		materialName = materialName + "Mat4";
		break;
	}
	if(index == 0)
	{
		((*mTerrainBlocks)[GX][GZ])->setBlockType(LowGround,GroundDisable,0);
		((*mTerrainBlocks)[GX][GZ])->setTerrainAsPlane(DefaultHeight);
		mGrid->SetLowGround(GX-1,GZ-1,0x08);
		mGrid->SetLowGround(GX,GZ-1,0x04);
		mGrid->SetLowGround(GX-1,GZ,0x01);
		mGrid->SetLowGround(GX,GZ,0x02);
	}
	else if(index == 15)
	{
		switch(blockType)
		{
		case HighGround:
			((*mTerrainBlocks)[GX][GZ])->setBlockType(blockType,trrianType,15);
			((*mTerrainBlocks)[GX][GZ])->setTerrainAsPlane(HIGHGROUNDHEIGHT);
			//mGrid->SetHighGround(GX-1,GZ-1,0x08);
			//mGrid->SetHighGround(GX,GZ-1,0x04);
			//mGrid->SetHighGround(GX-1,GZ,0x01);
			//mGrid->SetHighGround(GX,GZ,0x02);
			break;
		case Water:
			((*mTerrainBlocks)[GX][GZ])->setBlockType(blockType,trrianType,15);
			((*mTerrainBlocks)[GX][GZ])->setTerrainAsPlane(-2);
			break;
		}
	}
	else
	{
		switch(index)
		{
		case 1:
			meshName = meshName + "1";
			angle = 0;
			break;
		case 2:
			meshName = meshName + "1";
			angle = 90;
			break;
		case 3:
			meshName = meshName + "2";
			angle = 0;
			break;
		case 4:
			meshName = meshName + "1";
			angle = -90;
			break;
		case 5:
			meshName = meshName + "2";
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
			angle = 180;
			break;
		case 9:
			meshName = meshName + "4";
			angle = 0;
			break;
		case 10:
			meshName = meshName + "2";
			angle = 90;
			break;
		case 11:
			meshName = meshName + "3";
			angle = 90;
			break;
		case 12:
			meshName = meshName + "2";
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
		((*mTerrainBlocks)[GX][GZ])->setBlockType(blockType,trrianType,index);
		((*mTerrainBlocks)[GX][GZ])->setTerrainAsPlane(-2);
		if(rand()%10 >5)
			meshName = meshName + "_1";
		else
			meshName = meshName + "_2";
		((*mTerrainBlocks)[GX][GZ])->setTerrainAsMesh(meshName,angle);
		((*mTerrainBlocks)[GX][GZ])->setMeshMaterial(materialName);
		if(blockType == HighGround)
		{
			mGrid->SetHighGround(GX-1,GZ-1,0x08);
			mGrid->SetHighGround(GX,GZ-1,0x04);
			mGrid->SetHighGround(GX-1,GZ,0x01);
			mGrid->SetHighGround(GX,GZ,0x02);
		}
		else
		{
			mGrid->SetLowGround(GX-1,GZ-1,0x08);
			mGrid->SetLowGround(GX,GZ-1,0x04);
			mGrid->SetLowGround(GX-1,GZ,0x01);
			mGrid->SetLowGround(GX,GZ,0x02);
		}
	}
}

BlockType GroundEditor::getTileBlockType(int GX,int GZ)
{
	/*
	if (((*mTerrainBlocks)[GX][GZ])->getBlockType() != LowGround)
	{
		int index = ((*mTerrainBlocks)[GX][GZ])->getBlockMeshIndex();
		if ((index & 4) > 0 )
			return ((*mTerrainBlocks)[GX][GZ])->getBlockType();
	}
	*/
	return ((*mTerrainBlocks)[GX][GZ])->getBlockType(BottomRight);
}

GroundType GroundEditor::getTileTerrianType(int GX,int GZ)
{
	return ((*mTerrainBlocks)[GX][GZ])->getTerrianType(BottomRight);
}

void GroundEditor::changeHighGroundPlane(int GX,int GZ,GroundType trrianType)
{
	GroundType  cliffType;
	cliffType = isHighGroundPlane( GX, GZ);
	if(cliffType!=GroundDisable)
	{
		((*mTerrainBlocks)[GX][GZ]) ->setPlaneMaterial(trrianType,BottomRight);
		((*mTerrainBlocks)[GX+1][GZ]) ->setPlaneMaterial(trrianType,BottomLeft);
		((*mTerrainBlocks)[GX][GZ+1]) ->setPlaneMaterial(trrianType,TopRight);
		((*mTerrainBlocks)[GX+1][GZ+1]) ->setPlaneMaterial(trrianType,TopLeft);
	}
}

GroundType GroundEditor::isHighGroundPlane(int GX,int GZ)
{
	GroundType cliffType = GreenLand;
	if(((*mTerrainBlocks)[GX][GZ])->getBlockType() != HighGround || ((*mTerrainBlocks)[GX][GZ])->getBlockMeshIndex() != 15)
		cliffType = GroundDisable;
	if(((*mTerrainBlocks)[GX+1][GZ])->getBlockType() != HighGround || ((*mTerrainBlocks)[GX+1][GZ])->getBlockMeshIndex() != 15)
		cliffType = GroundDisable;
	if(((*mTerrainBlocks)[GX][GZ+1])->getBlockType() != HighGround || ((*mTerrainBlocks)[GX][GZ+1])->getBlockMeshIndex() != 15)
		cliffType = GroundDisable;
	if(((*mTerrainBlocks)[GX+1][GZ+1])->getBlockType() != HighGround || ((*mTerrainBlocks)[GX+1][GZ+1])->getBlockMeshIndex() != 15)
		cliffType = GroundDisable;
	if(cliffType == GroundDisable)
		return cliffType;
	else
	{
		int gz = GZ;
		while(gz >= 0)
		{
			if(((*mTerrainBlocks)[GX][gz])->getBlockType() == HighGround && ((*mTerrainBlocks)[GX][gz])->getBlockMeshIndex() < 15)
				return ((*mTerrainBlocks)[GX][gz])->getTerrianType(BottomRight);
			else
				gz--;
		}
		return GroundDisable;
	}
}

void GroundEditor::setRamp(int GX,int GZ)
{
	mRamp->setRamp(GX,GZ);
}
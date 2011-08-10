/*
 * 文件名:Common.h
 * 创建时间:2010:10:14   16:09
 * 编写者:winsock
 * 功能:  全局公共定义文件
 */

#pragma once

const int MAX_MAPSIZE=64;//地图最大64*64

enum EditorID//编辑器ID
{
	NoneID,
	BlockID,
	GroundID
};

enum GridID
{
	MainGrid,
	SecGrid
};

enum EditorMode//编辑器编辑模式
{
	PutMode,//放置模式
	RemoveMode//移除模式
};

enum MouseButton//鼠标按键
{
	LeftButton,
	MidButton,
	RightButton
};

enum ConerType//地形图层位置
{
	TopRight = 0,
	TopLeft = 1,
	BottomLeft = 2,
	BottomRight = 3,
	ConerTypeCount=4
};

enum GroundType//贴图
{
	GroundDisable=-1,
	GreenLand = 0,
	Desert = 1,
	Swamp = 2,
	Snow = 3
};

enum BlockType
{
	Water,
	LowGround,
	HighGround,
	HighGroundPlane,
	Ramp,
	Planish
};

enum QueryMark//查询掩码
{
	DEFAULT_QUERY_MARK=1<<1,
	ARROW_QUERY_MARK=1<<2
};

static const int DefaultHeight=0;//默认高度
static const int VERTEX_POS_BINDING=0;//顶点位置绑定位置
static const int VERTEX_UV_BINDING=1;//贴图坐标绑定位置
static const int TEXTURE_COUNT=4;//贴图坐标数
static const int VERTEX_QUAD = 4;//每一个地形块拥有的顶点数
static const int VERTEX_PREQUAD = 6;//每一个地形块的索引数

static const float TEXTURE_SIZE=512.0f;//贴图大小
static const float TEXTURE_BLOCK_SIZE=128.0f;//贴图块大小

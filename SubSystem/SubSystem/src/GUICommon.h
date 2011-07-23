#pragma once

#include <string>

enum GUIImageLayer
{
	EffectsLayer,
	LeftLayer,
	MidLayer,
	RightLayer,
	BackGroundLayer,
	AllLayer
};

struct GUIDialogAttribute
{
	unsigned int TextLeft;
	unsigned int TextTop;
	unsigned int TextWidth;
	unsigned int TextHeight;

	std::string TextBgImage;
	unsigned int TextBgLeft;
	unsigned int TextBgTop;
	unsigned int TextBgWidth;
	unsigned int TextBgHeight;

	unsigned int RoleNameLeft;
	unsigned int RoleNameTop;
	unsigned int RoleNameWidth;
	unsigned int RoleNameHeight;

	float TextRed;
	float TextGreen;
	float TextBlue;

	float RoleNameRed;
	float RoleNameGreen;
	float RoleNameBlue;

	std::string TextFont;
	std::string RoleFont;
};

struct GUIImageAttribute
{
	unsigned int LeftLayerX;
	unsigned int LeftLayerY;
	unsigned int MidLayerX;
	unsigned int MidLayerY;
	unsigned int RightLayerX;
	unsigned int RightLayerY;
};

enum GUISceneType
{
	NoneScene,
	StageScene,
	MenuScene,
	PUDebugScene,
	LoadingScene,
	BattleScene,
	SLScene,
	MenuWindowsScene,
	MessageBoxScene
};

#define DefaultDialogVisibleTime 0.5//默认对话框渐出时间
#define DefaultRoleNameVisibleTime 0.1//默认角色名渐变时间
#define DefaultShowTextTime 0.1//默认打字效果速度
#define DefaultCursorTime 0.01//默认光标闪烁频率
#define LineCursorFileName "LineCursor.png"//默认行光标文件名
#define PageCursorFileName "PageCursor.png"//默认换页光标文件名

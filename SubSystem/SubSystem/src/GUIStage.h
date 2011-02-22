#pragma once

#include "GUIScene.h"

class GUIStage:public GUIScene
{
public:
	GUIStage(int width,int height);
	~GUIStage(void);

	void showScene();//显示场景
	void hideScene();//隐藏场景

	//帧事件	
	void FrameEvent();

	void showImage( std::string imageName,GUIImageLayer layer,float time,int left,int top);//在图层上显示图片

	void showText( std::wstring text,float delay);//显示文字

	void clearText();//清空文本

	void showOtherText();//在打字状态下,直接显示余下的文本

	void showRoleName( std::wstring text );//显示角色名

	void setTextDialog(const GUIDialogAttribute& attribute);//设置对话框
	void setTextDialogVisible(bool visible);

	void setCheckMouseDown();//检查鼠标是否按下

	bool CheckMouseState();//返回是否按下了鼠标

	void showTextCursor(bool isLine);

	void hideTextCursor();

	void waitTime( float time );

	GUISceneType getType()
	{
		return StageScene;
	}

	//当前定时器的工作
	enum TimerWork
	{
		NoneWork,
		PrinterWork,//打字机效果
		UniversalWork,//过渡效果
		DialogVisible,//对话框显隐
		WaitWork,//等待
		RoleNameWork,//名字渐变
		ClearAllRoleWork//清除所有的角色图片
	};
	TimerWork mTimerWork;

private:

	void eventMouseButtonClick(MyGUI::Widget* _sender);
	
	int mTextX;
	int mTextY;

	bool mCheckMouseDown;
	bool mIsMouseDown;

	std::wstring mTextBuffer;//文本缓冲

	MyGUI::Timer mTimer;//定时器
	float mTickTime;//单次触发时间

	float mSetp;//渐变步
	bool mSetpDirection;//渐变步的方向,true为正方向
	MyGUI::ImageBox* mUniversalLayer;//当前使用的渐变层
	MyGUI::ImageBox* mScrLayer;//当前被执行渐变的层
	std::string mTextureName;//目标贴图名

	MyGUI::ImageBox* mBackGroundGroup;
	MyGUI::ImageBox* mBackGround;
	MyGUI::ImageBox* mBackGroundUniversal;

	MyGUI::ImageBox* mLeftLayerGroup;
	MyGUI::ImageBox* mLeftLayer;
	MyGUI::ImageBox* mLeftLayerUniversal;

	MyGUI::ImageBox* mMidLayerGroup;
	MyGUI::ImageBox* mMidLayer;
	MyGUI::ImageBox* mMidLayerUniversal;

	MyGUI::ImageBox* mRightLayerGroup;
	MyGUI::ImageBox* mRightLayer;
	MyGUI::ImageBox* mRightUniversal;

	MyGUI::ImageBox* mTextBoxBG;
	MyGUI::EditBox* mTextBox;
	MyGUI::EditBox* mRoleName;
	MyGUI::EditBox* mRoleNameUniversal;
	MyGUI::ImageBox* mTextCursor;

	MyGUI::ImageBox* mEffectLayer;

};

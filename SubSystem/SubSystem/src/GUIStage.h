#pragma once

#include "GUIScene.h"

class GUIStage:public GUIScene
{
public:
	GUIStage(int width,int height);
	~GUIStage(void);

	void showScene(std::string arg);//显示场景
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

	void onOtherSceneNotify(std::string arg);

	GUISceneType getType()
	{
		return StageScene;
	}

	bool mIsFastForward;

private:

	void eventMouseButtonClick(MyGUI::Widget* _sender);
	void keyPressed(const OIS::KeyEvent &arg);
	void keyReleased(const OIS::KeyEvent &arg);

	void onSave(MyGUI::Widget* _sender);
	void onLoad(MyGUI::Widget* _sender);
	void onHide(MyGUI::Widget* _sender);
	void onSystem(MyGUI::Widget* _sender);

	void load();

	void loadComplete();

	void returnScene();

	void fastForward(bool value);

	void UIInit();
	
	int mTextX;
	int mTextY;

	bool mCheckMouseDown;
	bool mIsMouseDown;

	std::wstring mTextBuffer;//文本缓冲

	MyGUI::ImageBox* mUniversalLayer;//当前使用的渐变层
	MyGUI::ImageBox* mScrLayer;//当前被执行渐变的层
	std::string mTextureName;//目标贴图名

	MyGUI::ImageBox* mBackGroundGroup;
	MyGUI::ImageBox* mBackGround;
	MyGUI::ImageBox* mBackGroundUniversal;
	std::string mBackGroundImageName;

	MyGUI::ImageBox* mLeftLayerGroup;
	MyGUI::ImageBox* mLeftLayer;
	MyGUI::ImageBox* mLeftLayerUniversal;
	std::string mLeftImageName;

	MyGUI::ImageBox* mMidLayerGroup;
	MyGUI::ImageBox* mMidLayer;
	MyGUI::ImageBox* mMidLayerUniversal;
	std::string mMidImageName;

	MyGUI::ImageBox* mRightLayerGroup;
	MyGUI::ImageBox* mRightLayer;
	MyGUI::ImageBox* mRightUniversal;
	std::string mRightImageName;

	MyGUI::ImageBox* mTextBoxBG;
	MyGUI::EditBox* mTextBox;
	MyGUI::EditBox* mRoleName;
	MyGUI::EditBox* mRoleNameUniversal;
	MyGUI::ImageBox* mTextCursor;
	bool mTextCursorType;
	bool mTextBoxVisible;

	MyGUI::ImageBox* mEffectLayer;

	MyGUI::Button* mSaveButton;
	MyGUI::Button* mLoadButton;
	MyGUI::Button* mHideButton;
	MyGUI::Button* mSystemButton;

};

class GUIStageFactory:
	public GUISceneFactory
{
public:
	GUIStageFactory(){}

	~GUIStageFactory(){}

	GUIScene* CreateScene(int Width,int Height)
	{
		return new GUIStage(Width,Height);
	}
};
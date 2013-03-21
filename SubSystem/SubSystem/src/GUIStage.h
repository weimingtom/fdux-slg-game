#pragma once

#include "GUIScene.h"

class GUISLWindow;

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

	void shockImage(GUIImageLayer layer,float durationTime,float amplitudeX,float amplitudeY);//震动图片

	void moveImage(GUIImageLayer layer,float time,int left,int top);

	void showText( std::wstring text,float delay);//显示文字

	void changeShowTextOptionTime();

	void clearText();//清空文本

	void showOtherText();//在打字状态下,直接显示余下的文本

	void showRoleName( std::wstring text );//显示角色名

	void setTextDialog(const GUIDialogAttribute& attribute);//设置对话框
	void setTextDialogVisible(bool visible);
	void setButtonLock(bool visible);

	void setCheckMouseDown();//检查鼠标是否按下

	bool CheckMouseState();//返回是否按下了鼠标

	void showTextCursor(bool isLine);

	void hideTextCursor();

	void waitTime( float time );

	void onOtherSceneNotify(std::string arg);

	void saveData(bool isAutoSave);

	void setHistoryBoxVisible(bool visible);

	void setIsShowSupplyButton(bool visible);

	void setSupplyTips();

	void eventSupplyTipsFade(MyGUI::Widget* _sender);

	void resetAutoTimer(){mAutoTimer.reset();isClearAutoTimer=true;}

	void addToHistoryBox(std::wstring text);

	GUISceneType getType()
	{
		return StageScene;
	}

	bool mIsFastForward;

	//当前定时器的工作
	enum TimerWork
	{
		NoneWork,
		PrinterWork,//打字机效果
		UniversalWork,//过渡效果
		FadeInOutWork,//对话框显隐
		WaitWork,//等待
		RoleNameWork,//名字渐变
		ClearAllRoleWork,//清除所有的角色图片
		MoveWork,//移动图片
		ShockWork//震动图片
	};
	TimerWork mTimerWork;

private:

	MyGUI::Timer mTimer;//定时器
	MyGUI::Timer mAutoTimer;//自动等待计时器
	bool isClearAutoTimer;
	float mTickTime;//单次触发时间

	void eventMouseButtonClick(MyGUI::Widget* _sender);
	void eventHistoryBoxExit(MyGUI::Widget* _sender);
	void getMouseState();
	void keyPressed(const OIS::KeyEvent &arg);
	void keyReleased(const OIS::KeyEvent &arg);

	void onSave(MyGUI::Widget* _sender);
	void onLoad(MyGUI::Widget* _sender);
	void onHide(MyGUI::Widget* _sender);
	void onSystem(MyGUI::Widget* _sender);
	void onHistory( MyGUI::Widget* _sender );
	void onAuto( MyGUI::Widget* _sender );
	void onSupply( MyGUI::Widget* _sender );

	void load();

	void loadComplete();

	void returnScene();

	void fastForward();

	void UIInit(std::string arg);

	void buttonLock(bool lock);

	bool isCanFastForward();
	bool isCanAuto();
	bool isCanClick();

	int mTextX;
	int mTextY;

	bool mCheckMouseDown;
	bool mIsMouseDown;
	bool mIsAuto;

	GUISLWindow* SLWindow;

	float mShowTextOptionTime;//用户调节显示文本时间
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
	bool mIsCanShowTextBox;
	bool mIsCanShowButton;

	MyGUI::EditBox* mHistoryBox;
	MyGUI::ImageBox* mHistoryBoxExit;
	std::wstring mCurrentRoleName;
	std::wstring mHistoryText;
	int mLeftOffect;

	MyGUI::ImageBox* mEffectLayerGroup;
	MyGUI::ImageBox* mEffectLayer;
	MyGUI::ImageBox* mEffectLayerUniversal;

	MyGUI::ImageBox* mInputGroup;
	MyGUI::ImageBox* mInputLayer;
	MyGUI::Button* mSaveButton;
	MyGUI::Button* mLoadButton;
	MyGUI::Button* mHideButton;
	MyGUI::Button* mSystemButton;
	MyGUI::Button* mHistoryButton;
	MyGUI::Button* mAutoButton;
	MyGUI::Button* mSupplyButton;
	bool mIsShowSupplyButton;

	MyGUI::ImageBox* mSupplyTips;
	MyGUI::ControllerFadeAlpha* mTipsFadeController;
	bool mIsSupplyTipsFade;

	struct ShockParam
	{
		int mImageX;
		int mImageY;
		float mDurationTime;//持续时间
		float mAge;//当前时间
		float mAmplitudeX;//振幅
		float mAmplitudeY;//频率
	};
	
	ShockParam mShockParam;

	bool mIsMirrorMode;

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
#include "GUIStage.h"

#include "GUISystem.h"
#include "LuaSystem.h"

#include "AudioSystem.h"

#include <ogre.h>

#ifndef SCRIPT_EDITOR
#include "GUISLWindow.h"
#include "GUIMenuWindow.h"
#include "DataLibrary.h"
#include "StringTable.h"
#include <boost/format.hpp>
#endif

#define DefaultDialogVisibleTime 500//默认对话框渐出时间
#define DefaultRoleNameVisibleTime 100//默认角色名渐变时间
#define LineCursorFileName "LineCursor.png"//默认行光标文件名
#define PageCursorFileName "PageCursor.png"//默认换页光标文件名

#define SAVE_PATH "..\\save"

#ifndef SCRIPT_EDITOR
#include "timer.hpp"
#include "StateManager.h"
#else
#include "..\..\SLGGame\SLGGame\Src\timer.hpp"
#endif

GUIStage::GUIStage(int width,int height):GUIScene("Stage.layout",width,height),mCheckMouseDown(false),mIsMouseDown(false),mTextX(0),mTextY(0),mIsFastForward(false),SLWindow(NULL),mIsAuto(false),mLeftOffect(0),mIsCanShowTextBox(false),mIsCanShowButton(true),mIsShowSupplyButton(true)
{
	setSceneLanguage();

	assignWidget(mBackGroundGroup, "BackGroundGroup");
	assignWidget(mBackGround, "BackGround");
	assignWidget(mBackGroundUniversal, "BackGroundUniversal");

	assignWidget(mLeftLayerGroup, "LeftLayerGroup");
	assignWidget(mLeftLayer, "LeftLayer");
	assignWidget(mLeftLayerUniversal, "LeftLayerUniversal");

	assignWidget(mMidLayerGroup, "MidLayerGroup");
	assignWidget(mMidLayer, "MidLayer");
	assignWidget(mMidLayerUniversal, "MidLayerUniversal");

	assignWidget(mRightLayerGroup, "RightLayerGroup");
	assignWidget(mRightLayer, "RightLayer");
	assignWidget(mRightUniversal, "RightLayerUniversal");

	assignWidget(mTextBoxBG, "TextBoxBG");
	assignWidget(mTextBox, "TextBox");
	assignWidget(mRoleName, "RoleName");
	assignWidget(mRoleNameUniversal, "RoleNameUniversal");
	assignWidget(mTextCursor, "TextCursor");

	assignWidget(mEffectLayerGroup, "EffectLayerGroup");
	assignWidget(mEffectLayer, "EffectLayer");
	assignWidget(mEffectLayerUniversal, "EffectLayerUniversal");

	assignWidget(mHistoryBox, "HistoryBox");
	assignWidget(mHistoryBoxExit, "HistoryBoxExit");

	assignWidget(mInputGroup, "InputGroup");
	assignWidget(mInputLayer, "InputLayer");
	assignWidget(mSaveButton, "SaveButton");
	assignWidget(mLoadButton, "LoadButton");
	assignWidget(mHideButton,"HideButton");
	assignWidget(mSystemButton,"SystemButton");
	assignWidget(mHistoryButton,"HistoryButton");
	assignWidget(mAutoButton,"AutoButton");
	assignWidget(mSupplyButton,"Supprot");

#ifndef SCRIPT_EDITOR
	mSaveButton->setCaption(StringTable::getSingletonPtr()->getString("SaveButton"));
	mLoadButton->setCaption(StringTable::getSingletonPtr()->getString("LoadButton"));
	mHideButton->setCaption(StringTable::getSingletonPtr()->getString("HideButton"));
	mSystemButton->setCaption(StringTable::getSingletonPtr()->getString("SystemButton"));
	mHistoryButton->setCaption(StringTable::getSingletonPtr()->getString("HistoryButton"));
	mAutoButton->setCaption(StringTable::getSingletonPtr()->getString("AutoButton"));
#endif

	mInputLayer->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::eventMouseButtonClick);
	mHistoryBoxExit->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::eventHistoryBoxExit);
	mSaveButton->eventMouseButtonClick+=MyGUI::newDelegate(this, &GUIStage::onSave);
	mLoadButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::onLoad);
	mHideButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::onHide);
	mSystemButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::onSystem);
	mHistoryButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::onHistory);
	mAutoButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::onAuto);
	mSupplyButton->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::onSupply);

	changeShowTextOptionTime();
}

GUIStage::~GUIStage(void)
{
#ifndef SCRIPT_EDITOR
	if (SLWindow!=NULL)
	{
		SLWindow->setCallScene(SLWindow);
	}
	//AudioSystem::getSingletonPtr()->stopStream(1000);
#endif
}

void GUIStage::UIInit(std::string arg)
{
	mBackGroundGroup->setSize(mWidth,mHeigth);//设置背景大小
	mBackGround->setSize(mWidth,mHeigth);
	mBackGroundUniversal->setSize(mWidth,mHeigth);

	mLeftLayerGroup->setSize(mWidth,mHeigth);//设置左大小
	mMidLayerGroup->setSize(mWidth,mHeigth);//设置中大小
	mRightLayerGroup->setSize(mWidth,mHeigth);//设置右大小
	mEffectLayerGroup->setSize(mWidth,mHeigth);

	mInputGroup->setSize(mWidth,mHeigth);
	mInputLayer->setSize(mWidth,mHeigth);

	mTextBoxBG->setSize(mWidth,mHeigth);//TextBoxBG
	mEffectLayer->setSize(mWidth,mHeigth);//EFLayer
	mEffectLayerUniversal->setSize(mWidth,mHeigth);//EFLayer

	mBackGround->setAlpha(1);
	mBackGroundUniversal->setImageTexture("");
	mLeftLayer->setAlpha(1);
	mLeftLayerUniversal->setImageTexture("");
	mMidLayer->setAlpha(1);
	mMidLayerUniversal->setImageTexture("");
	mRightLayer->setAlpha(1);
	mRightUniversal->setImageTexture("");
	mRoleName->setAlpha(1);
	mRoleNameUniversal->setCaption("");
	
	hideTextCursor();
#ifndef SCRIPT_EDITOR
	LuaSystem::getSingletonPtr()->executeFunction("AVGInit.lua",arg,"1");//运行界面初始设定
#endif
}

void GUIStage::showScene(std::string arg)
{
	UIInit(arg);
}

void GUIStage::hideScene()
{

}

void GUIStage::eventMouseButtonClick(MyGUI::Widget* _sender)
{
	getMouseState();
}

void GUIStage::eventHistoryBoxExit(MyGUI::Widget* _sender)
{
	setHistoryBoxVisible(false);
}

void GUIStage::keyPressed(const OIS::KeyEvent &arg )
{
	if(arg.key==OIS::KC_P)
	{
		int i;
		i=1;
	}

	if (arg.key==OIS::KC_LCONTROL)
	{
		mIsFastForward=true;
	}
	else if(arg.key==OIS::KC_SPACE || arg.key==OIS::KC_RETURN)
	{
		getMouseState();
	}
}

void GUIStage::keyReleased(const OIS::KeyEvent &arg )
{
	if (arg.key==OIS::KC_LCONTROL)
	{
		mIsFastForward=false;
	}
}

void GUIStage::getMouseState() 
{
	if (mCheckMouseDown && isCanClick())
	{
		mIsMouseDown=true;
		mCheckMouseDown=false;
	}

	if(!mTextBoxVisible && mIsCanShowTextBox)
	{
		setTextDialogVisible(true);
		mIsCanShowTextBox=false;
	}
}

void GUIStage::setCheckMouseDown()
{
	mCheckMouseDown=true;
	mIsMouseDown=false;
}

bool GUIStage::CheckMouseState()
{
	if (mIsFastForward||isCanAuto())
	{
		return true;
	}
	else
	{
		return mIsMouseDown;
	}
}


void GUIStage::setTextDialog( const GUIDialogAttribute& attribute )
{
	mTextBoxBG->setPosition(attribute.TextBgLeft,attribute.TextBgTop);
	mTextBoxBG->setSize(attribute.TextBgWidth,attribute.TextBgHeight);
	mTextBoxBG->setImageTexture(attribute.TextBgImage);

	mTextBox->setPosition(attribute.TextLeft,attribute.TextTop);
	mTextX=attribute.TextLeft;
	mTextY=attribute.TextTop;

	mTextBox->setSize(attribute.TextWidth,attribute.TextHeight);
	mTextBox->setTextColour(MyGUI::Colour(attribute.TextRed,attribute.TextGreen,attribute.TextBlue));
	mTextBox->setFontName(attribute.TextFont);

	mHistoryBox->setTextColour(MyGUI::Colour::White);
	mHistoryBox->setFontName(attribute.TextFont);

	mRoleName->setPosition(attribute.RoleNameLeft,attribute.RoleNameTop);
	mRoleName->setSize(attribute.RoleNameWidth,attribute.RoleNameHeight);
	mRoleName->setTextColour(MyGUI::Colour(attribute.RoleNameRed,attribute.RoleNameGreen,attribute.RoleNameBlue));
	mRoleName->setFontName(attribute.RoleFont);

	mRoleNameUniversal->setPosition(attribute.RoleNameLeft,attribute.RoleNameTop);
	mRoleNameUniversal->setSize(attribute.RoleNameWidth,attribute.RoleNameHeight);
	mRoleNameUniversal->setTextColour(MyGUI::Colour(attribute.RoleNameRed,attribute.RoleNameGreen,attribute.RoleNameBlue));
	mRoleNameUniversal->setFontName(attribute.RoleFont);
}


void GUIStage::setTextDialogVisible( bool visible )
{
	mTextBoxVisible=visible;

	if (visible)
	{
		FadeIn(DefaultDialogVisibleTime,mTextBoxBG);
	}
	else
	{
		FadeOut(DefaultDialogVisibleTime,mTextBoxBG);
	}

	mTimerWork=FadeInOutWork;
	
	if (visible)
	{
		buttonLock(mIsCanShowButton);
	}
	else
	{
		buttonLock(false);
	}
	
}

void GUIStage::setHistoryBoxVisible( bool visible )
{
	if (visible)
	{
		mInputGroup->setVisible(false);
		mHistoryBox->addText(mHistoryText);
		mHistoryText.clear();
	}
	else
	{
		mInputGroup->setVisible(true);
	}

	mHistoryBox->setVisible(visible);
	mHistoryBoxExit->setVisible(visible);
	setTextDialogVisible(!visible);
}

void GUIStage::addToHistoryBox(std::wstring text)
{
	int RoleNameLength=0;
	if(!mCurrentRoleName.empty())
	{
		//mHistoryBox->addText();
		
		mHistoryText+=std::wstring(L"#FF0000")+mCurrentRoleName+std::wstring(L"#FFFFFF : ");
		RoleNameLength=mCurrentRoleName.length()+3;
		mCurrentRoleName.clear();
	}

	//MyGUI::IntPoint p=mHistoryBox->getTextCursorPos();

	int lineTextNum=(mHistoryBox->getWidth()-mLeftOffect-30)/25;

	if (lineTextNum>text.length())
	{
		mHistoryText+=text;
		if (text!=L"\n")
		{
			mLeftOffect+=(RoleNameLength+text.length())*25;
		}
		else
		{
			mLeftOffect=0;
		}
	}
	else
	{
		int offset;
		text.insert(lineTextNum-RoleNameLength,L"\n");
		offset=lineTextNum-RoleNameLength;

		lineTextNum=(mHistoryBox->getWidth()-30)/25;

		int j=(text.length()-offset)/lineTextNum;

		for (int i=0;i<j;i++)
		{
			offset+=lineTextNum;
			text.insert(offset,L"\n");
		}

		mLeftOffect=text.length()-offset;

		mHistoryText+=text;
	}
}

void GUIStage::waitTime( float time )
{
	mTimerWork=WaitWork;
	mTickTime=time;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::changeShowTextOptionTime()
{
#ifndef SCRIPT_EDITOR
	int TextSpeed;
	DataLibrary::getSingletonPtr()->getData("SystemConfig/TextSpeed",TextSpeed);
	mShowTextOptionTime=50.0/TextSpeed;
#endif
}

void GUIStage::showText( std::wstring text,float delay)
{
	Timer t;
	t.reset();
	addToHistoryBox(text);
	std::cout<<"addToHistoryBox:"<<t.getMilliseconds()<<std::endl;

	if(delay==0)
	{
		mTextBox->addText(text);
	}
	else
	{
		//如果是打字效果,那么启动打字定时器
		mTextBuffer=text;
		mTimerWork=PrinterWork;
		mTickTime=delay*1000*mShowTextOptionTime;

		//开始帧更新
		mTimer.reset();
		GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
	}
}

void GUIStage::showOtherText()
{
	//停止帧更新
	mTickTime=0;
	mTimerWork=NoneWork;
	GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);

	MyGUI::IntPoint p=mTextBox->getTextCursorPos();

	int lineTextNum=(mTextBox->getWidth()-p.left+mTextBox->getLeft()+mTextBoxBG->getLeft())/25;

	if (lineTextNum>mTextBuffer.length())
	{
		mTextBox->addText(mTextBuffer);
	}
	else
	{
		mTextBox->addText(mTextBuffer.substr(0,lineTextNum));
		mTextBuffer.erase(0,lineTextNum);

		lineTextNum=(mTextBox->getWidth())/25;

		for (int i=0;i<=(mTextBuffer.length()/lineTextNum);i++)
		{
			mTextBox->addText("\n");
			mTextBox->addText(mTextBuffer.substr(0,lineTextNum));
			mTextBuffer.erase(0,lineTextNum);
		}
	}

	//while(!mTextBuffer.empty())
	//{
	//	std::wstring subString=mTextBuffer.substr(0,1);
	//	mTextBox->addText(subString);
	//	if (mTextBox->getHScrollPosition()!=0)//自动换行
	//	{
	//		int length=mTextBox->getTextLength();
	//		mTextBox->eraseText(length-1);
	//		mTextBox->addText("\n");
	//		mTextBox->addText(subString);
	//	}
	//	mTextBuffer.erase(mTextBuffer.begin());
	//}
	mTextBuffer.clear();
}

void GUIStage::showImage( std::string imageName,GUIImageLayer layer,float time,int left,int top)
{

	//选择图层

	switch(layer)
	{
	case EffectsLayer:
		{
			mEffectLayerGroup->setVisible(true);
			mScrLayer=mEffectLayer;
			mUniversalLayer=mEffectLayerUniversal;
		}
	case LeftLayer:
		{
			mScrLayer=mLeftLayer;
			mUniversalLayer=mLeftLayerUniversal;
			mLeftImageName=imageName;
			break;
		}
	case MidLayer:
		{
			mScrLayer=mMidLayer;
			mUniversalLayer=mMidLayerUniversal;
			mMidImageName=imageName;
			break;
		}
	case RightLayer:
		{
			mScrLayer=mRightLayer;
			mUniversalLayer=mRightUniversal;
			mRightImageName=imageName;
			break;
		}
	case BackGroundLayer:
		{
			mScrLayer=mBackGround;
			mUniversalLayer=mBackGroundUniversal;
			mBackGroundImageName=imageName;
			break;
		}
	case AllLayer://如果为清除所有的人物
		{
			mTimerWork=ClearAllRoleWork;
			
			FadeOut(time,mLeftLayer);
			FadeOut(time,mMidLayer);
			FadeOut(time,mRightLayer);

			GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);

			return;
		}
	}

	//预先加载,获取图片的宽高

	int width,height=0;

	if (!imageName.empty())
	{
		if(!Ogre::TextureManager::getSingleton().resourceExists(imageName))
		{
			Ogre::Image i;
			i.load(imageName,"GUI");
			width=i.getWidth();
			height=i.getHeight();
		}
		else
		{
			width=((Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(imageName))->getWidth();
			height=((Ogre::TexturePtr)Ogre::TextureManager::getSingleton().getByName(imageName))->getHeight();
		}
	}

	if (mScrLayer!=NULL)
	{
		mScrLayer->setPosition(left,top);
		mUniversalLayer->setPosition(left,top);
		if (!imageName.empty())//如果名字为空的话...那么不调整大小
		{
			mScrLayer->setSize(width,height);
			mUniversalLayer->setSize(width,height);
		}


		if (time!=0)//如果要使用渐变进入
		{
			mUniversalLayer->setImageTexture(imageName);

			if(layer==LeftLayer)
				mIsMirrorMode=true;
			else
				mIsMirrorMode=false;

			if(mIsMirrorMode)
				mUniversalLayer->getSubWidgetMain()->_setUVSet(MyGUI::FloatRect(1,0,0,1));;

			mTimerWork=UniversalWork;
			mTextureName=imageName;

			mScrLayer->setAlpha(1);
			mUniversalLayer->setAlpha(0);
			
			FadeOut(time,mScrLayer);
			FadeIn(time,mUniversalLayer);
			GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
		}
		else
		{
			mScrLayer->setImageTexture(imageName);
			if(layer==LeftLayer)
				mScrLayer->getSubWidgetMain()->_setUVSet(MyGUI::FloatRect(1,0,0,1));
		}

	}
}

void GUIStage::moveImage(GUIImageLayer layer,float time,int left,int top)
{
	switch(layer)
	{
	case LeftLayer:
		{
			mScrLayer=mLeftLayer;
			mUniversalLayer=mLeftLayerUniversal;
			break;
		}
	case MidLayer:
		{
			mScrLayer=mMidLayer;
			mUniversalLayer=mMidLayerUniversal;
			break;
		}
	case RightLayer:
		{
			mScrLayer=mRightLayer;
			mUniversalLayer=mRightUniversal;
			break;
		}
	case BackGroundLayer:
		{
			mScrLayer=mBackGround;
			mUniversalLayer=mBackGroundUniversal;
			break;
		}
	}

	mTimerWork=MoveWork;
	mUniversalLayer->setPosition(left,top);
	mUniversalLayer->setVisible(false);
	MoveTo(left,top,time,mScrLayer);
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);

}

void GUIStage::shockImage(GUIImageLayer layer,float durationTime,float amplitudeX,float amplitudeY)
{
	switch(layer)
	{
	case LeftLayer:
		{
			mScrLayer=mLeftLayer;
			mUniversalLayer=mLeftLayerUniversal;
			break;
		}
	case MidLayer:
		{
			mScrLayer=mMidLayer;
			mUniversalLayer=mMidLayerUniversal;
			break;
		}
	case RightLayer:
		{
			mScrLayer=mRightLayer;
			mUniversalLayer=mRightUniversal;
			break;
		}
	case BackGroundLayer:
		{
			mScrLayer=mBackGround;
			mUniversalLayer=mBackGroundUniversal;
			break;
		}
	}

	mUniversalLayer->setVisible(false);
	mShockParam.mImageX=mScrLayer->getLeft();
	mShockParam.mImageY=mScrLayer->getTop();
	mShockParam.mAge=0;
	mShockParam.mDurationTime=durationTime;
	mShockParam.mAmplitudeX=amplitudeX;
	mShockParam.mAmplitudeY=amplitudeY;

	mTimerWork=ShockWork;
	mTickTime=1;
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);

}

void GUIStage::showRoleName( std::wstring text )
{
	mCurrentRoleName=text;
	mRoleNameUniversal->setCaption(text);
	mRoleNameUniversal->setAlpha(0);
	mRoleName->setAlpha(1);

	mTimerWork=RoleNameWork;

	FadeIn(DefaultRoleNameVisibleTime,mRoleNameUniversal);
	FadeOut(DefaultRoleNameVisibleTime,mRoleName);
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::clearText()
{
	mTextBox->setCaption("");
	addToHistoryBox(L"\n");
}

bool GUIStage::isCanFastForward()
{
	if (mTimerWork==FadeInOutWork)
	{
		return false;
	}
	else if(mHistoryBox->getVisible())
	{
		return false;
	}
/*	else if (!mTextBoxVisible)
	{
		return false;
	}*/
	else if (SLWindow!=NULL)
	{
		return false;
	}
	else if(mHistoryBox->getVisible())
	{
		return false;
	}

	return true;
}

bool GUIStage::isCanAuto()
{
	if (!mIsAuto)
	{
		return false;
	}
	else if (mTimerWork!=NoneWork)
	{
		return false;
	}
	else if (!mTextBoxVisible)
	{
		return false;
	}
	else if (SLWindow!=NULL)
	{
		return false;
	}
	else if(mHistoryBox->getVisible())
	{
		return false;
	}

	return true;
}

bool GUIStage::isCanClick()
{
	return isCanFastForward();
}

void GUIStage::fastForward()
{
	if (!isCanFastForward())
	{
		mIsFastForward=false;
		return;
	}

	switch(mTimerWork)
	{
	case PrinterWork:
		{
			showOtherText();
			break;
		}
	case MoveWork:
		{
			StopMoveTo(mScrLayer);
			break;
		}
	case ShockWork:
		{
			mShockParam.mAge =mShockParam.mDurationTime+1;
			break;
		}
	case UniversalWork:
		{
			StopFadeOut(mScrLayer);
			StopFadeIn(mUniversalLayer);
			break;
		}
	case WaitWork:
		{
			mTickTime=1;
			break;
		}
	case RoleNameWork:
		{
			StopFadeOut(mRoleName);
			StopFadeIn(mRoleNameUniversal);
			break;
		}
	case ClearAllRoleWork:
		{
			StopFadeOut(mLeftLayer);
			StopFadeOut(mMidLayer);
			StopFadeOut(mRightLayer);
			break;
		}
	}
}

void GUIStage::FrameEvent()
{
	if (mIsFastForward)
	{
		fastForward();
	}

	if(mTickTime!=0)
	{
		if (mTimer.getMilliseconds()>=mTickTime )
		{
			switch(mTimerWork)
			{
				case PrinterWork:
				{
					if (!mTextBuffer.empty())
					{
						mTextBox->addText(mTextBuffer.substr(0,1));
						if (mTextBox->getHScrollPosition()!=0)//自动换行
						{
							int length=mTextBox->getTextLength();
							mTextBox->eraseText(length-1);
							mTextBox->addText("\n");
							mTextBox->addText(mTextBuffer.substr(0,1));
						}
						mTextBuffer.erase(mTextBuffer.begin());
					}
					else
					{
						//停止帧更新
						mTickTime=0;
						mTimerWork=NoneWork;
						GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
					}
					break;
				}
				case WaitWork:
					{
						//停止帧更新
						mTickTime=0;
						mTimerWork=NoneWork;
						GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);

						break;
					}
				case ShockWork:
					{
						// 记录当前累计震动时间
						mShockParam.mAge += mTimer.getMilliseconds() / 1000.0;

						// 若超时则归位
						if(mShockParam.mAge >mShockParam.mDurationTime)
						{
							mScrLayer->setPosition(mShockParam.mImageX,mShockParam.mImageY);
							mUniversalLayer->setVisible(true);
							//停止帧更新
							mTickTime=0;
							mTimerWork=NoneWork;
							GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
						}
						else
						{
							// 按照公式求偏移量
							
							int x,y=0;

							if (mShockParam.mAmplitudeX!=0)
								x=int(((float)rand())/RAND_MAX * mShockParam.mAmplitudeX - mShockParam.mAmplitudeX);

							if (mShockParam.mAmplitudeY!=0)
								y= int(((float)rand())/RAND_MAX * mShockParam.mAmplitudeY - mShockParam.mAmplitudeY);

							// 进行偏移产生震动效果
							mScrLayer->setPosition(mShockParam.mImageX+x,mShockParam.mImageY+y);
						}

						break;
					}
			}

			//复位定时器
			mTimer.reset();
		}
	}
}

void GUIStage::onOtherSceneNotify(std::string arg)
{
	if(arg=="LoadSelect")
	{
		load();
	}
	else if(arg=="LoadComplete")
	{
		loadComplete();
		SLWindow=NULL;
	}
	else if (arg=="Return")
	{
		returnScene();
		SLWindow=NULL;
	}
	else if(arg=="FadeInOver")
	{
		switch(mTimerWork)
		{
		case FadeInOutWork:
			{
				//buttonLock(true);
				mTimerWork=NoneWork;
				break;
			}
		}

	}
	else if(arg=="FadeOutOver")
	{
		switch(mTimerWork)
		{
		case ClearAllRoleWork:
			{
				mLeftLayer->setImageTexture("");
				mLeftLayer->setAlpha(1.0);
				mLeftLayerUniversal->setImageTexture("");
				mLeftLayerUniversal->setAlpha(1.0);
				mMidLayer->setImageTexture("");
				mMidLayer->setAlpha(1.0);
				mMidLayerUniversal->setImageTexture("");
				mMidLayerUniversal->setAlpha(1.0);
				mRightLayer->setImageTexture("");
				mRightLayer->setAlpha(1.0);
				mRightUniversal->setImageTexture("");
				mRightUniversal->setAlpha(1.0);
				break;
			}
		case FadeInOutWork:
			{
				//buttonLock(true);
				break;
			}
		case RoleNameWork:
			{
				std::string s=mRoleNameUniversal->getCaption();
				mRoleName->setCaption(s);
				mRoleName->setAlpha(1);
				mRoleNameUniversal->setAlpha(0);
				break;
			}
		case UniversalWork:
			{
				mScrLayer->setImageTexture(mTextureName);
				mScrLayer->setAlpha(1);
				if(mIsMirrorMode)
					mScrLayer->getSubWidgetMain()->_setUVSet(MyGUI::FloatRect(1,0,0,1));
				mUniversalLayer->setAlpha(0);
				if (mEffectLayerGroup->getVisible())
				{
					mEffectLayerGroup->setVisible(false);
				}
				break;
			}
		}

		mTimerWork=NoneWork;
		GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
	}
	else if(arg=="MoveToOver")
	{
		mScrLayer->setPosition(mUniversalLayer->getPosition());
		mUniversalLayer->setVisible(true);

		mTimerWork=NoneWork;
		GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
	}
	else if (arg=="ReturnFromSupply")
	{
		mInputGroup->setEnabled(true);
		mInputGroup->setVisible(true);
	}
}



void GUIStage::showTextCursor( bool isLine )
{
	MyGUI::IntPoint p=mTextBox->getTextCursorPos();

	int l=mTextBoxBG->getLeft();
	int t=mTextBoxBG->getTop();

	mTextCursor->setPosition(p.left-l,p.top-t);
	mTextCursor->setVisible(true);
	mTextCursor->setItemResource ("TextCursorImage");
	mTextCursorType=isLine;

	if(!isLine)
	{
		mTextCursor->setItemGroup("LineBreak");
	}
	else
	{
		mTextCursor->setItemGroup("PageBreak");
	}

	mTextCursor->setItemName("show");

}

void GUIStage::hideTextCursor()
{
	mTextCursor->setVisible(false);
}

void GUIStage::saveData(bool isAutoSave)
{
#ifndef SCRIPT_EDITOR
	//写入场景数据
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/GameState","AVG");
	//记录图层
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/BackGroundName",mBackGroundImageName);
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/BackGroundPosition",Ogre::Vector3(mBackGround->getLeft(),mBackGround->getTop(),0));
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/BackGroundSize",Ogre::Vector3(mBackGround->getWidth(),mBackGround->getHeight(),0));

	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/LeftName",mLeftImageName);
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/LeftPosition",Ogre::Vector3(mLeftLayer->getLeft(),mLeftLayer->getTop(),0));
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/LeftSize",Ogre::Vector3(mLeftLayer->getWidth(),mLeftLayer->getHeight(),0));

	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/MidName",mMidImageName);
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/MidPosition",Ogre::Vector3(mMidLayer->getLeft(),mMidLayer->getTop(),0));
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/MidSize",Ogre::Vector3(mMidLayer->getWidth(),mMidLayer->getHeight(),0));

	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/RightName",mRightImageName);
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/RightPosition",Ogre::Vector3(mRightLayer->getLeft(),mRightLayer->getTop(),0));
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/RightSize",Ogre::Vector3(mRightLayer->getWidth(),mRightLayer->getHeight(),0));

	//记录文本
	if (mTimerWork==PrinterWork)
	{
		std::wstring text=mTextBuffer;
		std::wstring temp=mTextBox->getCaption();
		while(!text.empty())
		{
			mTextBox->addText(text.substr(0,1));
			if (mTextBox->getHScrollPosition()!=0)//自动换行
			{
				int length=mTextBox->getTextLength();
				mTextBox->eraseText(length-1);
				mTextBox->addText("\n");
				mTextBox->addText(text.substr(0,1));
			}
			text.erase(text.begin());
		}

		DataLibrary::getSingletonPtr()->setData("GameData/StoryData/Text",mTextBox->getOnlyText());
		mTextBox->setCaption(temp);
	}
	else
	{
		DataLibrary::getSingletonPtr()->setData("GameData/StoryData/Text",mTextBox->getOnlyText());
	}

	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/RoleName",mRoleName->getOnlyText());
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/TextCursorType",mTextCursorType);

	//写入脚本名与位置
	LuaSystem::getSingletonPtr()->saveScriptRuntime();

	//写入音乐
	DataLibrary::getSingletonPtr()->setData("GameData/StoryData/MusicName",AudioSystem::getSingletonPtr()->mStreamName);

	if (isAutoSave)
	{
		//加入时间戳
		SYSTEMTIME systm;
		GetLocalTime(&systm);
		std::string timeString=str(boost::format(" %1%-%2%-%3% %4%:%5%:%6%")%systm.wYear%systm.wMonth%systm.wDay%systm.wHour%systm.wMinute%systm.wSecond);

		std::string mScriptName;
		DataLibrary::getSingletonPtr()->getData("GameData/StoryData/ScriptName",mScriptName);
		std::string::size_type j = mScriptName.find(".");
		mScriptName=mScriptName.substr(2, j-2);

		std::string  AutoSaveCapture=str(boost::format(StringTable::getSingletonPtr()->getString("AutoSaveCapture"))%mScriptName);

		DataLibrary::getSingletonPtr()->setData("SystemConfig/Save/Save1",AutoSaveCapture+timeString);
		DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::SystemConfig,std::string(SAVE_PATH)+std::string("\\Config.xml"));
		DataLibrary::getSingletonPtr()->saveXmlData(DataLibrary::GameData,std::string(SAVE_PATH)+std::string("\\save1.xml"));
	}
#endif
}

void GUIStage::onSave(MyGUI::Widget* _sender)
{
#ifndef SCRIPT_EDITOR
	saveData(false);

	SLWindow= (GUISLWindow*)GUISystem::getSingletonPtr()->createScene(SLScene);
	SLWindow->setCallScene(this);
	SLWindow->showScene("save");
#endif
}

void GUIStage::onLoad(MyGUI::Widget* _sender)
{
#ifndef SCRIPT_EDITOR
	SLWindow= (GUISLWindow*)GUISystem::getSingletonPtr()->createScene(SLScene);
	SLWindow->setCallScene(this);
	SLWindow->showScene("load");
#endif
}

void GUIStage::onHide( MyGUI::Widget* _sender )
{
	setTextDialogVisible(false);	
	mIsCanShowTextBox=true;
}

void GUIStage::onHistory( MyGUI::Widget* _sender )
{
	setHistoryBoxVisible(true);
}

void GUIStage::onAuto( MyGUI::Widget* _sender )
{
	mIsAuto=!mIsAuto;
}

void GUIStage::onSystem( MyGUI::Widget* _sender )
{
#ifndef SCRIPT_EDITOR
	GUIMenuWindow* menuWindow =static_cast<GUIMenuWindow *>(GUISystem::getSingletonPtr()->createScene(MenuWindowsScene));
	menuWindow->showScene("");
#endif
}

void GUIStage::onSupply( MyGUI::Widget* _sender )
{
#ifndef SCRIPT_EDITOR
	mInputGroup->setEnabled(false);
	mInputGroup->setVisible(false);
	StateManager::getSingletonPtr()->addAffixationState("AVG",StateManager::Supply);
#endif
}

void GUIStage::load()
{
#ifndef SCRIPT_EDITOR
	//读取场景数据
	//读取图层
	Ogre::Vector3 LayerPosition;
	Ogre::Vector3 LayerSize;
	std::string ImageName;

	UIInit("AVGInit");

	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/BackGroundName",ImageName);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/BackGroundPosition",LayerPosition);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/BackGroundSize",LayerSize);
	mBackGroundImageName=ImageName;
	mBackGround->setImageTexture(ImageName);
	mBackGround->setPosition(LayerPosition.x,LayerPosition.y);
	mBackGround->setSize(LayerSize.x,LayerSize.y);


	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/LeftName",ImageName);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/LeftPosition",LayerPosition);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/LeftSize",LayerSize);
	mLeftImageName=ImageName;
	mLeftLayer->setImageTexture(ImageName);
	mLeftLayer->setPosition(LayerPosition.x,LayerPosition.y);
	mLeftLayer->setSize(LayerSize.x,LayerSize.y);

	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/MidName",ImageName);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/MidPosition",LayerPosition);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/MidSize",LayerSize);
	mMidImageName=ImageName;
	mMidLayer->setImageTexture(ImageName);
	mMidLayer->setPosition(LayerPosition.x,LayerPosition.y);
	mMidLayer->setSize(LayerSize.x,LayerSize.y);

	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/RightName",ImageName);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/RightPosition",LayerPosition);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/RightSize",LayerSize);
	mRightImageName=ImageName;
	mRightLayer->setImageTexture(ImageName);
	mRightLayer->setPosition(LayerPosition.x,LayerPosition.y);
	mRightLayer->setSize(LayerSize.x,LayerSize.y);

	//设置文本
	mTextBuffer.clear();
	std::string text;
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/Text",text);
	mTextBox->setCaption(text);
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/RoleName",text);
	mRoleName->setCaption(text);
	int type;
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/TextCursorType",type);
	//showTextCursor(type);

	mTextBoxVisible=true;
	buttonLock(true);
	mTextBoxBG->setVisible(true);
	mTextBoxBG->setAlpha(1);

	//读取音乐
	
	DataLibrary::getSingletonPtr()->getData("GameData/StoryData/MusicName",text);
	if (text!="none" && text!="")
	{
		AudioSystem::getSingletonPtr()->playStream(text,true,1000);
	}

#endif
}

void GUIStage::loadComplete()
{
	//读取脚本名与位置
	LuaSystem::getSingletonPtr()->loadScripRuntime();
	returnScene();

}

void GUIStage::returnScene()
{
	if (mTimerWork!=NoneWork)
	{
		if (mTimerWork==PrinterWork)
		{
			mTimer.reset();
			GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
			if (mTextCursor->getVisible())
			{
				hideTextCursor();
			}
		}
		else
		{
			mTimerWork=NoneWork;
		}

	}
}

void GUIStage::buttonLock( bool lock )
{
	mSaveButton->setVisible(lock);
	mLoadButton->setVisible(lock);
	mHideButton->setVisible(lock);
	mSystemButton->setVisible(lock);
	mHistoryButton->setVisible(lock);
	mAutoButton->setVisible(lock);
	mSupplyButton->setVisible(lock && mIsShowSupplyButton);
}

void GUIStage::setButtonLock( bool visible )
{
	mIsCanShowButton=visible;
}

void GUIStage::setIsShowSupplyButton( bool visible )
{
	mIsShowSupplyButton=visible;
}


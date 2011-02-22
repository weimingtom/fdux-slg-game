#include "GUIStage.h"

#include "GUISystem.h"

#include <ogre.h>

GUIStage::GUIStage(int width,int height):GUIScene("Stage.layout"),mCheckMouseDown(false),mIsMouseDown(false),mTextX(0),mTextY(0)
{
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

	assignWidget(mEffectLayer, "EffectLayer");

	mBackGroundGroup->setSize(width,height);//设置背景大小
	mBackGround->setSize(width,height);
	mBackGroundUniversal->setSize(width,height);

	mLeftLayerGroup->setSize(width,height);//设置左大小
	mMidLayerGroup->setSize(width,height);//设置中大小
	mRightLayerGroup->setSize(width,height);//设置右大小

	mTextBoxBG->setSize(width,height);//TextBoxBG
	mEffectLayer->setSize(width,height);//EFLayer
	mEffectLayer->eventMouseButtonClick+= MyGUI::newDelegate(this, &GUIStage::eventMouseButtonClick);
}

GUIStage::~GUIStage(void)
{
}

void GUIStage::showScene()
{

}

void GUIStage::hideScene()
{

}

void GUIStage::eventMouseButtonClick(MyGUI::Widget* _sender)
{
	if (mCheckMouseDown)
	{
		mIsMouseDown=true;
		mCheckMouseDown=false;
	}
}


void GUIStage::setCheckMouseDown()
{
	mCheckMouseDown=true;
	mIsMouseDown=false;
}

bool GUIStage::CheckMouseState()
{
	return mIsMouseDown;
}


void GUIStage::setTextDialog( const GUIDialogAttribute& attribute )
{
	mTextBox->setPosition(attribute.TextLeft,attribute.TextTop);
	mTextX=attribute.TextLeft;
	mTextY=attribute.TextTop;

	mTextBox->setSize(attribute.TextWidth,attribute.TextHeight);
	mTextBox->setTextColour(MyGUI::Colour(attribute.TextRed,attribute.TextGreen,attribute.TextBlue));
	mTextBox->setFontName(attribute.TextFont);

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
	if (visible)
	{
		mSetp=0;
		mSetpDirection=true;
	}
	else
	{
		mSetp=1;
		mSetpDirection=false;
	}

	mTextBoxBG->setAlpha(mSetp);
	mTextBoxBG->setVisible(true);

	mTimerWork=DialogVisible;
	mTickTime=DefaultDialogVisibleTime*1000/100;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::waitTime( float time )
{
	mTimerWork=WaitWork;
	mTickTime=time;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::showText( std::wstring text,float delay)
{
	if(delay==0)
	{
		mTextBox->addText(text);
	}
	else
	{
		//如果是打字效果,那么启动打字定时器
		mTextBuffer=text;
		mTimerWork=PrinterWork;
		mTickTime=delay*1000;

		//开始帧更新
		mTimer.reset();
		GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
	}
}

void GUIStage::showImage( std::string imageName,GUIImageLayer layer,float time,int left,int top)
{

	//选择图层

	switch(layer)
	{
	case EffectsLayer:
		{
			mScrLayer=mEffectLayer;
			mUniversalLayer=NULL;
		}
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
	case AllLayer://如果为清除所有的人物
		{
			mSetp=1;
			mTimerWork=ClearAllRoleWork;
			mTickTime=time/100;

			//开始帧更新
			mTimer.reset();
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
			i.load(imageName,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
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
			mUniversalLayer->setAlpha(0);
			mUniversalLayer->setImageTexture(imageName);
			mUniversalLayer->setVisible(true);

			mSetp=0;
			mTimerWork=UniversalWork;
			mTickTime=time/100;
			mTextureName=imageName;

			//开始帧更新
			mTimer.reset();
			GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
		}
		else
		{
			mScrLayer->setImageTexture(imageName);
		}

	}
}

void GUIStage::showRoleName( std::wstring text )
{
	mRoleNameUniversal->setAlpha(0);
	mRoleNameUniversal->setCaption(text);
	mRoleNameUniversal->setVisible(true);

	mSetp=0;
	mTimerWork=RoleNameWork;
	mTickTime=DefaultRoleNameVisibleTime*1000/100;

	//开始帧更新
	mTimer.reset();
	GUISystem::getSingletonPtr()->setFrameUpdateScene(StageScene);
}

void GUIStage::showOtherText()
{
	//停止帧更新
	mTickTime=0;
	mTimerWork=NoneWork;
	GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);

	mTextBox->addText(mTextBuffer);
	mTextBuffer.clear();
}

void GUIStage::clearText()
{
	mTextBox->setCaption("");
}

void GUIStage::FrameEvent()
{
	if(mTickTime!=0)
	{
		if (mTimer.getMilliseconds()>=mTickTime)
		{
			//复位定时器
			mTimer.reset();

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
			case UniversalWork:
				{
					if(mSetp+0.01<=1.0)
					{

						mScrLayer->setAlpha(1.0-mSetp);
						mUniversalLayer->setAlpha(mSetp);

						mSetp+=0.01;
					}
					else
					{
						mScrLayer->setImageTexture(mTextureName);
						mScrLayer->setAlpha(1.0);
						mUniversalLayer->setVisible(false);

						//停止帧更新
						mTickTime=0;
						mTimerWork=NoneWork;
						GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
					}

					break;
				}
				case DialogVisible:
					{
						if (mSetpDirection)//判定渐变步方向
						{
							if(mSetp+0.01<=1.0)
							{
								mSetp+=0.01;
								
								mTextBoxBG->setAlpha(mSetp);
							}
							else
							{
								//停止帧更新
								mTickTime=0;
								mTimerWork=NoneWork;
								GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
							}
						}
						else
						{
							if(mSetp-0.01>=0)
							{
								mSetp-=0.01;
								
								mTextBoxBG->setAlpha(mSetp);
							}
							else
							{

								mTextBoxBG->setVisible(false);

								//停止帧更新
								mTickTime=0;
								mTimerWork=NoneWork;
								GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
							}

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
				case RoleNameWork:
					{
						if(mSetp+0.01<=1.0)
						{
							mRoleName->setAlpha(1.0-mSetp);
							mRoleNameUniversal->setAlpha(mSetp);

							mSetp+=0.01;
						}
						else
						{
							std::string s=mRoleNameUniversal->getCaption();
							mRoleNameUniversal->setVisible(false);
							mRoleName->setCaption(s);
							mRoleName->setAlpha(1);

							//停止帧更新
							mTickTime=0;
							mTimerWork=NoneWork;
							GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
						}

						break;
					}
				case ClearAllRoleWork:
					{
						if(mSetp-0.01>=0)
						{
							mSetp-=0.01;

							mLeftLayer->setAlpha(mSetp);
							mMidLayer->setAlpha(mSetp);
							mRightLayer->setAlpha(mSetp);

						}
						else
						{
							
							mLeftLayer->setImageTexture("");
							mLeftLayer->setAlpha(1.0);
							mMidLayer->setImageTexture("");
							mMidLayer->setAlpha(1.0);
							mRightLayer->setImageTexture("");
							mRightLayer->setAlpha(1.0);

							//停止帧更新
							mTickTime=0;
							mTimerWork=NoneWork;
							GUISystem::getSingletonPtr()->setFrameUpdateScene(NoneScene);
						}
					}
			}
		}
	}
}

void GUIStage::showTextCursor( bool isLine )
{
	MyGUI::IntPoint p=mTextBox->getTextCursorPos();

	mTextCursor->setPosition(p.left,p.top);
	mTextCursor->setVisible(true);
	mTextCursor->setItemResource ("TextCursorImage");

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
